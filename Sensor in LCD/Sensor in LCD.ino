#include<LiquidCrystal.h>
const int rs = 12, en = 11;
const int d4 = 5, d5 = 4, d6 = 3, d7 = 2;

const int inputPin = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(inputPin, INPUT);
  // put your setup code here, to run once:
  lcd.begin(20, 4);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  if(digitalRead(inputPin) == LOW)
  {
    lcd.clear();
    lcd.print("Slot occupied");
    delay(10);
  }
  else
  {
    lcd.clear();
    lcd.print("Slot empty");
    delay(10);  
  }
}
