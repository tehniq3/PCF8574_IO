/*
 * based on https://github.com/xreef/PCF8574_library
 * https://www.hackster.io/mdraber/practical-guide-to-pcf8574-adding-extra-pins-for-arduino-4095f2
 * Nicu FLORICA (niq_ro) tested 2 buttons and 2 outputs with "stadard" i2c module for LCD1602
 */

#include "Arduino.h"
#include "PCF8574.h"

#define sw1 1
#define sw2 0
#define led1 6
#define led2 7

// Set i2c HEX address
PCF8574 pcf8574(0x27);
unsigned long timeElapsed;

void setup(){
 Serial.begin(9600);

  pcf8574.pinMode(sw1, INPUT_PULLUP);
  pcf8574.pinMode(sw2, INPUT_PULLUP);
  pcf8574.pinMode(led1, OUTPUT);
  pcf8574.pinMode(led2, OUTPUT);
 
   if(pcf8574.begin())
     Serial.println("OK");
     else Serial.println("Failed");
}

void loop(){
  uint8_t val1 = pcf8574.digitalRead(sw1);            // Read the value of pin P0 
  uint8_t val2 = pcf8574.digitalRead(sw2);            // Read the value of pin P1        
  if (val1 == HIGH)  pcf8574.digitalWrite(led1, HIGH); // If Button is Pressed
  else
    { 
     pcf8574.digitalWrite(led1, LOW);  // When Button is Released
     Serial.println("SW1 was pressed");
    }
       
  if (val2 == HIGH)  pcf8574.digitalWrite(led2, HIGH); // If Button is Pressed
  else
    { 
     pcf8574.digitalWrite(led2, LOW);  // When Button is Released
     Serial.println("SW2 was pressed");
    }

  delay(50);
}
