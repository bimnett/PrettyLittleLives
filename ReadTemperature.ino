
#include "DHT.h"
DHT dht(A0, DHT11);   // use pin A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin(); 
}

void loop() {
  // put your main code here, to run repeatedly:
float temperature = dht.readTemperature(); 
Serial.println(temperature); 
delay(1000);

}
