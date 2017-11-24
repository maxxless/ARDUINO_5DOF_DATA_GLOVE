#include <SoftwareSerial.h> 
#include <Wire.h> 
#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP085_U.h> 
#include <Adafruit_ADXL345_U.h> 
#include <L3G4200D.h> 
#define address 0x1E 
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

int Pin_1 = A0; 
int Pin_2 = A1; 
int Pin_3 = A3; 
int Pin_4 = A4; 
int Pin_5= A5; 
int Pin_6= A2; 
int m [5]; 

float temperature; 
int x,y,z;

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
int state=0; 

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085); 
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); 

SoftwareSerial data(9, 10); 

void setup() 
{ 

Serial.begin(9600); 
data.begin(9600); 
Wire.begin(); 
gyro.enableDefault(); 
Wire.beginTransmission(address); 
Wire.write(0x02);  
Wire.write(0x00);
Wire.endTransmission(); 


pinMode(ledPin, OUTPUT); 
pinMode(buttonPin_1, INPUT); 
pinMode(buttonPin_2, INPUT); 
pinMode(buttonPin_3, INPUT); 

if(!bmp.begin()) 
{ 
Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!"); 
while(1); 
} 
if(!accel.begin()) 
{ 
Serial.println("Ooops, no ADXL345 detected ... Check your wiring!"); 
while(1); 
} 
accel.setRange(ADXL345_RANGE_2_G); 
accel.setDataRate(ADXL345_DATARATE_200_HZ); 
} 