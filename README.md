# ATtiny_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/ATtiny_PWM.svg?)](https://www.ardu-badge.com/ATtiny_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ATtiny_PWM.svg)](https://github.com/khoih-prog/ATtiny_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ATtiny_PWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ATtiny_PWM.svg)](http://github.com/khoih-prog/ATtiny_PWM/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Important Note for Arduino IDE](#Important-Note-for-Arduino-IDE)
* [Why do we need this ATtiny_PWM library](#why-do-we-need-this-ATtiny_PWM-library)
  * [Features](#features)
  * [Why using hardware-based PWM is better](#why-using-hardware-based-pwm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [More useful Information](#more-useful-information)
  * [1. Documents](#1-documents)
  * [2. Timer TCB0-TCB1](#2-timer-tcb0-tcb1)
* [Usage](#usage)
  * [1. Create PWM Instance with Pin, Frequency, dutycycle](#1-create-pwm-instance-with-pin-frequency-dutycycle)
  * [2. Initialize PWM Instance](#2-Initialize-PWM-Instance)
  * [3. Set or change PWM frequency or dutyCycle](#3-set-or-change-PWM-frequency-or-dutyCycle)
  * [4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation](#4-Set-or-change-PWM-frequency-and-dutyCycle-manually-and-efficiently-in-waveform-creation)
* [Examples](#examples)
  * [ 1. PWM_Basic](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Basic)
  * [ 2. PWM_DynamicDutyCycle](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicDutyCycle) 
  * [ 3. PWM_DynamicDutyCycle_Int](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicDutyCycle_Int)
  * [ 4. PWM_DynamicFreq](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicFreq)
  * [ 5. PWM_Multi](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Multi)
  * [ 6. PWM_MultiChannel](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_MultiChannel)
  * [ 7. PWM_Waveform](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Waveform)
  * [ 8. PWM_StepperControl](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_StepperControl) **New**
  * [ 9. PWM_manual](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_manual) **New**
  * [10. PWM_SpeedTest](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_SpeedTest) **New**
* [Example PWM_Multi](#example-PWM_Multi)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. PWM_DynamicDutyCycle on AVR_ATtiny3217](#1-PWM_DynamicDutyCycle-on-AVR_ATtiny3217)
  * [2. PWM_Multi on AVR_ATtiny3217](#2-PWM_Multi-using-QuadTimers-on-AVR_ATtiny3217)
  * [3. PWM_DynamicFreq on AVR_ATtiny3217](#3-PWM_DynamicFreq-on-AVR_ATtiny3217)
  * [4. PWM_Waveform on AVR_ATtiny3217](#4-PWM_Waveform-on-AVR_ATtiny3217)
  * [5. PWM_manual on AVR_ATtiny3217](#5-PWM_manual-on-AVR_ATtiny3217)
  * [6. PWM_SpeedTest on AVR_ATtiny3217](#6-PWM_SpeedTest-on-AVR_ATtiny3217)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Note for Arduino IDE

With some Arduino IDE versions, such as v1.8.19, upload directly via USB to some boards, such as `AVR_CuriosityNano3217` can't be done without `unknown-to-me` fix. We'll get the following error when uploading

```
avrdude: Version 6.3-20201216
         Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
         Copyright (c) 2007-2014 Joerg Wunsch

         System wide configuration file is "/home/kh/.arduino15/packages/megaTinyCore/hardware/megaavr/2.5.11/avrdude.conf"
         User configuration file is "/home/kh/.avrduderc"
         User configuration file does not exist or is not a regular file, skipping

         Using Port                    : usb
         Using Programmer              : curiosity_updi
avrdude: usbdev_open(): Found nEDBG CMSIS-DAP, serno: MCHP3333021800000998
avrdude: usbdev_open(): WARNING: failed to set configuration 1: Device or resource busy
avrdude: Found CMSIS-DAP compliant device, using EDBG protocol
avrdude: usbdev_send(): wrote -5 out of 912 bytes, err = Input/output error
avrdude: jtag3_edbg_prepare(): failed to send command to serial port

avrdude done.  Thank you.

the selected serial port 
 does not exist or your board is not connected
```

We can use drag-and-drop method to `drag-and-drop` the compiled **hex** file to `CURIOSITY` virtual drive. 

If `success`, The LED blinks **slowly** for 2 sec, or **rapidly** for 2 sec if `failure`


For example, to run [Change_Interval example](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/Change_Interval), use Arduino IDE to compile, and get the `Change_Interval.ino.hex` file. For Ubuntu Linux, the file is stored in directory `/tmp/arduino_build_xxxxxx`


<p align="center">
    <img src="https://github.com/khoih-prog/ATtiny_PWM/raw/main/pics/Change_Interval.png">
</p>


After drag-and-drop the `Change_Interval.ino.hex` into `CURIOSITY` virtual drive, the code will run immediately if successfully loaded (LED blinks **slowly**)


<p align="center">
    <img src="https://github.com/khoih-prog/ATtiny_PWM/raw/main/pics/CURIOSITY_drive.png">
</p>


---
---

### Why do we need this [ATtiny_PWM library](https://github.com/khoih-prog/ATtiny_PWM)

### Features

This hardware-based PWM library, a wrapper and enhancement around `megaTinyCore analogWrite()` code, enables you to use Hardware-PWM on **Arduino AVR ATtiny-based boards (ATtiny3217, etc.)** using [**megaTinyCore**](https://github.com/SpenceKonde/megaTinyCore), to create and output PWM. These purely hardware-based PWM channels can generate very high PWM frequencies, depending on CPU clock and acceptable accuracy. The maximum and default resolution is **8-bit** resolution.

This library is using the **same or similar functions** as other FastPWM libraries, as follows, to enable you to **port your PWM code easily between platforms**

 1. [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM)
 2. [**AVR_PWM**](https://github.com/khoih-prog/AVR_PWM)
 3. [**megaAVR_PWM**](https://github.com/khoih-prog/megaAVR_PWM)
 4. [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM)
 5. [**SAMD_PWM**](https://github.com/khoih-prog/SAMD_PWM)
 6. [**SAMDUE_PWM**](https://github.com/khoih-prog/SAMDUE_PWM)
 7. [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM)
 8. [**Teensy_PWM**](https://github.com/khoih-prog/Teensy_PWM)
 9. [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM)
10. [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM)
11. [**Portenta_H7_PWM**](https://github.com/khoih-prog/Portenta_H7_PWM)
12. [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM)
13. [**nRF52_MBED_PWM**](https://github.com/khoih-prog/nRF52_MBED_PWM)
14. [**STM32_PWM**](https://github.com/khoih-prog/STM32_PWM)


---

The most important feature is they're purely hardware-based PWM channels. Therefore, their operations are **not blocked by bad-behaving software functions / tasks**.

This important feature is absolutely necessary for mission-critical tasks. These hardware PWM-channels, still work even if other software functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software timers using `millis()` or `micros()`. That's necessary if you need to control external systems (Servo, etc.) requiring better accuracy.

New efficient `setPWM_manual()` function enables waveform creation using PWM.

The [**PWM_Multi**](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Multi) example will demonstrate the usage of multichannel PWM using multiple Hardware-PWM blocks (Timer & Channel). The 2 independent Hardware-PWM channels are used **to control 2 different PWM outputs**, with totally independent frequencies and dutycycles on `ATtiny-based boards`.

Being hardware-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

---

### Why using hardware-based PWM is better

Imagine you have a system with a **mission-critical** function, controlling a robot or doing something much more important. You normally use a software timer to poll, or even place the function in `loop()`. But what if another function is **blocking** the `loop()` or `setup()`.

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use `hardware-based PWM`.

These hardware-based PWM channels still work even if other software functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software-based PWMs, using `millis()` or `micros()`.

Functions using normal software-based PWMs, relying on `loop()` and calling `millis()`, won't work if the `loop()` or `setup()` is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

---

### Currently supported Boards

- **tinyAVR boards using megaTinyCore**

##### Curiosity Nano ATtiny3217

<p align="center">
    <img src="https://github.com/khoih-prog/ATtiny_PWM/raw/main/pics/Curiosity_ATtiny3217.png">
</p>



---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`SpenceKonde megaTinyCore core 2.6.4+`](https://github.com/SpenceKonde/megaTinyCore) for Arduino ATtiny boards.  [![GitHub release](https://img.shields.io/github/release/SpenceKonde/megaTinyCore.svg)](https://github.com/SpenceKonde/megaTinyCore/releases/latest). Follow [**megaTinyCore Installation**](https://github.com/SpenceKonde/megaTinyCore/blob/master/Installation.md).

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ATtiny_PWM.svg?)](https://www.ardu-badge.com/ATtiny_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM) page.
2. Download the latest release `ATtiny_PWM-main.zip`.
3. Extract the zip file to `ATtiny_PWM-main` directory 
4. Copy whole `ATtiny_PWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ATtiny_PWM** library](https://registry.platformio.org/libraries/khoih-prog/ATtiny_PWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/ATtiny_PWM/installation). Search for **ATtiny_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

## More useful Information

### 1. Documents

1. [Arduino 101: Timers and Interrupts](https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072)
2. [Getting Started with Timer/Counter Type B (TCB)](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ApplicationNotes/ApplicationNotes/TB3214-Getting-Started-with-TCB-DS90003214.pdf)
3. [megaTinyCore README.md](https://github.com/SpenceKonde/megaTinyCore/blob/master/README.md)
4. [ATtiny3217 Curiosity Nano Hardware User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/40002193A.pdf)
5. [AVR128DA48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DA48-Curiosity-Nano-UG-DS50002971B.pdf)
6. [AVR128DB48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DB48-Curiosity-Nano-HW-UserG-DS50003037A.pdf)


### 2. Timer TCB0-TCB1

TCB0-TCB1 are 16-bit timers

The ATtiny boards, such as `ATtiny3217`, `ATtiny1617`, will have only maximum 2 TCB timers, (TCB0-TCB1).

The ATtiny boards, such as `ATtiny817`, will have only maximum 1 TCB timer, (TCB0).

The number of TCB timers will be automatically configured by the library.

The following is the partial list of number of TCBs for each ATtiny board/chip

#### TCB0-TCB1, TCA, TCD

**ATtiny3217, ATtiny1617, ATtiny3216, ATtiny1616, ATtiny1614**

#### TCB0, TCA, TCD

**ATtinyx12, ATtinyx14, ATtinyx16, ATtinyx17, such as ATtiny817, ATtiny417, ATtiny816, etc.**

#### TCB0, TCA, no TCD

**ATtinyx02, ATtinyx04, ATtinyx06, ATtinyx07, such as ATtiny1607, ATtiny807, ATtiny1606, etc.**

---
---


## Usage

Before using any PWM `Timer` and `channel`, you have to make sure the `Timer` and `channel` has not been used by any other purpose.


#### 1. Create PWM Instance with Pin, Frequency, dutycycle

```cpp
ATtiny_PWM* PWM_Instance;

PWM_Instance = new ATtiny_PWM(pinToUse, frequency, dutyCycle, channel, PWM_resolution);
```

#### 2. Initialize PWM Instance

```cpp
if (PWM_Instance)
{
  PWM_Instance->setPWM();
}
```

#### 3. Set or change PWM frequency or dutyCycle

To use `float new_dutyCycle`

```cpp
PWM_Instance->setPWM(PWM_Pins, new_frequency, new_dutyCycle);
```

such as 

```cpp
dutyCycle = 10.0f;
  
Serial.print(F("Change PWM DutyCycle to ")); Serial.println(dutyCycle);
PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);
```

---

To use `uint32_t new_dutyCycle` = `(real_dutyCycle * 65536) / 100`


```cpp
PWM_Instance->setPWM_Int(PWM_Pins, new_frequency, new_dutyCycle);
```

such as for `real_dutyCycle = 50%`

```cpp
// 50% dutyCycle = (real_dutyCycle * 65536) / 100
dutyCycle = 32768;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

for `real_dutyCycle = 50%`

```cpp
// 20% dutyCycle = (real_dutyCycle * 65536) / 100
dutyCycle = 13107;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

#### 4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation

Function prototype

```cpp
bool setPWM_manual(const uint8_t& pin, const uint16_t& DCValue);
bool setPWM_DCPercentage_manual(const uint8_t& pin, const float& DCPercentage);
bool setPWM_DCPercentageInt_manual(const uint8_t& pin, const uint16_t& DCPercentage);
```

Need to call only once for each pin


```cpp
PWM_Instance->setPWM(PWM_Pins, frequency, dutyCycle);
```

after that, if just changing `dutyCycle` / `level`, use the `faster`

```cpp
// For 50.0f dutycycle
// 97465ns
new_level = 50.0f * PWM_Instance->getPWMPeriod() / 100.0f ;
PWM_Instance->setPWM_manual(PWM_Pins, new_level);
```

or better and much easier to use, but `slowest`

```cpp
// v1.2.0: 129500ns. Previous v1.1.0 : 169577ns
new_DCPercentage = 50.0f;
PWM_Instance->setPWM_DCPercentage_manual(PWM_Pins, new_DCPercentage);
```

or the **fastest**

```cpp
// dutycyclePercent = 0-65535 == 0-100%
// Faster, 94197ns
dutycyclePercentInt = MAX_16BIT / 2;   // 50%
PWM_Instance->setPWM_DCPercentageInt_manual(pinToUse, dutycyclePercentInt);
```


---
---

### Examples: 

 1. [PWM_Basic](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Basic)
 2. [PWM_DynamicDutyCycle](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicDutyCycle)
 3. [PWM_DynamicDutyCycle_Int](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicDutyCycle_Int)
 4. [PWM_DynamicFreq](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicFreq)
 5. [PWM_Multi](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Multi)
 6. [PWM_MultiChannel](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_MultiChannel)
 7. [PWM_Waveform](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Waveform)
 8. [PWM_StepperControl](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_StepperControl) **New**
 9. [PWM_manual](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_manual) **New**
10. [PWM_SpeedTest](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_SpeedTest) **New**
 
---
---

### Example [PWM_Multi](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Multi)


https://github.com/khoih-prog/ATtiny_PWM/blob/5e2c8076e07ff5bd60b23753dbc66d8a8ebf4c74/examples/PWM_Multi/PWM_Multi.ino#L11-L141


---
---

### Debug Terminal Output Samples

### 1. PWM_DynamicDutyCycle on AVR_ATtiny3217

The following is the sample terminal output when running example [PWM_DynamicDutyCycle](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicDutyCycle) on **AVR_ATtiny3217**, to demonstrate the ability to provide high PWM frequencies and ability to change DutyCycle `on-the-fly`


```cpp
Starting PWM_DynamicDutyCycle on AVR_ATtiny3217
ATtiny_PWM v1.2.0
[PWM] ATtiny_PWM: freq = 5000.00
[PWM] ATtiny_PWM: _dutycycle = 0
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58982 , frequency = 5000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 200 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 62 , _actualFrequency = 5040
[PWM] setPWM_Int: TIMERA0, _dutycycle = 58982 , dutycycle = 56
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 56 , actual DC% = 90.48
=====================================================================================
Actual data: pin = 1, PWM DC = 90.00, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 20.00
[PWM] setPWM: _dutycycle = 13107 , frequency = 5000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 200 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 62 , _actualFrequency = 5040
[PWM] setPWM_Int: TIMERA0, _dutycycle = 13107 , dutycycle = 12
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 12 , actual DC% = 20.63
=====================================================================================
Actual data: pin = 1, PWM DC = 20.00, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58982 , frequency = 5000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 200 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 62 , _actualFrequency = 5040
[PWM] setPWM_Int: TIMERA0, _dutycycle = 58982 , dutycycle = 56
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 56 , actual DC% = 90.48
=====================================================================================
Actual data: pin = 1, PWM DC = 90.00, PWMPeriod = 200.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
```

---

### 2. PWM_Multi on AVR_ATtiny3217

The following is the sample terminal output when running example [**PWM_Multi**](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Multi) on **TAVR_ATtiny3217**, to demonstrate the ability to provide high PWM frequencies on multiple `PWM-capable` pins

```cpp
Starting PWM_Multi on AVR_ATtiny3217
ATtiny_PWM v1.2.0
[PWM] ATtiny_PWM: freq = 2000.00 , _dutycycle = 19660
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 0 dutycycle = 47 , actual DC% = 30.57
[PWM] ATtiny_PWM: freq = 8000.00 , _dutycycle = 58981
[PWM] setPWM_Int: TIMERD0, _dutycycle = 58981 , dutycycle = 229
[PWM] setPWM_Int 3: TCD0 pin = 12 dutycycle = 229
=====================================================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=====================================================================================
0	0	2000.00		30.00		2000.0000
1	12	8000.00		90.00		8000.0000
=====================================================================================
Actual data: pin = 0, PWM DC = 30.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 12, PWM DC = 90.00, PWMPeriod = 125.00, PWM Freq (Hz) = 8000.0000
=====================================================================================
```

---

### 3. PWM_DynamicFreq on AVR_ATtiny3217

The following is the sample terminal output when running example [**PWM_DynamicFreq**](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_DynamicFreq) on **AVR_ATtiny3217**, to demonstrate the ability to change dynamically PWM frequencies

```cpp
Starting PWM_DynamicFreq on AVR_ATtiny3217
ATtiny_PWM v1.2.0
[PWM] ATtiny_PWM: freq = 10000.00
[PWM] ATtiny_PWM: _dutycycle = 32767
=====================================================================================
Change PWM Freq to 20000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 20000.00
[PWM] setPWM_Int: new freq = 20000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 50 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 15 , _actualFrequency = 20833
[PWM] setPWM_Int: TIMERA0, _dutycycle = 32768 , dutycycle = 8
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 8 , actual DC% = 56.25
=====================================================================================
Actual data: pin = 1, PWM DC = 50.00, PWMPeriod = 50.00, PWM Freq (Hz) = 20000.0000
=====================================================================================
Change PWM Freq to 10000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 10000.00
[PWM] setPWM_Int: new freq = 10000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 100 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 31 , _actualFrequency = 10080
[PWM] setPWM_Int: TIMERA0, _dutycycle = 32768 , dutycycle = 16
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 16 , actual DC% = 53.13
=====================================================================================
Actual data: pin = 1, PWM DC = 50.00, PWMPeriod = 100.00, PWM Freq (Hz) = 10000.0000
=====================================================================================
Change PWM Freq to 20000.00
[PWM] setPWM: _dutycycle = 32768 , frequency = 20000.00
[PWM] setPWM_Int: new freq = 20000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 50 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 15 , _actualFrequency = 20833
[PWM] setPWM_Int: TIMERA0, _dutycycle = 32768 , dutycycle = 8
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 8 , actual DC% = 56.25
=====================================================================================
Actual data: pin = 1, PWM DC = 50.00, PWMPeriod = 50.00, PWM Freq (Hz) = 20000.0000
=====================================================================================
```


---


### 4. PWM_Waveform on AVR_ATtiny3217

The following is the sample terminal output when running example [**PWM_Waveform**](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_Waveform) on **AVR_ATtiny3217**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation


```cpp
Starting PWM_Waveform on AVR_ATtiny3217
ATtiny_PWM v1.2.0
============================================================================================
Actual data: pin = 1, PWM DutyCycle = 0.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
============================================================================================
[PWM] setPWM_manual: _dutycycle = 0 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 3276 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 6553 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 9830 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 13107 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 16383 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 19660 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 22937 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 26214 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 29490 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 32767 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 36044 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 39321 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 42597 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 45874 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 49151 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 52428 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 55704 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 58981 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 62258 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 65535 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 62258 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 58981 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 55704 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 52428 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 49151 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 45874 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 42597 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 39321 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 36044 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 32767 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 29490 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 26214 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 22937 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 19660 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 16383 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 13107 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 9830 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 6553 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 3276 , frequency = 2000.00
[PWM] setPWM_manual: _dutycycle = 0 , frequency = 2000.00
```

---

### 5. PWM_manual on AVR_ATtiny3217

The following is the sample terminal output when running example [**PWM_manual**](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_manual) on **AVR_ATtiny3217**, to demonstrate how to use the `setPWM_manual()` and `setPWM_DCPercentage_manual()` functions in wafeform creation


```cpp
Starting PWM_manual on AVR_ATtiny3217
ATtiny_PWM v1.2.0
[PWM] ATtiny_PWM: freq = 2000.00 , _dutycycle = 0
[PWM] setPWM: _dutycycle = 0 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 0 , actual DC% = 0.64
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 0.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 0.00 , dc = 0.00
[PWM] setPWM_manual: _dutycycle = 0 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 0 , actual DC% = 0.64
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 0.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 5.00 , dc = 3276.75
[PWM] setPWM_manual: _dutycycle = 3276 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 7 , actual DC% = 5.10
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 5.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 10.00 , dc = 6553.50
[PWM] setPWM_manual: _dutycycle = 6553 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 15 , actual DC% = 10.19
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 10.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 15.00 , dc = 9830.25
[PWM] setPWM_manual: _dutycycle = 9830 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 23 , actual DC% = 15.29
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 15.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 20.00 , dc = 13107.00
[PWM] setPWM_manual: _dutycycle = 13107 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 31 , actual DC% = 20.38
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 20.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 25.00 , dc = 16383.75
[PWM] setPWM_manual: _dutycycle = 16383 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 39 , actual DC% = 25.48
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 25.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 30.00 , dc = 19660.50
[PWM] setPWM_manual: _dutycycle = 19660 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 47 , actual DC% = 30.57
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 30.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 35.00 , dc = 22937.25
[PWM] setPWM_manual: _dutycycle = 22937 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 55 , actual DC% = 35.67
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 35.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 40.00 , dc = 26214.00
[PWM] setPWM_manual: _dutycycle = 26214 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 63 , actual DC% = 40.76
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 40.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 45.00 , dc = 29490.75
[PWM] setPWM_manual: _dutycycle = 29490 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 70 , actual DC% = 45.22
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 45.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 50.00 , dc = 32767.50
[PWM] setPWM_manual: _dutycycle = 32767 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 78 , actual DC% = 50.32
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 50.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 55.00 , dc = 36044.25
[PWM] setPWM_manual: _dutycycle = 36044 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 86 , actual DC% = 55.41
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 55.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 60.00 , dc = 39321.00
[PWM] setPWM_manual: _dutycycle = 39321 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 94 , actual DC% = 60.51
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 60.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 65.00 , dc = 42597.75
[PWM] setPWM_manual: _dutycycle = 42597 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 101 , actual DC% = 64.97
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 65.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 70.00 , dc = 45874.50
[PWM] setPWM_manual: _dutycycle = 45874 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 109 , actual DC% = 70.06
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 70.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 75.00 , dc = 49151.25
[PWM] setPWM_manual: _dutycycle = 49151 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 117 , actual DC% = 75.16
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 75.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 80.00 , dc = 52428.00
[PWM] setPWM_manual: _dutycycle = 52428 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 125 , actual DC% = 80.25
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 80.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 85.00 , dc = 55704.75
[PWM] setPWM_manual: _dutycycle = 55704 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 133 , actual DC% = 85.35
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 85.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 90.00 , dc = 58981.50
[PWM] setPWM_manual: _dutycycle = 58981 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 141 , actual DC% = 90.45
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 90.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 95.00 , dc = 62258.25
[PWM] setPWM_manual: _dutycycle = 62258 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 149 , actual DC% = 95.54
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 95.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
[PWM] setPWM_DCPercentage_manual: DCPercentage = 100.00 , dc = 65535.00
[PWM] setPWM_manual: _dutycycle = 65535 , frequency = 2000.00
[PWM] setPeriod_TimerA0: F_CPU = 20000000 , microseconds = 500 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: pwmPeriod = 156 , _actualFrequency = 2003
[PWM] setPWM_Int: TCA0 pin = 1 dutycycle = 157 , actual DC% = 100.64
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 100.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
```


---

### 6. PWM_SpeedTest on AVR_ATtiny3217

The following is the sample terminal output when running example [**PWM_SpeedTest**](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_SpeedTest) on **AVR_ATtiny3217**, to demonstrate how to use new faster `setPWM_DCPercentageInt_manual()` function in wafeform creation, The time is `94197ns` compared to `169577ns` when using `setPWM_DCPercentage_manual()` function of `v1.1.0`. The `setPWM_manual` with `97465ns` is to be used with pre-calculated values in array

##### USING_DC_PERCENT

```
Starting PWM_SpeedTest on AVR_ATtiny3217
ATtiny_PWM v1.2.0
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 0.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
Average time of setPWM function USING_DC_PERCENT
count=10607, ns=94277
count=10616, ns=94197
count=10616, ns=94197
count=10607, ns=94277
count=10616, ns=94197
count=10615, ns=94206
count=10607, ns=94277
count=10616, ns=94197
count=10616, ns=94197
count=10616, ns=94197
count=10607, ns=94277
```

##### not USING_DC_PERCENT

```
Starting PWM_SpeedTest on AVR_ATtiny3217
ATtiny_PWM v1.2.0
=================================================================================================
Actual data: pin = 1, PWM DutyCycle % = 0.00, PWMPeriod = 500.00, PWM Freq (Hz) = 2000.0000
=================================================================================================
Average time of setPWM function not USING_DC_PERCENT
count=10248, ns=97580
count=10261, ns=97456
count=10260, ns=97465
count=10252, ns=97541
count=10260, ns=97465
count=10260, ns=97465
count=10252, ns=97541
count=10260, ns=97465
count=10261, ns=97456
count=10260, ns=97465
count=10252, ns=97541
count=10260, ns=97465

```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [ATtiny_PWM issues](https://github.com/khoih-prog/ATtiny_PWM/issues)

---
---

## TO DO

1. Search for bug and improvement.
2. Support to **TCD0** to change frequency

---

## DONE

 1. Basic `TCA0` hardware PWM-channels for Arduino **AVR ATtiny-based boards (ATtiny3217, etc.)** using [**megaTinyCore**](https://github.com/SpenceKonde/megaTinyCore)
 2. Add example [PWM_StepperControl](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_StepperControl) to demo how to control Stepper Motor using PWM
 3. Add example [PWM_manual](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_manual) to demo how to correctly use PWM to generate waveform
 4. Add function `setPWM_DCPercentage_manual()` to facilitate the setting PWM DC manually by using `DCPercentage`, instead of `absolute DCValue` depending on varying PWMPeriod
 5. Catch low frequency error and use lowest permissible frequency
 6. Optimize speed with new `setPWM_DCPercentageInt_manual` function to improve speed almost 50% compared to `setPWM_DCPercentage_manual` of previous `v1.1.0`
 7. Add example [PWM_SpeedTest](https://github.com/khoih-prog/ATtiny_PWM/tree/main/examples/PWM_SpeedTest) to demo the better speed of new `setPWM_DCPercentageInt_manual` function

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to [Paul van Dinther](https://github.com/dinther) for proposing new way to use PWM to drive Stepper-Motor in [Using PWM to step a stepper driver #16](https://github.com/khoih-prog/RP2040_PWM/issues/16), leading to v1.0.1


<table>
  <tr>
    <td align="center"><a href="https://github.com/dinther"><img src="https://github.com/dinther.png" width="100px;" alt="dinther"/><br /><sub><b>Paul van Dinther</b></sub></a><br /></td>
  </tr>
</table>

---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/ATtiny_PWM/blob/main/LICENSE)

---

## Copyright

Copyright (c) 2022- Khoi Hoang


