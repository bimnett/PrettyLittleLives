#include <TFT_eSPI.h>
#include <LIS3DHTR.h> // Library for built-in accelerometer 
#include <rpcWiFi.h>
#include <PubSubClient.h> // MQTT client library
#include "connectionCredentials.h" 

LIS3DHTR <TwoWire> motion; // Uses the TwoWire interface 
WiFiClient wifiClient;
TFT_eSPI tft;
PubSubClient mqttClient(wifiClient);

bool isDancing = false;

void setup() {
  Serial.begin(115200);
  motion.begin(Wire1); // Wire1 is part of the TwoWire interface
  pinMode(WIO_BUZZER, OUTPUT);
  setTextSettings();  
  connectToWiFi(); 
  connectToMQTT();

  mqttClient.subscribe("pll/game/dancestop/state");

  
  // Checks if the built-in accelerometer sensor is initialised, if not prints an error message and halts the rest of the program.  
  if (!motion) { 
    Serial.println("Error"); 
    while (1);
  }
  motion.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); 
  motion.setFullScaleRange(LIS3DHTR_RANGE_2G); 

}

void loop() {
  if (!mqttClient.connected()) {
    connectToMQTT();
  }
  mqttClient.loop();
  checkMotion(); 


 
  delay(100); 
}
void checkMotion() {
  float xValues = motion.getAccelerationX(); // Retrieves the acceleration on the x-axis which is direction: Forward  
  float yValues = motion.getAccelerationY(); // Retrieves the acceleration on the y-axis which is direction: Sideways 
  float zValues = motion.getAccelerationZ(); // Retrieves the acceleration on the z-axis which is direction: Upwards 

  // Calculate total acceleration magnitude
  float totalAcceleration = sqrt((yValues * yValues) + (zValues * zValues) + (xValues * xValues)); 

  float motionThreshold = 1.04; 
  
  if (isDancing) {
    tft.fillScreen(TFT_GREEN); // Change screen color to green
    if (totalAcceleration > motionThreshold) {
      Serial.println("Motion detected - Keep dancing"); 
    } else {
      Serial.println("No motion detected - Dance!"); 
      playBuzzer(); // Play buzzer when no motion detected but user should keep dancing
    }
  } else {
    tft.fillScreen(TFT_RED); // Change screen color to red
    if (totalAcceleration < motionThreshold) {
      Serial.println(" No motion detected"); 
    } else {
      Serial.println("Motion detected - Stop!");
      playBuzzer(); // Play buzzer when motion detected but user should stop
    }
  }
}


void playBuzzer() {
  analogWrite(WIO_BUZZER, 150); 
  delay(1000); 
  analogWrite(WIO_BUZZER, 0); 
  delay(1000); 
}

void connectToWiFi() {
  // Attempt to connect to the WiFi network until a connection is established
  while (!WiFi.isConnected()) {
    displayText("Connecting to WiFi..");
    WiFi.begin(ssid, password);
    delay(3000);
  }
  // Print confirmation on wio terminal 
  displayText("Connected!");
}

void displayText(char* text) {
  tft.fillScreen(0x0000);
  tft.drawString(text, tft.width() / 2, tft.height() / 2);
}

void setTextSettings() {
  tft.begin();
  tft.setRotation(3);
  tft.setTextSize(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.setTextDatum(MC_DATUM);
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Convert payload to an integer
  int message = atoi((char*)payload);
  
  // Check message content and change the state accordingly
  if (message == 1) {
    isDancing = true;
  } else if (message == 0) {
    isDancing = false;
  }
}

void connectToMQTT() {
  // Loop until MQTT connection is established
  while (!mqttClient.connected()) {
    // Ensure that WiFi is connected before proceeding
    if (!WiFi.isConnected()) {
      connectToWiFi();
    }
    displayText("Connecting to MQTT..");

    // Configure pubsub client with property setters
    mqttClient.setClient(wifiClient);
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

    // If mqtt connection is successful, break from loop.
    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      mqttClient.setCallback(callback);
      break;
    }

    // If MQTT connection failed, wait and retry
    if (!mqttClient.connected()) {
      Serial.println("Failed to connect to MQTT broker, retrying...");
      delay(3000);
    }
  }

  displayText("MQTT connected!");
  delay(1000);
}
