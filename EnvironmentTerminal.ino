#include "rpcWiFi.h"
#include "TFT_eSPI.h"

// Initialize TFT_eSPI object to manipulate screen.
TFT_eSPI tft;

// Initialize credential variables for WiFi.begin().
const char* ssid = "laptop";
const char* password =  "PrettyLL";


void setup() {

  // Set text settings and background.
  tft.begin();
  tft.setRotation(3);
  tft.setTextSize(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.setTextDatum(MC_DATUM);

  connectToWiFi();
}

void loop() {

}

// Display text on the center of the screen.
void displayText(char* text) {
  tft.fillScreen(0x0000);
  tft.drawString(text, tft.width() / 2, tft.height() / 2);
}

void connectToWiFi() {

  // Disconnect from WiFi if it's currently connected
  if(WiFi.status() == WL_CONNECTED) {
    displayText("Disconnecting from WiFi..");
    WiFi.disconnect();
    delay(3000);
  }
  
  // Attempt to connect to the WiFi network until a connection is established
  while(WiFi.status() != WL_CONNECTED) {
    displayText("Connecting to WiFi..");
    WiFi.begin(ssid, password);
    delay(3000);
  }

  // Print confirmation
  displayText("Connected!");
}