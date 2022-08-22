#include <SoftwareSerial.h>
SoftwareSerial softSerial3(0, 1);
 
/* LCD Module Part */
#include<LiquidCrystal.h>
const int rs = 6, en = 7;
const int d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
#include "MyClass.h"
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
int totalRfid = 4;
MyClass* allRfid[] = { new MyClass("C0 B6 0B 32"), new MyClass("59 D6 A0 D5"), new MyClass("C3 75 56 40"), new MyClass("59 EB B0 D5") };
MyClass* temp;
double billPerSec = 10;
 
void showSlot(String slotString)
{
  lcd.clear();
  for(int slot=0; slot<slotString.length(); slot++)
  {
    lcd.setCursor(slot/2, (slot%2)*11 + 1);
    if(slotString[slot] == '1')
    {
      lcd.print("Slot " + String(slot+1) + ": Occ"); // Occ => Occupied
      Serial.println("Slot " + String(slot+1) + ": Occ");
      delay(100);      
    }
    else
    {
      lcd.print("Slot " + String(slot+1) + ": Emp"); // Emp => Empty
      Serial.println("Slot " + String(slot+1) + ": Emp");
      delay(100);
    }
  }
}
 
void setup()
{
  softSerial3.begin(9600);
  Serial.begin(9600);
  Serial.println("Mao");
  /* setting up pin modes as necessary */
  lcd.begin(20, 4);
 
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}
 
void loop()
{
  if(softSerial3.available())
  {
    String temp = softSerial3.readString();
    //Serial.println(temp);
    String slotString = temp.substring(11);
    //Serial.println(slotString);
    showSlot(slotString);
  }
 
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
    return;
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
    return;
  //Show UID on serial monitor
  Serial.print("UID tag: ");
  String content;
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  Serial.println(content.substring(1));
 
  for(int i=0; i<totalRfid; i++)
  {
    temp = allRfid[i];
    if(content.substring(1) != temp->getRfid())
        continue;
       
    if(temp->isActive())
    {
      long startTime = temp->getStartTime();
      long endTime = millis();
      double totalTime = (endTime-startTime)/1000.0;
      double bill = totalTime*billPerSec;
      Serial.println(totalTime);
      Serial.println(bill);
      temp->setActive(false);
    }    
    else
    {
      temp->setStartTime(millis());
      temp->setActive(true);
    }
    delay(3000);
    break;
  }
}