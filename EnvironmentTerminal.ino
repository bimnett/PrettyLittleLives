#include "rpcWiFi.h"
#include "TFT_eSPI.h"
#include "includes/connectionCredentials.h"


// Initialize TFT_eSPI object to manipulate screen.
TFT_eSPI tft;


void setup() {

  setTextSettings();
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

  // Attempt to connect to the WiFi network until a connection is established
  while(!WiFi.isConnected()) {

    displayText("Connecting to WiFi..");
    WiFi.begin(SSID, WIFI_PASSWORD);
    delay(3000);
  }

  // Print confirmation
  displayText("Connected!");
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