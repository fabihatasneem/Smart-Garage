#include <SoftwareSerial.h>
SoftwareSerial softSerial1(0, 1);
SoftwareSerial softSerial2(4, 5);

#define TOTAL_SLOTS 2
int slotPinNumbers[] = {7, 8};

void setup() 
{
  softSerial1.begin(9600);
  softSerial2.begin(9600);
  /* setting up pin modes as necessary */
  for(int i=0; i<TOTAL_SLOTS; i++)
    pinMode(slotPinNumbers[i], INPUT); 
}

void loop() 
{
  String slotString;
  int count = 0;
  // checking whether slot is occupied
  for(int i=0; i<TOTAL_SLOTS; i++)
  {
    if(digitalRead(slotPinNumbers[i]) == LOW)
    {
      slotString += "1";
      count++;
    }
    else
      slotString += "0";
  }

  softSerial1.print("Arduino 3: " + slotString); // offset = 11
  //if(count == TOTAL_SLOTS)
  softSerial2.print("Arduino 3: " + String(count == TOTAL_SLOTS)); 
  //delay(3000);
}