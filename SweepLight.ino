/*  SweepLight
*   Arduino firmware for detecting direction of light source.
*   Device has servo motor with light detector. Servo motor is rotating and light detector
*   is measuring light power of light source (analog value). Finally, servo motor is moved
*   to position where light intensity is the highest.
*   Credits: Drago Trebežnik
*/ 

#include <Servo.h> 

Servo myservo;          // create servo object to control a servo

int sensor_pin = A3;    // light sensor is connected to A3
int servo_pin = 9;      // servo motor is connected to D9

int curr_position = 0;  // current position of the light sensor
int top_position = 0;   // position of the light sensor where light intensity is the highest

int curr_light = 0;     // current light intensity
int top_light = 0;      // maximum light intensity
 
void setup() 
{ 
  Serial.begin(9600);                                 // initialize serial port (9600 bps)
  myservo.attach(servo_pin);                          // servo motor connect
  
  for (curr_position = 0; curr_position <= 140; curr_position += 1)  // moving servo motor from 0 to 140 degree for one step at a time
  {
    myservo.write(curr_position);                     // move servo motor to desired position
    delay(15);                                        // servo motor needs 15 ms for a movement
    
    curr_light = analogRead(sensor_pin);              // read current light intensity
    
    if (curr_light > top_light)                       // find out if current light intensity is higher than previous value
    {
      top_light = curr_light;
      top_position = curr_position;
      }
  } 
  
  delay(500);                       // wait for 0.5 seconds
  myservo.write(0);                 // start moving servo motor from the beginning
  delay(1000);                      // wait for 1 second
  myservo.write(top_position);      // move servo motor to position of most intensive light
      
} 
 
void loop() 
{ 
  // In loop we are only showing the current value of light intensity:
  curr_light = analogRead(sensor_pin);
  Serial.println(curr_light);
  delay(300); 
} 

