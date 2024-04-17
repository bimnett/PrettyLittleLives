#include "TFT_eSPI.h"
#include "rpcWiFi.h"
#include <PubSubClient.h>
#include <cstring>

// Declare tft object for manipulating the wio terminal screen.
TFT_eSPI tft;

// Initialize credential variables for WiFi.begin().
const char SSID[] = "laptop";
const char PASSWORD[] =  "PrettyLL";


// Initialize and declare necessary variables for local MQTT broker
WiFiClient wifiClient;
PubSubClient mqttClient;
const char MQTT_SERVER[] = "broker.hivemq.com";
const char MQTT_CLIENT_ID[] = "GameTerminal";
const int MQTT_PORT = 1883;


// Options for the end-user to select. Will be initialized from a subscription message from the web client.
String options[] = {"Option 1", "Option 2", "Option 3", "Option 4"};

// Default value for option
String selectedOption;

void setup() {

  Serial.begin(115200);

  // Initializes the 5-way joystick on the terminal
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);

  // Initialize sound replay button on top of terminal
  pinMode(WIO_KEY_C, INPUT_PULLUP);

  // Initializes the tft object and the initial background
  setTextSettings();
  connectToWiFi();
  connectToMQTTBroker();
  mqttClient.subscribe("pll/game-terminal/sound-game/options");
}

void loop() {

  // Re-establish connection if any is lost
  if(!WiFi.isConnected()) {
    connectToWiFi();
  }
  if(!mqttClient.loop()) {
    connectToMQTTBroker();
  }

  replaySound();
  handleJoystickInput();
}


// Display text on the center of the screen.
void displayText(char* text) {

  tft.fillScreen(0x0000);
  tft.drawString(text, tft.width() / 2, tft.height() / 2);
}


void connectToWiFi() {

  // Attempt to connect to the WiFi network until a connection is established
  while(!WiFi.isConnected()) {

    displayText("Connecting to WiFi..");
    WiFi.begin(SSID, PASSWORD);
    delay(3000);
  }

  // Print confirmation
  displayText("Connected!");
}


void connectToMQTTBroker() {

  // Configure pubsub client with property setters
  while(!mqttClient.connected()) {

    // Ensure that WiFi is connected before proceeding
    if(!WiFi.isConnected()) {
      connectToWiFi();
    }

    displayText("Connecting to MQTT..");

    mqttClient.setClient(wifiClient);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

    // If mqtt connection is successful, break from loop.
    if(mqttClient.connect(MQTT_CLIENT_ID)) {
      break;
    }
    
    if(!mqttClient.connected()) {
      delay(3000);
    }
  }

  mqttClient.setCallback(callback);
  displayText("MQTT connected!");
  delay(1000);
}

// Retrieves mqtt subscription message.
// Is automatically called when a message is received.
void callback(char* topic, byte* payload, unsigned int length) {

  char message[length];

  // Convert byte payload of the message to a character array.
  for(int i = 0; i < length; i++) {
    message[i] = payload[i];
  }


  // 
  char* subOptions = strtok(message, ",");
  int i = 0;

  while(subOptions != NULL) {
    options[i] = subOptions;
    subOptions = strtok (NULL, ",");
    i++;
  }


  // Set 1st option as default value.
  selectedOption = options[0];

  // Start the game
  startSoundGame();
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
    delay(350); // delay to ensure a button click only sends one answer.
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

  //
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

// Overloaded text method to choose size and color.
void setTextSettings(uint16_t color, int textSize) {
  tft.setTextSize(textSize);
  tft.setTextColor(color);
  tft.setTextDatum(MC_DATUM);
}

// Displays the sound game.
void startSoundGame() {

  //Paints the background yellow and adds the black borders
  tft.fillRect(0, 50, tft.width(), tft.height(), TFT_YELLOW);
  tft.drawLine(tft.width() / 2, 50, tft.width() / 2, tft.height(), TFT_BLACK);  
  tft.drawLine(0, (tft.height() + 50) / 2, tft.width(), (tft.height() + 50) / 2, TFT_BLACK);

  setTextSettings(TFT_YELLOW, 3);

  // Draws game title
  tft.drawString("Guess The Sound!", tft.width() / 2, 25);

  setTextSettings(TFT_BLACK, 2);

  // Displays option 1 as the initial selected option
  tft.fillRect(0, 50, tft.width() / 2, (tft.height() - 50) / 2, TFT_CYAN);

  // Displays the text for each option in their box
  tft.drawString(options[0], tft.width() / 4, (tft.height() + 50) / 3); 
  tft.drawString(options[1], tft.width() / 4 * 3, (tft.height() + 50) / 3);
  tft.drawString(options[2], tft.width() / 4, (tft.height() + 50) / 3 * 2);
  tft.drawString(options[3], tft.width() / 4 * 3, (tft.height() + 50) / 3 * 2);
}