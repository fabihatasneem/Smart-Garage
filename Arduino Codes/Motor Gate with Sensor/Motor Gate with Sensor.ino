#include<LiquidCrystal.h>
const int rs = 12, en = 11;
const int d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include<Servo.h>
Servo servo;
const int servoPin = 8;
const int gateInPin = 13;
const int gateOutPin = 9;

#define TOTAL_SLOTS 1

int slots[] = {7};
int i;

void checkSlot(int slot)
{
  lcd.setCursor(slot/2, (slot%2)*11 + 1);
  //lcd.print("Hello World");
  if(digitalRead(slots[slot]) == LOW)
  {
    lcd.clear();
    lcd.print("Slot " + String(slot+1) + ": Occ");
    delay(100);
  }
  else
  {
    lcd.clear();
    lcd.print("Slot " + String(slot+1) + ": Emp");
    delay(100);  
  }  
}

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
  pinMode(gateInPin, INPUT);
  pinMode(gateOutPin, INPUT);

  //for(i=0; i<TOTAL_SLOTS; i++)
    pinMode(slots[0], INPUT); 

  lcd.begin(20, 4);
}

void loop() {
  // put your main code here, to run repeatedly:
  //for(i=0; i<TOTAL_SLOTS; i++)
    checkSlot(0);

  if(digitalRead(gateInPin) == LOW || digitalRead(gateOutPin) == LOW)
  {
    servo.write(170);
    delay(5000);
  }

  servo.write(110);
  delay(50);
}
