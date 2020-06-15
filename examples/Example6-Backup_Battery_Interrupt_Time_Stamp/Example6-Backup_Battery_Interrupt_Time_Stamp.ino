/*
  Battery Backup Interrupt Time Stamp Configuration of RV-3028-C7 Real Time Clock
  By: Paolo Salvagione
  Date: 6/15/2020
  License: This code is public domain.

  This example shows how to set the Battery Backup Interrupt Time Stamp 
  Configuration of RTC RV-3028-C7. Open the serial monitor at 115200 baud.

  For more information see 
  https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf

  Assumptions,
  1) You've already set the RTC time. See the SetPrint_Time example.
  2) You have a backup battery, or capacitor, attached to the RTC's Vbackup pin. See datasheet.
  3) You're keeping the backup battery, or capacitor, topped off with the trickle charge feature
  of the RTC. See Trickle_Charging example.
  4) The Vbackup supply, a battery or a capacitor, has enougth power to keep the RTC alive during 
  interrupt event.
  5) That you will unplug/plug the USB cable powering your microcontroller/Arduino to simulate 
  loss of power.

  Known Issues,
  1) Unplugging/plugging the RTC directly will bounce and the time stamp counter will count
  each bounce as an event.
  2) Default call to rtc.begin disables trick charge settings. 
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
    Serial.println("RTC online!");
  }
  
  // Enable Trickle Charger, see Trickle Charging example for complete list of settings.
  rtc.enableTrickleCharge(TCR_3K);   //series resistor 3kOhm

  // Time Stamp Interrupt settings
  if (rtc.isInterruptTimeStampEnabled() == false) // allows settings to persist through reboot.
  {
    rtc.enableInterruptTimeStamp(backupBattery, lastEvent, clockOff); 
    //rtc.enableInterruptTimeStamp(backupBattery, firstEvent, clockOff);
  }

  Serial.println("Unplug/plug the USB cable to simulate loss of power.\n");

} // end setup()

void loop() {
  // Print time stamp register
  if (rtc.readInterruptTimeStamp() == false) 
  {
    Serial.println("RTC failed to update.");
    while (rtc.readInterruptTimeStamp() == false);
  } 
  else if (rtc.readNumberOfInterrupts() !=0)
  {
    static String lastInterruptTime = "";
    String currentInterruptTime = rtc.stringTimeStamp();
    if (currentInterruptTime != lastInterruptTime) 
    {
      Serial.print(currentInterruptTime);
      Serial.print(" <<< interrupt time stamp, interrupted ");
      Serial.print(rtc.readNumberOfInterrupts());
      Serial.println(" times.");
      lastInterruptTime = currentInterruptTime;
    }    
  }

  // Print time
  if (rtc.updateTime() == false) //Updates the time variables from RTC.
  {
    Serial.println("RTC failed to update.");
    while (rtc.updateTime() == false);
  } 
  else 
  {
    static String lastTime = "";
    String currentTime = rtc.stringTimeStamp();
    if (currentTime != lastTime) {
      Serial.println(currentTime);
      lastTime = currentTime;
    }
  }

  // Change time stamp register settings
  if (Serial.available()) {
    switch (Serial.read()) {
      case 'c':
        rtc.clearTimeStampRegister();
        Serial.println("Time stamp register cleared.");
        break;
      case 'f':
        rtc.enableInterruptTimeStamp(backupBattery, firstEvent, clockOff);
        Serial.println("Time stamp register cleared and set to store first interrupt time stamp.");
        break;
      case 'l':
        rtc.enableInterruptTimeStamp(backupBattery, lastEvent, clockOff);
        Serial.println("Time stamp register cleared and set to store last interrupt time stamp.");
        break;
      case '\n':
        // trap returns 
        break;
      default:
        Serial.println("---------------------------------------------");
        Serial.println("c - Clears the Time Stamp Register");
        Serial.println("f - Stores first event in time stamp register");
        Serial.println("l - Stores last event in time stamp register");
        Serial.println("---------------------------------------------");
        break;
      }
    } 
} // end loop()