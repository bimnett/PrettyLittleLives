#include <Arduino.h> 


void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  float decibelValue = analogToDecibel(sensorValue);

  Serial.print("Analog value: ");
  Serial.println(sensorValue);

  Serial.print("Decibel value: ");
  Serial.println(decibelValue);

  delay(1000);
}

float analogToDecibel(float analogValue) {
  float referenceVoltage = 5.0;
  float currentVoltage = analogValue * (referenceVoltage / 1023.0);
  float decibelValue = 20 * log10(currentVoltage / referenceVoltage);
  return decibelValue;
}

