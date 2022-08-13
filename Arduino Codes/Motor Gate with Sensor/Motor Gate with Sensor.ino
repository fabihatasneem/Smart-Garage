/* LCD Module Part */
#include<LiquidCrystal.h>
const int rs = 12, en = 11;
const int d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* Servo Motor Part */
#include<Servo.h>
Servo servo;
const int servoPin = 8;

// IR sensor pins inside & outside of the gate
const int gateInPin = 13;
const int gateOutPin = 9;

#define TOTAL_SLOTS 1
int slotPinNumbers[] = {7};
int i;

void checkSlot(int slot)
{
  lcd.setCursor(slot/2, (slot%2)*11 + 1);

  /* Handling LCD accordingly */
  if(digitalRead(slotPinNumbers[slot]) == LOW)
  {
    lcd.clear();
    lcd.print("Slot " + String(slot+1) + ": Occ"); // Occ => Occupied
    delay(100);
  }
  else
  {
    lcd.clear();
    lcd.print("Slot " + String(slot+1) + ": Emp"); // Emp => Empty
    delay(100);  
  }  
}

void setup() {
  /* setting up pin modes as necessary */
  servo.attach(servoPin);
  pinMode(gateInPin, INPUT);
  pinMode(gateOutPin, INPUT);

  for(i=0; i<TOTAL_SLOTS; i++)
    pinMode(slotPinNumbers[i], INPUT); 

  lcd.begin(20, 4);
}

void loop() {
  // checking whether slot is occupied
  for(i=0; i<TOTAL_SLOTS; i++)
    checkSlot(i);

  // checking if either of the sensors near the gate have obstacles  
  if(digitalRead(gateInPin) == LOW || digitalRead(gateOutPin) == LOW)
  {
    servo.write(170); // lifting the gate up
    delay(5000); // giving 5 seconds time to escape 
  }

  servo.write(110); // lifting the gate down
  delay(50); // Idk what this delay does...should be okay if you remove it
}