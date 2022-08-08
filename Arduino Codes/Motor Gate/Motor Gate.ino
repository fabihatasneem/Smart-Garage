#include<Servo.h>
Servo servo;
const int servoPin = 8;
const int gateInPin = 13;
const int gateOutPin = 9;
int i;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  pinMode(gateInPin, INPUT);
  pinMode(gateOutPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(gateInPin) == LOW || digitalRead(gateOutPin) == LOW)
  {
    servo.write(170);
    delay(5000);
  }

  servo.write(110);
  delay(500);
}
