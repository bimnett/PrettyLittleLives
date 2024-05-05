
#include "DHT.h"
#include "rpcWiFi.h"
#include "TFT_eSPI.h"
#include <PubSubClient.h>
#include "connectionCredentials.h"

// Initialize TFT_eSPI object to manipulate screen.
TFT_eSPI tft;

// Initialize and declare necessary variables for local MQTT broker
WiFiClient wifiClient;
PubSubClient mqttClient;

// To be able to read the analog readings with the
// temperature and humidity sensor throug the pin A0
// DHT11 is the sensor temperature and humidity sensor 
DHT dht(A0, DHT11);   


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setTextSettings();
  connectToWiFi();
  connectToMQTTBroker();
  dht.begin(); 
  
}


void loop() {
  // Re-establish connection if any is lost
  if(!WiFi.isConnected()) {
    connectToWiFi();
  }
  if(!mqttClient.loop()) {
    connectToMQTTBroker();
  }

  //read the tempature 
  float temperature = dht.readTemperature(); 

  // convert temp to string so it can be sent to MQTT broker
  char temp_char[5];
  dtostrf(temperature,5, 1, temp_char);
  mqttClient.publish("pll/sensor/temp", temp_char);

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


// to be able to recive mqtt messages 
void callback(char* topic, byte* payload, unsigned int length) {
  char message[length];
  // transform the byte to a readable message 
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