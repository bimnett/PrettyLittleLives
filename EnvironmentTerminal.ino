#include "rpcWiFi.h"

// Credential variables need a pointer for WiFi.begin().
const char* ssid = "laptop";
const char* password =  "PrettyLL";

void setup() {

    Serial.begin(115200);
    while(!Serial); // Wait for Serial before moving on

    connectToWiFi();
}

void loop() {

}

void connectToWiFi() {

  // Disconnect from WiFi if it's currently connected
  WiFi.disconnect();
  delay(3000);
  
  // Attempts to connect to the WiFi network until it establishes a connection
  while(WiFi.status() != WL_CONNECTED) {

    Serial.println("Establishing connection...");
    WiFi.begin(ssid, password);
    delay(3000);
  }

  // Prints the connection confirmation along with the IP
  Serial.println("Connection established!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}