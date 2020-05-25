/*
  Trickle Charge Configuration of RV-3028-C7 Real Time Clock
  By: Constantin Koch
  Date: 7/31/2019
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting my work? Give me a star!
  https://github.com/constiko/RV-3028_C7-Arduino_Library

  This example shows how to set the Trickle Charge Configuration of RTC RV-3028-C7.
  Open the serial monitor at 115200 baud.
*/

#include <RV-3028-C7.h>

RV3028 rtc;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Trickle Charging - RTC Example");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  }
  else
    Serial.println("RTC online!");
    Serial.println();

  //Trickle Charger
  rtc.disableTrickleCharge();         // disable trickle charger
  Serial.print("Config EEPROM 0x37 before:\t0b");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37), BIN);
 

  rtc.enableTrickleCharge(TCR_3K);    //series resistor 3kOhm
  //rtc.enableTrickleCharge(TCR_5K);  //series resistor 5kOhm
  //rtc.enableTrickleCharge(TCR_9K);  //series resistor 9kOhm
  //rtc.enableTrickleCharge(TCR_15K); //series resistor 15kOhm
  //rtc.disableTrickleCharge();       //Trickle Charger disabled

  Serial.print("Config EEPROM 0x37 after:\t0b");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37), BIN);
  Serial.println("\t\t(1 = ON) TCE_bit    ^\t^^ TCR_bits (00 = 3k series resistor)");

  //For more information see https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48
}

void loop() {

}
