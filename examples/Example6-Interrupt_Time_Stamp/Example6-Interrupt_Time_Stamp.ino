/*
  Interrupt Time Stamp Configuration of RV-3028-C7 Real Time Clock
  By: Paolo Salvagione
  Date: 5/17/2020
  License: This code is public domain.

  This example shows how to set the Interrupt Time Stamp Configuration of RTC RV-3028-C7.
  Open the serial monitor at 115200 baud.
*/

#include <RV-3028-C7.h>

RV3028 rtc;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("Backup Battery Interrupt Time Stamp - RTC Example");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  } else {
    Serial.println("RTC online!\n");
  }
  

  //Trickle Charger
  Serial.print("Config EEPROM 0x37 before:\t0b");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37), BIN);
  rtc.enableTrickleCharge(TCR_3K);   //series resistor 3kOhm
  //rtc.enableTrickleCharge(TCR_5K); //series resistor 5kOhm
  //rtc.enableTrickleCharge(TCR_9K); //series resistor 9kOhm
  //rtc.enableTrickleCharge(TCR_15K); //series resistor 15kOhm
  //rtc.disableTrickleCharge(); //Trickle Charger disabled

  Serial.print("Config EEPROM 0x37 after:\t0b");
  Serial.println(rtc.readConfigEEPROM_RAMmirror(0x37), BIN);



  Serial.print(rtc.getInterruptTimeStampSetting());
  Serial.println(" TSE setting.");

//rtc.enableInterruptTimeStamp(backupBattery, lastEvent, clockOff); 

  if (rtc.getInterruptTimeStampSetting() == false) {
    rtc.enableInterruptTimeStamp(backupBattery, lastEvent, clockOff); 
    Serial.println("Enabling interrutp time stamp function");
    Serial.print(rtc.getInterruptTimeStampSetting());
    Serial.println(" TSE setting.");
  }

  


  //For more information see https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48
}

void loop() {


  if (rtc.readInterruptTimeStamp() == false) //Updates the time variables from RTC
  {
    Serial.println("RTC failed to update");
  } else {
    static String lastInterruptTime = "";
    String currentInterruptTime = rtc.stringTimeStamp();
    if (currentInterruptTime != lastInterruptTime) {
      Serial.print(currentInterruptTime);
      Serial.println(" interrupt time stamp.");
      lastInterruptTime = currentInterruptTime;
    }
    
  }

    //PRINT TIME
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  } else {
    static String lastTime = "";
    String currentTime = rtc.stringTimeStamp();
    if (currentTime != lastTime) {
      Serial.print(currentTime);
      Serial.println(" current time.");
      lastTime = currentTime;
    }
  }
} // end loop()