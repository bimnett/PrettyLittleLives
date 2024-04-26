// #include <Arduino.h> 
#include "rpcWiFi.h"
#include "TFT_eSPI.h"
#include <PubSubClient.h>
#include "connectionCredentials.h"

// Initialize TFT_eSPI object to manipulate screen.
TFT_eSPI tft;

// Initialize and declare necessary variables for local MQTT broker
WiFiClient wifiClient;
PubSubClient mqttClient;
const char *MQTT_CLIENT_ID = "enviromentTerminal";


const int sampleWindow = 50; // Time frame where millis function will run. 
unsigned int soundSample; // sound sample collected within the sampleWindow

void setup()
{
  Serial.begin(9600);
  setTextSettings();
  connectToWiFi();
  connectToMQTTBroker();
}

void loop()
{
  // Re-establish connection if any is lost
  if(!WiFi.isConnected()) {
    connectToWiFi();
  }

  if(!mqttClient.loop()) {
    connectToMQTTBroker();
  }

  unsigned long startMillis = millis(); // Unsigned = always positive values. The milliseconds will always be positive.  
  float peakToPeak = 0; 
  unsigned int signalMax = 0; 
  unsigned int signalMin = 1023; 

  while (millis() - startMillis < sampleWindow){ 
    soundSample = analogRead(0);
    if(soundSample < 1023){
      if(soundSample > signalMax){
        signalMax = soundSample; 
      }
      else if (soundSample < signalMin){
        signalMin = soundSample; 
      }
    }
  }
  
  peakToPeak = signalMax - signalMin; 
  // Mapping from anlog to decibel
  float db = map (peakToPeak, 20, 900, 49.5, 90); 

  // convert to char* to then send it to the mqtt broker 
  char db_char[5];
  dtostrf(db,5, 1, db_char);

  mqttClient.publish("pll/sensor/enviroment", db_char);
  Serial.println(db);
  delay(1000);
}


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

void connectToMQTTBroker() {

  // Loop until mqtt connection is established
  while(!mqttClient.connected()) {

    // Ensure that WiFi is connected before proceeding
    if(!WiFi.isConnected()) {
      connectToWiFi();
    }

    displayText("Connecting to MQTT..");

    // Configure pubsub client with property setters
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.connect(MQTT_CLIENT_ID);
    mqttClient.setCallback(callback);
    
    // 3 second cooldown before next connection attempt
    if(!mqttClient.connected()) {
      delay(3000);
    }
  }

  displayText("MQTT connected!");
  delay(1000);
}

// Handle mqtt subscription message.
void callback(char* topic, byte* payload, unsigned int length) {

  char message[length];

  for(int i = 0; i < length; i++) {
    message[i] = payload[i];
  }

  displayText(message);
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


