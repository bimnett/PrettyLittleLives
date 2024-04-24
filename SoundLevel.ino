// #include <Arduino.h> 

const int sampleWindow = 50; // Time frame where millis function will run. 
unsigned int soundSample; // sound sample collected within the sampleWindow

void setup()
{
    Serial.begin(9600);
}

void loop()
{
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
  int db = map (peakToPeak, 20, 900, 49.5, 90); 

    Serial.println(db);
    delay(1000);
}

