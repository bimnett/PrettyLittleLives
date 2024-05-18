#include <DHT.h> // For temperature sensor
#include "rpcWiFi.h" // For wifi
#include "TFT_eSPI.h" // For Wio display
#include <PubSubClient.h> // For the pub/sub MQTT
#include <Grove_LED_Bar.h> // For the LED bar 
// These header files below were created by the team, where: 
#include "connectionCredentials.h" // "connectionCredentials.h" --> credentials for the wifi and MQTT
#include "MaryLamb.h" // "MaryLamb.h" --> calls a function from this header when db exceed certain threshold
#include "WheelsOnTheBus.h" // "WheelsOnTheBus.h" --> calls a function from this header when db exceed certain threshold

/*----------------------------------------------------- START OF VARIABLE/OBJECT DECLARATION AND INITIALIZATION ----------------------------------------*/ 

// Create necessary instances of the header files + for the buzzer
#define BUZZER_PIN WIO_BUZZER 
WiFiClient wifiClient;
PubSubClient mqttClient;
TFT_eSPI tft;
MaryLamb mary(BUZZER_PIN);
WheelsOnTheBus WheelsOnTheBus(BUZZER_PIN);

// Temp sensor and LED bar
DHT dht(D2, DHT11);   
Grove_LED_Bar bar(D8, D6, 1);  // Clock pin, Data pin, Orientation

const int sampleWindow = 50; // Time frame where millis function will run. 
unsigned int soundSample; // Sound samples collected within the sampleWindow
unsigned long startMillis = millis();   
float peakToPeak = 0; 
unsigned int signalMin = 0; 
unsigned int signalMax = 1023; 

// Decibel thresholds for setLedbar function 
const int lowThreshold = 4; 
const int mediumLowThreshold = 6; 
const int mediumHighThreshold = 11; 
const int highThreshold = 15; 


/*-------------------------------------------------- END OF VARIABLE/OBJECT DECLARATION AND INITIALIZATION ----------------------------------------*/ 

void setup(){
  Serial.begin(9600);
  setTextSettings();
  connectToWiFi();
  connectToMQTTBroker();
  dht.begin(); 
  pinMode(BUZZER_PIN, OUTPUT); 
  bar.begin(); 
  
}

void loop() {
  // Re-establish WIFI and MQTT connection if lost
  if(!WiFi.isConnected()) {
    connectToWiFi();
  }
  if(!mqttClient.loop()) {
    connectToMQTTBroker();
  }

  // Read and convert temperature, to send it to the MQTT broker 
  float temperature = dht.readTemperature(); 
  char temp_char[4];
  dtostrf(temperature,4, 1, temp_char);
  mqttClient.publish("pll/sensor/temp", temp_char);

  delay(1000);

  // Read analog input from the loudness sensor and convert it to percentage
  soundSample = analogRead(0); 
  float db = map (soundSample, signalMin, signalMax, 0, 100); 

/* Play "Mary Had a Little Lamb" if sensor value is between 11% and 15%.
   Play "The wheels on the bus go round and round" if it exceeds 15%.
   Light up the ledbar according to the corresponding db % level
*/
  if(db >= mediumHighThreshold && db <= highThreshold) {
    mary.playSong();
  }else if(db > highThreshold){
    WheelsOnTheBus.playSong();
  }
  setLedbar(db); 

  // Convert to char to then send it to the mqtt broker
  char db_char[5];
  dtostrf(db,5, 1, db_char); 
  mqttClient.publish("pll/sensor/soundLevel", db_char);

  delay(1000);

}

/*----------------------------------------------------- START OF SEPERATE METHODS ------------------------------------------------------------*/


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


// In order to receive mqtt messages 
void callback(char* topic, byte* payload, unsigned int length) {
  char message[length];
  // Transform the byte to a readable message 
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
// Light up depending on the db percentage level
void setLedbar(int soundLevel) {
    if (soundLevel <= lowThreshold) {
        bar.setLevel(3); // Lights up 3 lights on the ledbar 
    } else if (soundLevel <= mediumLowThreshold) { 
        bar.setLevel(5); // Lights up 5 lights on the ledbar 
    } else if (soundLevel <= mediumHighThreshold) { 
        bar.setLevel(7); // Lights up 7 lights on the ledbar
    } else if (soundLevel <= highThreshold) { 
        bar.setLevel(8); // Lights up 8 lights on the ledbar
    } else if (soundLevel > highThreshold) { 
        bar.setLevel(10); // Lights up 10 lights on the ledbar
    } else {
        bar.setLevel(1); // Lights up 1 light on the ledbar
    }
}

/*----------------------------------------------------- START OF SEPERATE METHODS ------------------------------------------------------------*/