/*
  Interrupt Time Stamp Configuration of RV-3028-C7 Real Time Clock
  By: Paolo Salvagione
  Date: 5/17/2020
  License: This code is public domain.

  This example shows how to set the Interrupt Time Stamp Configuration of RTC RV-3028-C7.
  Open the serial monitor at 115200 baud.

    Assumptions,
  1) You've already set the RTC time. See the SetPrint_Time example.
  2) You have a backup battery, or capacitor, attached to the RTC's Vbackup pin. See datasheet.
  3) You're keeping the backup battery, or capacitor, topped off with the trickle charge feature
  of the RTC. See Trickle_Charging example.
  4) The Vbackup supply, a battery or a capacitor, has enougth power to keep the RTC running 
  during power interrupt event.
  5) 

*/

#include <RV-3028-C7.h>

// Using GPIO pins to power RTC
const uint8_t posPin = 20;
const uint8_t gndPin = 21;


RV3028 rtc;

void setup() {

  // Turn on RTC
  pinMode(posPin, OUTPUT);
  digitalWrite(posPin, HIGH);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);

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
  Serial.println("\t\t(1 = ON) TCE_bit    ^\t^^ TCR_bits (00 = 3k series resistor)");




//rtc.enableInterruptTimeStamp(backupBattery, lastEvent, clockOff); 

  if (rtc.isInterruptTimeStampEnabled() == false) {
    rtc.enableInterruptTimeStamp(backupBattery, lastEvent, clockOff); 
    Serial.println("Enabling interrutp time stamp function");
    Serial.print(rtc.isInterruptTimeStampEnabled());
    Serial.println(" TSE setting.");
  }

  


  //For more information see https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48
}

void loop() {

  if (rtc.isTrickleChargeEnabled() == false)
  {
    rtc.enableTrickleCharge(TCR_3K);
    Serial.println("\n\nEnabled trickle charge.\n");
  }

  if (rtc.isInterruptTimeStampEnabled() == false) {
    rtc.enableInterruptTimeStamp(backupBattery, lastEvent, clockOff); 
    Serial.println("Enabled interrupt time stamp.");
    Serial.print(rtc.isInterruptTimeStampEnabled());
    Serial.println(" TSE setting.");
  }


    //PRINT TIME
  if (rtc.updateTime() == false) //Updates the time variables from RTC.
  {
    Serial.println("RTC failed to update.");
    while (rtc.updateTime() == false);
  } else {
    static String lastTime = "";
    String currentTime = rtc.stringTimeStamp();
    if (currentTime != lastTime) {
      Serial.println(currentTime);
      lastTime = currentTime;
    }
  }


  if (rtc.readInterruptTimeStamp() == false) //Updates the time stamp variables from RTC.
  {
    Serial.println("RTC failed to update.");

  } else {
    static String lastInterruptTime = "";
    String currentInterruptTime = rtc.stringTimeStamp();
    if (currentInterruptTime != lastInterruptTime) {
      Serial.println();
      Serial.print(currentInterruptTime);
      Serial.println(" <<< interrupt time stamp.");
      lastInterruptTime = currentInterruptTime;
    }
    
  }


} // end loop()