#include <LIS3DHTR.h> // Library for buitl-in accelerometer 
LIS3DHTR <TwoWire> motion; // Uses the TwoWire interface 

int dance = 1; 
int stop = 2; 
int choice; 
bool isDancing = false; 

void setup() {
  Serial.begin(115200); 
  motion.begin(Wire1); // Wire1 is part of the TwoWire interface
  pinMode(WIO_BUZZER, OUTPUT); 

// Checks if the built-in accelerometer sensor is initialised, if not prints an error message and halts the rest of the program.  
  if(!motion){ 
    Serial.println("Error"); 
    while(1);
  }
  motion.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); 
  motion.setFullScaleRange(LIS3DHTR_RANGE_2G); 


Serial.println("Enter option 1 for Dance or 2 for Stop: "); 
    while(Serial.available()== 0){
      }
    
    choice = Serial.parseInt();
    if (choice == dance){
      isDancing = true; 
    } else {
      isDancing = false; 
    }
}

void loop() {
  float xValues = motion.getAccelerationX(); // Retrieves the acceleration on the x-axis which is direction: Forward  
  float yValues = motion.getAccelerationY(); // Retrieves the acceleration on the y-axis which is direction: Sideways 
  float zValues = motion.getAccelerationZ(); // Retrieves the acceleration on the z-axis which is direction: Upwards 

  // Calculate total acceleration magnitude
  float totalAcceleration = sqrt((yValues * yValues) + (zValues * zValues) + (xValues * xValues)); 

  float motionThreshold = 1.04; 
  
  if(choice == dance && isDancing){
    if(totalAcceleration > motionThreshold){
        Serial.println("Motion detected - Keep dancing"); 
      } else {
          Serial.println("No motion detected - Dance!"); 
          playBuzzer(); 
      }
  } else if (choice == stop && !isDancing){
      if(totalAcceleration < motionThreshold){
          Serial.println(" No motion detected"); 
        } else {
          Serial.println("Motion detected - Stop!");
          //Other buzzer sound to be implemented here! 
        }
  }
 
  delay(100); 
}
void playBuzzer(){
 analogWrite(WIO_BUZZER, 150); 
    delay(1000); 
    analogWrite(WIO_BUZZER, 0); 
    delay(1000); 
}