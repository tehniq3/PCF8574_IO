/*
 * based on https://github.com/xreef/PCF8574_library
 * https://www.hackster.io/mdraber/practical-guide-to-pcf8574-adding-extra-pins-for-arduino-4095f2
 * Nicu FLORICA (niq_ro) tested 1 button and 1 output with "stadard" i2c module for LCD1602
 */

#include "Arduino.h"
#include "PCF8574.h"

#define sw P0
#define led P7

// Set i2c HEX address
PCF8574 pcf8574(0x27);
unsigned long timeElapsed;

void setup(){
 Serial.begin(9600);

  pcf8574.pinMode(sw, INPUT_PULLUP);
  pcf8574.pinMode(led, OUTPUT);

   if(pcf8574.begin())
     Serial.println("OK");
     else Serial.println("Failed");

}

void loop(){
  uint8_t val = pcf8574.digitalRead(sw);            // Read the value of pin P0        
  if (val == HIGH)  pcf8574.digitalWrite(led, HIGH); // If Button is Pressed
  else
    { 
     pcf8574.digitalWrite(led, LOW);  // When Button is Released
     Serial.println("SW was pressed");
    }
  delay(50);
}
