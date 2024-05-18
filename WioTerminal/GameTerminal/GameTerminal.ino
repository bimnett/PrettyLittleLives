#include "TFT_eSPI.h"
#include "rpcWiFi.h"
#include <PubSubClient.h>
#include <cstring>
#include "connectionCredentials.h"
#include <LIS3DHTR.h> // Library for built-in accelerometer 

// Declare tft object for manipulating the wio terminal screen.
TFT_eSPI tft;
LIS3DHTR <TwoWire> motion; // Uses the TwoWire interface 

// Declare necessary variables for MQTT broker
WiFiClient wifiClient;
PubSubClient mqttClient;



// Variables that keep track if a game is currently active.
// Will be checked in the loop function before doing any game logic.
bool isDanceGameActive;
bool isSoundGameActive;
bool isDancing = false;



void setup() {
  Serial.begin(115200);

  // Initialize game states
  isDanceGameActive = false;
  isSoundGameActive = false;

  // Initializes the 5-way joystick on the terminal
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);

  // Initializes button on the terminal
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  pinMode(WIO_BUZZER, OUTPUT);
  motion.begin(Wire1); // Wire1 is part of the TwoWire interface

  // Initializes the tft object and the initial background
  setTextSettings();

  // Connect to WiFi and MQTT broker.
  connectToWiFi();
  connectToMQTTBroker();

  // Subscribe to sound game topics
  mqttClient.subscribe("pll/game-terminal/sound-game/options");
  mqttClient.subscribe("pll/game-terminal/sound-game/check-answer");
  mqttClient.subscribe("pll/game/dancestop/state");

  // Checks if the built-in accelerometer sensor is initialised, if not prints an error message in terminal and alerts the player on LCD screen.
  if (!motion) { 
    Serial.println("Error"); 
    shiftScreenColorAndText(TFT_YELLOW, "Dance Stop not available!");
    delay(1000); 
  }
  motion.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); 
  motion.setFullScaleRange(LIS3DHTR_RANGE_2G); 
}

void loop() {
  // Re-establish connection if any is lost
  if (!WiFi.isConnected()) {
    connectToWiFi();
  }
  if (!mqttClient.loop()) {
    connectToMQTTBroker();
  }

  // Track user input for the sound game
  if(isSoundGameActive) {
    
    replaySound();
    handleJoystickInput();
  }
  
  if(isDanceGameActive) {
    detectMotion(); 
  }
}

// Display text on the center of the screen.
void displayText(char* text) {
  tft.fillScreen(0x0000);
  tft.drawString(text, tft.width() / 2, tft.height() / 2);
}

/* ________________________________ WIFI AND MQTT CONNECTION _______________________________________*/

void connectToWiFi() {
  // Attempt to connect to the WiFi network until a connection is established
  while (!WiFi.isConnected()) {
    displayText("Connecting to WiFi..");
    WiFi.begin(SSID, WIFI_PASSWORD);
    delay(3000);
  }
  // Print confirmation
  displayText("Connected!");
}

void connectToMQTTBroker() {
  // Configure pubsub client with property setters
  while (!mqttClient.connected()) {
    // Ensure that WiFi is connected before proceeding
    if (!WiFi.isConnected()) {
      connectToWiFi();
    }
    displayText("Connecting to MQTT..");
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    // If mqtt connection is successful, break from loop.
    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      break;
    }
    if (!mqttClient.connected()) {
      delay(3000);
    }
  }
  mqttClient.setCallback(callback);
  displayText("MQTT connected!");
  delay(1000);
}

/* ___________________________________ END WIFI AND MQTT CONNECTION ___________________________________*/

/* --------------------------------------- DANCE_STOP GAME LOGIC --------------------------------------*/

void detectMotion() {
  float xValues = motion.getAccelerationX(); // Retrieves the acceleration on the x-axis which is direction: Forward  
  float yValues = motion.getAccelerationY(); // Retrieves the acceleration on the y-axis which is direction: Sideways 
  float zValues = motion.getAccelerationZ(); // Retrieves the acceleration on the z-axis which is direction: Upwards 

  // Calculate total acceleration magnitude
  float totalAcceleration = sqrt((yValues * yValues) + (zValues * zValues) + (xValues * xValues)); 

  float motionThreshold = 1.25; // motionThreshold is the "limit" used to decide whether or not there is enough movement.
  
  if (isDancing) {
    shiftScreenColorAndText(TFT_GREEN, "GO!"); // Change screen color to green and adds GO message on LCD screen 
    if (totalAcceleration < motionThreshold) {
      shiftScreenColorAndText(TFT_GREEN, "Keep on dancing!");
      playBuzzer();
    }
  } else {
    shiftScreenColorAndText(TFT_RED, "STOP!"); // Change screen color to red and adds stop message on LCD screen 
    if (totalAcceleration > motionThreshold) {
      shiftScreenColorAndText(TFT_RED, "Stop dancing!");
      playBuzzer(); 
    }
    delay(100); 
  }
}

void shiftScreenColorAndText(uint16_t color, const char* text){
  tft.fillScreen(color);
  // Display text on screen 
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(text, tft.width() / 2, tft.height() / 2);
}

void playBuzzer() {
  analogWrite(WIO_BUZZER, 150); 
  delay(1000); 
  analogWrite(WIO_BUZZER, 0); 
  delay(1000); 
}

/* ------------------------------ END DANCE_STOP GAME -------------------------------------------*/



// Retrieves mqtt subscription message.
// Is automatically called when a message is received.
// The handling of the message and topic is delegated to a separate function.
void callback(char* topic, byte* payload, unsigned int length) {

  // 
  char message[length];

  for (int i = 0; i < length; i++) {
    message[i] = payload[i];
  }

  handleSubMessage(message, topic);
}

// Handler that triggers different actions depending on topic and subscription message. 
void handleSubMessage(char message[], const char* topic) {

  isSoundGameActive = false;
  isDanceGameActive = false;

  // Start new instance of the sound game
  if (strcmp(topic, "pll/game-terminal/sound-game/options") == 0) {

    // Set the different option values
    parseSoundGameOptions(message);

    // Start the game
    isSoundGameActive = true;
    startSoundGame();

    return;
  }

  // Display result of the user's answer for the sound game
  else if (strcmp(topic, "pll/game-terminal/sound-game/check-answer") == 0) {

    isSoundGameActive = true;

    if (strcmp("correct", message) == 0) {
      displayCorrect();
    } else {
      displayIncorrect();
    }

    return;
  }

  else if(strcmp(topic, "pll/game/dancestop/state") == 0) {

    isDanceGameActive = true;

    // Convert message to integer for dance state comparison.
    int danceState = atoi((char*)message);

    if(danceState == 1) {
      isDancing = true;
    }
    else if(danceState == 0) {
      isDancing = false;
    }

    return;
  }
}

// Set text settings and background.
void setTextSettings() {
  
  tft.begin();
  tft.setRotation(3);
  tft.setTextSize(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.setTextDatum(MC_DATUM);
}


// Overloaded text method to choose size and color.
void setTextSettings(uint16_t color, int textSize) {
  tft.setTextSize(textSize);
  tft.setTextColor(color);
  tft.setTextDatum(MC_DATUM);
}



/**********************************************************************************************************************************/


                                  /**************************************************
                                   *                                                *
                                   *                   Sound Game                   *
                                   *                                                *
                                   *                      ↓ ↓ ↓                     *
                                   **************************************************/


// Options for the end-user to select from. Will be initialized from a subscription message from the web client.
String options[4];

// Keeps track of current value for the selected option
String selectedOption;


// Parse options message and set the option values
void parseSoundGameOptions(char message[]) {

  // Split subscription message for parsing.
    char* subOptions = strtok(message, ",");
    int i = 0;

    // Set the value of each option from newly created subOptions
    while(subOptions != NULL) {
      options[i] = subOptions;
      subOptions = strtok (NULL, ",");
      i++;
    }

    // Set 1st option as default value.
    selectedOption = options[0];
}


// Displays correct answer animation
void displayCorrect() {

  // Display green 'Correct!' text at the top
  tft.fillRect(0, 0, tft.width(), 50, TFT_BLACK);
  setTextSettings(TFT_DARKGREEN, 3);
  tft.drawString("Correct!", tft.width() / 2, 25);
}


// Displays incorrect answer animation
void displayIncorrect() {

  // Display red 'Try again..' text at the top
  tft.fillRect(0, 0, tft.width(), 50, TFT_BLACK);
  setTextSettings(TFT_RED, 3);
  tft.drawString("Try again..", tft.width() / 2, 25);
}


// Sends a message to the mqtt broker to replay the sound from the web app.
void replaySound() {

  if(digitalRead(WIO_KEY_C) == LOW) {
    mqttClient.publish("pll/game-terminal/sound-game/replay-sound", "replay");
    delay(300); // Delay to ensure a button click only sends one message.
  }
}


// Handles the joystick input by calling their respective method when it's being used.
void handleJoystickInput() {

  if (digitalRead(WIO_5S_UP) == LOW) {
    moveUp();
  }
  else if (digitalRead(WIO_5S_DOWN) == LOW) {
    moveDown();
  }
  else if (digitalRead(WIO_5S_LEFT) == LOW) {
    moveLeft();
  }
  else if (digitalRead(WIO_5S_RIGHT) == LOW) {
    moveRight();
  }
  else if (digitalRead(WIO_5S_PRESS) == LOW) {
    submitAnswer();
    delay(350); // Delay to ensure a button click only sends one answer.
  }
}


// Moves to the upwards option, if it's possible.
void moveUp() {
  
  if(selectedOption == options[2]) {
    selectedOption = options[0];
  }

  else if(selectedOption == options[3]) {
    selectedOption = options[1];
  }

  else {
    return;
  }

  displayCurrentOption(selectedOption);
}


// Moves to the downwards option, if it's possible.
void moveDown() {
  
  if(selectedOption == options[0]) {
    selectedOption = options[2];
  }

  else if(selectedOption == options[1]) {
    selectedOption = options[3];
  }

  else {
    return;
  }
  
  displayCurrentOption(selectedOption);
}


// Moves to the left option, if it's possible.
void moveLeft() {
  
  if(selectedOption == options[1]) {
    selectedOption = options[0];
  }

  else if(selectedOption == options[3]) {
    selectedOption = options[2];
  }

  else {
    return;
  }
  
  displayCurrentOption(selectedOption);
}


// Moves to the right option, if it's possible.
void moveRight() {
  
  if(selectedOption == options[0]) {
    selectedOption = options[1];
  }

  else if(selectedOption == options[2]) {
    selectedOption = options[3];
  }

  else {
    return;
  }
  
  displayCurrentOption(selectedOption);
}


// Sends the selected answer to the broker
void submitAnswer() {

  mqttClient.publish("pll/game-terminal/sound-game/answer", selectedOption.c_str());
}


// Hard coded method for moving around the options visually.
// Each if/else if statement re-draws the options page based on which option is selected.
void displayCurrentOption(String option) {

  
  if(option == options[0]) {

    // Displays rectangles, with the selected one being highlighted in cyan
    tft.fillRect(0, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_CYAN);
    tft.fillRect(tft.width() / 2 + 1, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(0, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(tft.width() / 2 + 1, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);

    // Displays the option names again, since the drawing of rectangles overwrites the previous text.
    tft.drawString(options[0], tft.width() / 4, (tft.height() + 50) / 3);
    tft.drawString(options[1], tft.width() / 4 * 3, (tft.height() + 50) / 3);
    tft.drawString(options[2], tft.width() / 4, (tft.height() + 50) / 3 * 2);
    tft.drawString(options[3], tft.width() / 4 * 3, (tft.height() + 50) / 3 * 2);
  }


  else if(option == options[1]) {

    // Displays rectangles, with the selected one being highlighted in cyan
    tft.fillRect(0, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(tft.width() / 2 + 1, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_CYAN);
    tft.fillRect(0, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(tft.width() / 2 + 1, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);

    // Displays the option names again, since the drawing of rectangles overwrites the previous text.
    tft.drawString(options[0], tft.width() / 4, (tft.height() + 50) / 3);
    tft.drawString(options[1], tft.width() / 4 * 3, (tft.height() + 50) / 3);
    tft.drawString(options[2], tft.width() / 4, (tft.height() + 50) / 3 * 2);
    tft.drawString(options[3], tft.width() / 4 * 3, (tft.height() + 50) / 3 * 2);
  }


  else if(option == options[2]) {

    // Displays rectangles, with the selected one being highlighted in cyan
    tft.fillRect(0, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(tft.width() / 2 + 1, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(0, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_CYAN);
    tft.fillRect(tft.width() / 2 + 1, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);

    // Displays the option names again, since the drawing of rectangles overwrites the previous text.
    tft.drawString(options[0], tft.width() / 4, (tft.height() + 50) / 3);
    tft.drawString(options[1], tft.width() / 4 * 3, (tft.height() + 50) / 3);
    tft.drawString(options[2], tft.width() / 4, (tft.height() + 50) / 3 * 2);
    tft.drawString(options[3], tft.width() / 4 * 3, (tft.height() + 50) / 3 * 2);
  }


  else {

    // Displays rectangles, with the selected one being highlighted in cyan
    tft.fillRect(0, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(tft.width() / 2 + 1, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(0, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_YELLOW);
    tft.fillRect(tft.width() / 2 + 1, (tft.height() + 50) / 2 + 1, tft.width() / 2, (tft.height() - 50) / 2, TFT_CYAN);

    // Displays the option names again, since the drawing of rectangles overwrites the previous text.
    tft.drawString(options[0], tft.width() / 4, (tft.height() + 50) / 3);
    tft.drawString(options[1], tft.width() / 4 * 3, (tft.height() + 50) / 3);
    tft.drawString(options[2], tft.width() / 4, (tft.height() + 50) / 3 * 2);
    tft.drawString(options[3], tft.width() / 4 * 3, (tft.height() + 50) / 3 * 2);
  }
}


// Displays the sound game.
void startSoundGame() {

  //Paints the background yellow and adds the black borders
  tft.fillRect(0, 50, tft.width(), tft.height(), TFT_YELLOW);
  tft.drawLine(tft.width() / 2, 50, tft.width() / 2, tft.height(), TFT_BLACK);  
  tft.drawLine(0, (tft.height() + 50) / 2, tft.width(), (tft.height() + 50) / 2, TFT_BLACK);

  // Draws game title
  setTextSettings(TFT_YELLOW, 3);
  tft.fillRect(0, 0, tft.width(), 50, TFT_BLACK);
  tft.drawString("Guess The Sound!", tft.width() / 2, 25);

  // Displays option 1 as the initial selected option
  tft.fillRect(0, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_CYAN);

  // Displays the text for each option in their box
  setTextSettings(TFT_BLACK, 2);
  tft.drawString(options[0], tft.width() / 4, (tft.height() + 50) / 3); 
  tft.drawString(options[1], tft.width() / 4 * 3, (tft.height() + 50) / 3);
  tft.drawString(options[2], tft.width() / 4, (tft.height() + 50) / 3 * 2);
  tft.drawString(options[3], tft.width() / 4 * 3, (tft.height() + 50) / 3 * 2);
}


/************************************************ END OF SOUND GAME ***************************************************************/
