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

void loop() 
{ 
buttonState_1 = digitalRead(buttonPin_1); 
buttonState_2 = digitalRead(buttonPin_2); 
buttonState_3 = digitalRead(buttonPin_3); 

if ((buttonState_1 == HIGH)) 
{ 
state=1; 
digitalWrite(ledPin, HIGH); 
} 

else if ((buttonState_2 == HIGH)) 
{ 
state=2; 
digitalWrite(ledPin, HIGH); 
} 

else if ((buttonState_3 == HIGH)) 
{ 
state=3; 
digitalWrite(ledPin, HIGH); 
} 

else if ((buttonState_1 == LOW) && (buttonState_2 == LOW) && (buttonState_3 == LOW) ) 
{ 
digitalWrite(ledPin, LOW); 
} 
}

switch(state) { 
case 3:  
{ 
if( (m[1] <135) && (m[2] >180) && (m[4] >180) ) 
{ 
data.println(1); 
Serial.println(1); 
delay(50); 
} 

if( (m[2] <= 130) ) 
{ 
data.println(3); 
delay(50); 
} 

if( (m[1] > 180 ) && (m[2] > 160) ) 
{ 
data.println(2); 
delay(50); 
} 

if( (m[4]<140)) 
{ 
data.println(4); 
delay(50); 
} 

if( (m[4]<140) && (m[1]<140) ) 
{ 
data.println(5); 
Serial.println(5); 
delay(50); 
} 
break; 
} 

case 2 :  
{
if( (m[4] <= 140) ) 
{ 
data.println(6); 
delay(50); 
} 

if( (m[1] <= 130) ) 
{ 
data.println(7); 
delay(50); 
} 

if( (m[2] <= 145) ) 
{ 
data.println(8); 
delay(50); 
} 
break; 
} 

case 1 : 
{ 
if( (m[1] <140)) 
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

if( (m[3]<=140 ) ) 
{ 
data.println(12); 
Serial.println(12); 
delay(50); 
} 
break; 
} 
} 

sensors_event_t event; 
bmp.getEvent(&event); 

if (ground_level<10) 
{ 
delay(25); 
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


if (event.pressure) 
{ 
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

pressure = ( pressure1 + pressure2 + pressure3 + pressure4 ) / 4; 
 
float seaLevelPressure = ground_level; 
} 
else 
{ 
Serial.println("Sensor error"); 
} 