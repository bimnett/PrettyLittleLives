#include "TFT_eSPI.h"

TFT_eSPI tft;

// These options will be changed based on the message from the web client
String options[] = {"Option 1", "Option 2", "Option 3", "Option 4"};

// Default value for a 
String selectedOption = options[0];

void setup() {

  Serial.begin(115200);

  // Initializes the 5-way joystick on the terminal
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);

  // Initializes the tft object and the initial background
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  startSoundGame();
}

void loop() {
  handleJoystickInput();
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

// Will send the selected answer to the mqtt broker
void submitAnswer() {

}


// Hard coded method for moving around the options visually.
// Each if/else if statement re-draws the options page.
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