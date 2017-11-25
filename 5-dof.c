#include <SoftwareSerial.h> 
#include <Wire.h> 
#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP085_U.h> 
#include <Adafruit_ADXL345_U.h> 
#include <L3G4200D.h> 
L3G4200D gyro; 
#define address 0x1E  // 0011110b, I2C 7bit address of HMC5883 

float ground_level1; 
float ground_level2; 
float ground_level3; 
float ground_level4; 
float ground_level5; 
float ground_level6; 
float ground_level7; 
float ground_level8; 
float ground_level9; 
float ground_level10; 
float ground_level = 1; 

float pressure1; 
float pressure2; 
float pressure3; 
float pressure4; 
float pressure5; 
float pressure6; 
float pressure7; 
float pressure8; 
float pressure9; 
float pressure10; 
float pressure; 

// New.... 
int Pin_1 = A0; 
int Pin_2 = A1; 
int Pin_3 = A3; 
int Pin_4 = A4; 
int Pin_5 = A5; 
int Pin_6 = A2; 
int m [5]; 

float temperature; 
int x,y,z; // triple axis data 

// Time  
int toto = 0; 
int titi = 0; 
int dt = 0; 

const int buttonPin_1 = 8; 
const int buttonPin_2 = 7; 
const int buttonPin_3 = 4; 
const int ledPin = 13; 

int buttonState_1 = 0; 
int buttonState_2 = 0; 
int buttonState_3 = 0; 
int state = 0; 

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085); 
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); 

SoftwareSerial data(9, 10); 

void setup() 
{ 
 Serial.begin(9600); 
 data.begin(9600); 
 Wire.begin(); 
 gyro.enableDefault(); 

 // Put the HMC5883 IC into the correct operating mode 
 Wire.beginTransmission(address); // open communication with HMC5883 
 Wire.write(0x02); // select mode register 
 Wire.write(0x00); // continuous measurement mode 
 Wire.endTransmission(); 

 pinMode(ledPin, OUTPUT); 
 pinMode(buttonPin_1, INPUT); 
 pinMode(buttonPin_2, INPUT); 
 pinMode(buttonPin_3, INPUT); 

 // Initialise the sensors 
 if( !bmp.begin() ) 
 {  // If the sensor can't be found 
  Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!"); 
  while(1); 
 } 

 if( !accel.begin() ) 
 {  // If the sensor can't be found 
  Serial.println("Ooops, no ADXL345 detected ... Check your wiring!"); 
  while(1); 
 } 

 // Set the datarate and range to what is appropriate for project 
 accel.setRange(ADXL345_RANGE_16_G); 
 displaySetRange(ADXL345_RANGE_8_G); 
 displaySetRange(ADXL345_RANGE_4_G); 
 displaySetRange(ADXL345_RANGE_2_G); 
 accel.setRange(ADXL345_RANGE_2_G); 
 accel.setDataRate(ADXL345_DATARATE_200_HZ); 
} 

void loop() 
{ 
 buttonState_1 = digitalRead(buttonPin_1); 
 buttonState_2 = digitalRead(buttonPin_2); 
 buttonState_3 = digitalRead(buttonPin_3); 

 if ((buttonState_1 == HIGH)) 
 { 
  state = 1; 
  digitalWrite(ledPin, HIGH); 
 } 

 else if ((buttonState_2 == HIGH)) 
 { 
  state = 2; 
  digitalWrite(ledPin, HIGH); 
 } 

 else if ((buttonState_3 == HIGH)) 
 { 
  state = 3; 
  digitalWrite(ledPin, HIGH); 
 } 

 else if ((buttonState_1 == LOW) && (buttonState_2 == LOW) && (buttonState_3 == LOW) ) 
 { 
  digitalWrite(ledPin, LOW); 
 } 
}

switch(state) { 

 case 1 : // manipulator 
 {
  if( (m[1] < 140)) 
  { 
   data.println(9); 
   Serial.println(9); 
   delay(50); 
  } 

  if( (m[4] <= 140) ) 
  { 
   data.println(10); 
   Serial.println(10); 
   delay(50); 
  }

  if( (m[2] <= 140) ) 
  { 
   data.println(11); 
   Serial.println(11); 
   delay(50); 
  } 

  if( (m[3] <= 140 ) ) 
  { 
   data.println(12); 
   Serial.println(12); 
   delay(50); 
  } 

  break; 
 } 

 case 2 : // camera 
 { 
  if( (m[4] <= 140) ) // Left 
  { 
   data.println(6); 
   delay(50); 
  } 

  if( (m[1] <= 130) ) // Centre 
  { 
   data.println(7); 
   delay(50); 
  } 

  if( (m[2] <= 145) ) // Right 
  { 
   data.println(8); 
   delay(50); 
  } 

  break; 
 } 

 case 3: // chassis 
 { 
  if( (m[1] < 135) && (m[2] > 180) && (m[4] > 180) ) // go forward 
  { 
   data.println(1); 
   Serial.println(1); 
   delay(50); 
  } 

  if( (m[2] <= 130) ) // go back 
  { 
   data.println(3); 
   delay(50); 
  } 

  if( (m[1] > 180 ) && (m[2] > 160) ) // stop 
  { 
   data.println(2); 
   delay(50); 
  } 

  if( (m[4] < 140)) 
  { 
   data.println(4); 
   delay(50); 
  } 

  if( (m[4] < 140) && (m[1] < 140) ) 
  { 
   data.println(5); 
   Serial.println(5); 
   delay(50); 
  } 

  break; 
 }   
} 

{
// Get the new sensor events 
 sensors_event_t event; 
 bmp.getEvent(&event); 

// Calibrate height readings to ground level 
 if (ground_level < 10) 
 { 
  delay(25); 
  //Trying to make the sensor output more stable, probably may be replaced with a kalman filter 
  ground_level1 = event.pressure; 
  delay(25); 
  ground_level2 = event.pressure; 
  delay(25); 
  ground_level3 = event.pressure; 
  delay(25); 
  ground_level4 = event.pressure; 
  delay(25); 
  ground_level5 = event.pressure; 
  delay(25); 
  ground_level6 = event.pressure; 
  delay(25); 
  ground_level7 = event.pressure; 
  delay(25); 
  ground_level8 = event.pressure; 
  delay(25); 
  ground_level9 = event.pressure; 
  delay(25); 
  ground_level10 = event.pressure; 
  ground_level = (ground_level1 + ground_level2 + ground_level3 + ground_level4) / 4; 
 } 

 // Display the results (barometric pressure is measured in hPa) 
 if (event.pressure) 
 { 
  // Trying to make the sensor output more stable, probably may be replaced with a kalman filter 
  pressure1 = event.pressure; 
  delay(25); 
  pressure2 = event.pressure; 
  delay(25); 
  pressure3 = event.pressure; 
  delay(25); 
  pressure4 = event.pressure; 
  delay(25); 
  pressure5 = event.pressure; 
  delay(25); 
  pressure6 = event.pressure; 
  delay(25); 
  pressure7 = event.pressure; 
  delay(25); 
  pressure8 = event.pressure; 
  delay(25); 
  pressure9 = event.pressure; 
  delay(25); 
  pressure10 = event.pressure; 

  // Display atmospheric pressue in hPa 
  pressure = ( pressure1 + pressure2 + pressure3 + pressure4 ) / 4;
  Serial.print(" Pressure: "); 
  Serial.print(pressure); 
  Serial.println(" hPa"); 

  // Display current temperature from the BMP085 
  bmp.getTemperature(&temperature); 
  Serial.print(" Temperature: "); 
  Serial.print(temperature); 
  Serial.println(" C"); 

// Heigth calculation 

    ((P0/P)^(1/5.257) - 1) * (T + 273.15) 
h = —------------------------------------ 
                  0.0065 

where: h - height (in meters) 
P0 - gorund level pressure (in hPa) 
P - atmospheric pressure (in hPa) 
T - temperature (in °C) // 

 float seaLevelPressure = ground_level; 
 Serial.print(" Altitude: "); 
 Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure, temperature)); 
 Serial.println(" m "); 
 } 

 else 
 { 
  Serial.println(" Sensor error "); 
 }  
}

/// GYRO CODE /// 

/// COMPASS CODE /// 

{
  // Tell the HMC5883 where to begin reading data 
 Wire.beginTransmission(address); 
 Wire.write(0x03); // select register 3, X MSB register 
 Wire.endTransmission(); 

 // Read data from each axis, 2 registers per axis 
 Wire.requestFrom(address, 6); 

 if ( 6 <= Wire.available() ) { 
  x = Wire.read()«8; // X msb 
  x |= Wire.read(); // X lsb 
  y = Wire.read()«8; // Y msb 
  y |= Wire.read(); // Y lsb 
  z = Wire.read()«8; // Z msb 
  z |= Wire.read(); // Z lsb 
 } 

 // Print out values of each axis 
 // New.... 
 titi = millis(); 
 dt = titi-toto; 
 toto = titi; 

 m[0] = analogRead(Pin_1); 
 m[1] = analogRead(Pin_2); 
 m[2] = analogRead(Pin_3); 
 m[3] = analogRead(Pin_4); 
 m[4] = analogRead(Pin_5); 
 m[5] = analogRead(Pin_6); 

 Serial.print(" Compass: x: "); 
 Serial.print(x); 
 Serial.print(" y: "); 
 Serial.print(y); 
 Serial.print(" z: "); 
 Serial.println(z); 
 Serial.println(""); 

 accel.getEvent(&event); 
 // Display the results (acceleration is measured in m/s^2) 
 data.print(event.acceleration.x); 
 data.print(" "); 
 data.print(event.acceleration.y); 
 data.print(" "); 
 data.print(event.acceleration.z); 
 data.print(" "); 

 gyro.read(); 
 data.print(((int)gyro.g.x)/100); 
 data.print(" "); 
 data.print(((int)gyro.g.y)/100); 
 data.print(" "); 
 data.print(((int)gyro.g.z)/100); 
 data.print(" "); 

 if( (m[1] < 120) )
 // go forward 
 { 
  data.println(1); 
  delay(50); 
 } 

 if( (m[2] < 140) ) // stop 
 { 
  data.println(3); 
  delay(50); 
 } 

 if( (m[1] > 150) && (m[2] > 150) ) // stop 
 { 
  data.println(2); 
  delay(50); 
 } 

 if(m[3] < 170) // go back 
 { 
  data.println(4); 
  delay(50); 
 } 

 data.print(" "); 
 data.print(m[3]); 
 data.print(" "); 
 data.print(m[2]); 
 data.print(" "); 
 data.print(m[1]); 
 data.print(" "); 
 data.print(m[4]); 
 data.println(" "); 
 data.print(m[5]); 
 data.println(" "); 

 Serial.print(" Time :"); 
 Serial.print(float(dt)/1000); 
 Serial.println('\n'); 
 delay(100); 
}