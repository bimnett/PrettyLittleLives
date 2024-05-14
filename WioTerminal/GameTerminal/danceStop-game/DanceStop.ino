#include <LIS3DHTR.h> // Library for buitl-in accelerometer 
LIS3DHTR <TwoWire> motion; // Uses the TwoWire interface 

void setup() {
  Serial.begin(115200); 
  motion.begin(Wire1); // Wire1 is part of the TwoWire interface

// Checks if the built-in accelerometer sensor is initialised, if not prints an error message and halts the rest of the program.  
  if(!motion){ 
    Serial.println("Error"); 
    while(1);
  }
  motion.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); 
  motion.setFullScaleRange(LIS3DHTR_RANGE_2G); 

}

void loop() {
  float xValues = motion.getAccelerationX(); // Retrieves the acceleration on the x-axis which is direction: Forward  
  float yValues = motion.getAccelerationY(); // Retrieves the acceleration on the y-axis which is direction: Sideways 
  float zValues = motion.getAccelerationZ(); // Retrieves the acceleration on the z-axis which is direction: Upwards 

  // Calculate total acceleration magnitude
  float totalAcceleration = sqrt((yValues * yValues) + (zValues * zValues)+ (xValues * xValues)); 

  float motionThreshold = 1.04; 
  //Serial.println("total acc: ");
  //Serial.println(totalAcceleration); 

  if(totalAcceleration > motionThreshold){
    Serial.println("Motion detected"); 
    
  } else{
    Serial.println("No motion detected"); 
  }
  delay(100); 
}
