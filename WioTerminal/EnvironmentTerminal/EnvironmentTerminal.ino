#include <DHT.h>
#include "rpcWiFi.h"
#include "TFT_eSPI.h"
#include <PubSubClient.h>
#include "connectionCredentials.h"
#include <Grove_LED_Bar.h>

#include "MaryLamb.h"
#include "WheelsOnTheBus.h"

// Macro define
#define BUZZER_PIN WIO_BUZZER 

// Initialize TFT_eSPI object to manipulate screen.
TFT_eSPI tft;

// Initialize and declare necessary variables for local MQTT broker
WiFiClient wifiClient;
PubSubClient mqttClient;

// To be able to read the analog readings with the
// temperature and humidity sensor throug the pin A0
// DHT11 is the sensor temperature and humidity sensor 
DHT dht(A0, DHT11);   
Grove_LED_Bar bar(A1, A0, 1);  // Clock pin, Data pin, Orientation

const int sampleWindow = 50; // Time frame where millis function will run. 
unsigned int soundSample; // sound samples collected within the sampleWindow
unsigned long startMillis = millis();   
float peakToPeak = 0; 
unsigned int signalMin = 0; 
unsigned int signalMax = 1023; 

// Lower and upper decibel bound for melody player
const int lowerBound = 50;
const int upperBound = 60;

// Decibel thresholds for setLedbar function 
const int lowThreshold = 30; 
const int mediumLowThreshold = 50; 
const int mediumHighThreshold = 70; 
const int highThreshold = 75; 

// Instance of MaryLamb
MaryLamb mary(BUZZER_PIN);
//Instance of WheelsOTheBus
WheelsOnTheBus WheelsOnTheBus(BUZZER_PIN);


void setup(){
  Serial.begin(9600);
  setTextSettings();
  connectToWiFi();
  connectToMQTTBroker();
  dht.begin(); 
  // Buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT); 
  bar.begin(); // initialise ledbar 
  
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


  soundSample = analogRead(0); // read analog input from the loudness sensor 

  
  // Mapping from anlog to decibel
  float db = map (soundSample, signalMin, signalMax, 0, 100); 

  // Play "Mary Had a Little Lamb" if sensor value is between 50db and 60db.
  // Play "The wheels on the bus go round and round" if it exceeds 60db.
  
  setLedbar(db); // Light upp the ledbar, according to the decibel value.

  // convert to char* to then send it to the mqtt broker
  char db_char[5];
  dtostrf(db,5, 1, db_char); 

  mqttClient.publish("pll/sensor/soundLevel", db_char);
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

void setLedbar(int soundLevel) {
    if (soundLevel <= lowThreshold) {
        bar.setLevel(3); // lights up 3 lights on the ledbar 
    } else if (soundLevel <= mediumLowThreshold) { 
        bar.setLevel(5); // lights up 5 lights on the ledbar 
    } else if (soundLevel <= mediumHighThreshold) { 
        bar.setLevel(7); // lights up 7 lights on the ledbar
    } else if (soundLevel <= highThreshold) { 
        bar.setLevel(8); // lights up 8 lights on the ledbar
    } else if (soundLevel > highThreshold) { 
        bar.setLevel(10); // lights up 10 lights on the ledbar
    } else {
        bar.setLevel(1); // lights up 1 light on the ledbar
    }
}

