#include <SoftwareSerial.h>
SoftwareSerial softSerial3(4, 5);

/* Servo Motor Part */
#include<Servo.h>
Servo servo;
const int servoPin = 8;

// IR sensor pins inside & outside of the gate
const int gateInPin = 13;
const int gateOutPin = 9;

void setup() 
{
  /* setting up pin modes as necessary */
  softSerial3.begin(9600);
  servo.attach(servoPin);
  pinMode(gateInPin, INPUT);
  pinMode(gateOutPin, INPUT);
}

void loop() 
{
  // checking if either of the sensors near the gate have obstacles  
  if(digitalRead(gateInPin) == LOW || digitalRead(gateOutPin) == LOW)
  {
    servo.write(170); // lifting the gate up
    delay(5000); // giving 5 seconds time to escape 
  }

  servo.write(110); // lifting the gate down

  // if(softSerial3.available())
  // {
  //   String slotFullStatus = softSerial3.readString().substring(11);
  //   if(slotFullStatus == "1")
  //     delay(15000);
  // }
}