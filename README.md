RTC RV-3028-C7 Arduino Library
========================================

![Real Time Clock](RV-3028-C7.png)

[*Application Manual*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf)

The RV-3028-C7 is an extremely precise, extremely low power, highly configurable RTC. Under ideal conditions it runs at approximately 40nA with +/-5ppm per year of deviation (+/- 160 seconds worst case per year).
This library was originally forked from the [Sparkfun RV-1805 library](https://github.com/sparkfun/SparkFun_RV-1805_Arduino_Library), and costumized and enhanced to the RV-3028-C7.

This library allows the user to:

* Set time using hard numbers or the BUILD_TIME from the Arduino compiler
* Read time
* Configure various aspects of the RTC including setting of alarms, countdown timers, periodic time update interrupts, trickle charging, power switchover mode and programmable clock output.

Examples are included to get you started (but still missing for CountdownTimer, PeriodicTimeUpdate Interrupt and Programmable Clock Output).

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 

Documentation
--------------
The library enables the following functions:

### General functions
Please call begin() sometime after initializing the I2C interface with Wire.begin().
###### `begin()`
###### `is12Hour()`
###### `isPM()`
###### `set12Hour()`
###### `set24Hour()`
###### `reset()`

<hr>

### Interrupt status
###### `status()`
###### `clearInterrupts()`

<hr>

### Set Time functions
###### `setTime(sec, min, hour, weekday, date, month, year);`
###### `setSeconds(value)`
###### `setMinutes(value)`
###### `setHours(value)`
###### `setWeekday(value)`
###### `setDate(value)`
###### `setMonth(value)`
###### `setYear(value)`
###### `setToCompilerTime()`

<hr>

### Get Time functions
Please call "updateTime()" before calling one of the other getTime functions.
###### `updateTime()`
###### `getSeconds()`
###### `getMinutes()`
###### `getHours()`
###### `getWeekday()`
###### `getDate()`
###### `getMonth()`
###### `getYear()`
###### `stringDateUSA()`
###### `stringDate()`
###### `stringTime()`
###### `stringTimeStamp()`

<hr>

### UNIX Time functions
Attention: UNIX Time and real time are INDEPENDENT!
###### `setUNIX(value)`
###### `getUNIX()`

<hr>

### Alarm Interrupt functions
###### `enableAlarmInterrupt(min, hour, date_or_weekday, bool setWeekdayAlarm_not_Date, mode, bool enable_clock_output = false)`
###### `disableAlarmInterrupt()`
###### `readAlarmInterruptFlag()`
###### `clearAlarmInterruptFlag()`
Set the alarm mode in the following way:  
0: When minutes, hours and weekday/date match (once per weekday/date)  
1: When hours and weekday/date match (once per weekday/date)  
2: When minutes and weekday/date match (once per hour per weekday/date)  
3: When weekday/date match (once per weekday/date)  
4: When hours and minutes match (once per day)  
5: When hours match (once per day)  
6: When minutes match (once per hour)  
7: All disabled – Default value  
If you want to set a weekday alarm (_setWeekdayAlarm_not_Date_ = true), set _date_or_weekday_ from 0 (Sunday) to 6 (Saturday).  
For further information about the alarm mode see [*Application Manual p. 68*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=68).

<hr>

### Countdown Timer Interrupt functions
Thanks [@JasonEdinburgh](https://github.com/JasonEdinburgh) for this enhancement.
###### `setTimer(bool timer_repeat, uint16_t timer_frequency, uint16_t timer_value, bool setInterrupt, bool start_timer, bool enable_clock_output = false)`
###### `enableTimer()`
###### `disableTimer()`
###### `enableTimerInterrupt()`
###### `disableTimerInterrupt()`
###### `readTimerInterruptFlag()`
###### `clearTimerInterruptFlag()`
_timer_repeat_  specifies either Single or Repeat Mode for the Periodic Countdown Timer.  
Setting of _timer_frequency_:
| _timer_frequency_ |        | error on first time | max. duration (_timer_value = 4095_) |
|:-----------------:|:------:|:-------------------:|:------------------------------------:|
| 4096 (default)    | 4096Hz | 122us               | 0.9998s                              |
| 64                | 64Hz   | 7.813ms             | 63.984s                              |
| 1                 | 1Hz    | 7.813ms             | 4095s                                |
| 60000             | 1/60Hz | 7.813ms             | 4095min                              |  

Countdown Period [s] = Timer Value / Timer Frequency  
See [*Application Manual p. 63*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=63) for more information.
<hr>

### Periodic Time Update Interrupt functions
Thanks [@JasonEdinburgh](https://github.com/JasonEdinburgh) for this enhancement.  
###### `enablePeriodicUpdateInterrupt(bool every_second, bool enable_clock_output = false)`
###### `disablePeriodicUpdateInterrupt()`
###### `readPeriodicUpdateInterruptFlag()`
###### `clearPeriodicUpdateInterruptFlag()`
_every_second_ specifies the interrupt to occur either every second or every minute.

<hr>

### Trickle Charge functions
###### `enableTrickleCharge(uint8_t tcr = TCR_15K)`
###### `disableTrickleCharge()`
###### `bool isTrickleChargeEnabled()`
At "enableTrickleCharge" you can choose the series resistor:  
TCR_3K for 3kOhm  
TCR_5K for 5kOhm  
TCR_9K for 9kOhm  
TCR_15K for 15kOhm  
See [*Application Manual p. 48*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48) for more information.

<hr>

### Backup Switchover Mode
###### `setBackupSwitchoverMode(mode)`
0 = Switchover disabled  
1 = Direct Switching Mode  
2 = Standby Mode  
3 = Level Switching Mode  
See [*Application Manual p. 45*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=45) for more information.

<hr>

### Programmable Clock Output

###### `enableClockOut(uint8_t freq)`
###### `enableInterruptControlledClockout(uint8_t freq)`
###### `disableClockOut()`
###### `readClockOutputInterruptFlag()`
###### `clearClockOutputInterruptFlag()`
Set Clockout Frequency _freq_ as follows:
| _freq_          | result                                        |
|-----------------|:---------------------------------------------:|
| FD_CLKOUT_32k   | 32.768 kHz                                    |
| FD_CLKOUT_8192  | 8192 Hz                                       |
| FD_CLKOUT_1024  | 1024 Hz                                       |
| FD_CLKOUT_64    | 64 Hz                                         |
| FD_CLKOUT_32    | 32 Hz                                         |
| FD_CLKOUT_1     | 1 Hz                                          |
| FD_CLKOUT_TIMER | Predefined periodic countdown timer interrupt |
| FD_CLKOUT_LOW   | CLKOUT = LOW                                  |  

See [*Application Manual p. 48*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf#page=48) for more information.
'enableInterruptControlledClockout' generally enables the Interrupt Controlled Clockout (required for triggering Clockout at Alarm, PeriodicUpdate and CountdownTimer Interrupts).


License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact constantinkoch@outlook.com.

Distributed as-is; no warranty is given.
