
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
    sample = analogRead(0);
    if(sample < 1023){
      if( sample > signalMax){
        signalMax = sample; 
      }
      else if (sample < signalMin){
        signalMin = sample; 
      }
    }
  }
  
  peakToPeak = signalMax - signalMin; 
  // Mapping from anlog to decibel
  int db = map (peakToPeak, 20, 900, 49.5, 90); 

    Serial.println(db);
    delay(1000);
}

