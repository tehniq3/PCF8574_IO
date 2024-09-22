/*
 * based on https://github.com/xreef/PCF8574_library
 * https://www.hackster.io/mdraber/practical-guide-to-pcf8574-adding-extra-pins-for-arduino-4095f2
 * Nicu FLORICA (niq_ro) tested 2 buttons and 2 outputs with "stadard" i2c module for LCD1602
 * v.1 - one temporary button & one output
 * v.2 - 2 temporary buttons & 2 outputs
 * v.3 - added troggle output state
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


byte staresw1 = 1;  // intial state of 1st output
byte staresw2 = 1;  // intial state of 2nd output
int SWreading1;         // the current reading from the input pin
int SWreading2;         // the current reading from the input pin
unsigned long SWtime1 = 0;  // the time of the push the 1st switch 
unsigned long SWtime2 = 0;  // the time of the push the 2nd switch
int pauzapcf = 250;
unsigned long PCFdelay = 1500; // ignore time for push the buttons

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
  int SWreading1 = pcf8574.digitalRead(sw1);  // read the state of the switch into a local variable:
  int SWreading2 = pcf8574.digitalRead(sw2);  // read the state of the switch into a local variable:
 
if ((SWreading1 == 0) and (millis() - SWtime1 > PCFdelay))       
  {
     staresw1 = staresw1 + 1;
     Serial.println("SW1 was pressed");
     SWtime1 = millis();  // reset the debouncing timer
     delay(pauzapcf);
  }

  if ((SWreading2 == 0) and (millis() - SWtime2 > PCFdelay))
  {
     staresw2 = staresw2 + 1;
     Serial.println("SW2 was pressed");
     SWtime2 = millis();  // reset the debouncing timer
     delay(pauzapcf);
  }

pcf8574.digitalWrite(led1, staresw1%2);
pcf8574.digitalWrite(led2, staresw2%2);

}  // end main loop
