## DoubleResetDetector_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/DoubleResetDetector_Generic.svg)](https://github.com/khoih-prog/DoubleResetDetector_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/DoubleResetDetector_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/DoubleResetDetector_Generic.svg)](http://github.com/khoih-prog/DoubleResetDetector_Generic/issues)

---
---

## Table of Contents

* [Why do we need this DoubleResetDetector_Generic library](#why-do-we-need-this-doubleresetdetector_generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](#changelog)
  * [Releases v1.0.3](#releases-v103)
  * [Releases v1.0.2](#releases-v102)
  * [Releases v1.0.1](#releases-v101)
  * [Releases v1.0.0](#releases-v100)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
* [Purpose](#purpose)
* [How It Works](#how-it-works)
* [Examples](#examples)
  * [ 1. minimal](examples/minimal)
  * [Many other libraries are depending on this library's DRD feature](#many-other-libraries-are-depending-on-this-librarys-drd-feature)
    * [ 1. BlynkEthernet_WM](https://github.com/khoih-prog/BlynkEthernet_WM)
    * [ 2. Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
    * [ 3. Blynk_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM)
    * [ 4. WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
    * [ 5. BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM)
    * [ 6. ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite)
    * [ 7. WIOTerminal_WiFiManager](https://github.com/khoih-prog/WIOTerminal_WiFiManager)
    * [ 8. Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager)
    * [ 9. Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)
* [Example minimal](#example-minimal)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. DRD Not Detected](#1-drd-not-detected)
  * [2. DRD detected and Config Portal opened](#2-drd-detected-and-config-portal-opened)
* [Libraries using ESP_DoubleResetDetector or DoubleResetDetector_Generic library](#libraries-using-esp_doubleresetdetector-or-doubleresetdetector_generic-library)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)
---
---

### Why do we need this [DoubleResetDetector_Generic library](https://github.com/khoih-prog/DoubleResetDetector_Generic)

#### Features

[**DoubleResetDetector_Generic**](https://github.com/khoih-prog/DoubleResetDetector_Generic) is a library for the **Arduino AVR, Teensy, SAM DUE, SAMD21, SAMD51, STM32F/L/H/G/WB/MP1, nRF52, etc.** boards to detects a double reset, within configurable timeout (default 10s) seconds, so that an alternative start-up mode can be used. Example use cases are to allow re-configuration of a device's WiFi / MQTT / Blynk credentials.

This library is based on, modified, bug-fixed and improved from [`Stephen Denne's DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) and [`Khoi Hoang's ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to add support for AVR, Teensy, SAM DUE, SAMD, STM32, nRF52, etc. boards.

Currently, [`DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) only supports ESP8266 using RTC memory, and [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) only ESP8266 and ESP32.
 
This library can be used to detect a double reset within a predetermined time to force the program to enter a special operation such as Config Portal, Clear Default Data, etc., using :

1. EEPROM for AVR, Teensy, STM32 boards.
2. [`FlashStorage_SAMD library v1.0.0`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, **NANO_33_IOT**, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
3. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
4. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52


#### Currently supported Boards

This [**DoubleResetDetector_Generic** library](https://github.com/khoih-prog/DoubleResetDetector_Generic) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAM DUE**
 
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 
 6. **AVR Mega1280, 2560, ADK.**
 
 7. **STM32F/L/H/G/WB/MP1 boards**

- Nucleo-144
- Nucleo-64
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
- STM32L0, STM32L1, STM32L4
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards

---

## Changelog

### Releases v1.0.3

1. Clean-up all compiler warnings possible.
2. Add Table of Contents
3. Modify Version String 

### Releases v1.0.2

1. Fix not-detected DRD bug for SAMD21 and SAMD51 boards.

### Releases v1.0.1

1. Support **nRF52** boards such as **Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, NINA_B302_ublox**, etc.
2. nRF52 boards to save data in **Adafruit's InternalFS/LittleFS**.

### Releases v1.0.0

1. Support boards such as **AVR, Teensy, SAM DUE, SAMD21, SAMD51 and STM32F/L/H/G/WB/MP1, etc.**
2. **AVR Mega, Teensy, STM32F/L/H/G/WB/MP1** to save data in **EPPROM**
3. **SAMD** to save data in EEPROM-simulated [**FlashStorage_SAMD**](https://github.com/khoih-prog/FlashStorage_SAMD)
4. **SAM DUE** to save data in [**DueFlashStorage**](https://github.com/sebnil/DueFlashStorage)

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Teensy core 1.53+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 3. [`Arduino SAM DUE core 1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 4. [`Arduino SAMD core 1.8.11+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 5. [`Adafruit SAMD core 1.6.4+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 6. [`Seeeduino SAMD core 1.8.1+`](https://www.seeedstudio.com/) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.).
 7. [`Adafruit nRF52 v0.21.0+`](www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox, NINA_B112_ublox**, etc.
 8. [`Arduino Core for STM32 v1.9.0+`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 9. [`FlashStorage_SAMD library v1.0.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) or [`Platform.io FlashStorage_SAMD library v1.0.0+`](https://platformio.org/lib/show/11242/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
10. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
11. [`Adafruit's LittleFS/InternalFS`](https://www.adafruit.com) for nRF52. Already included if you already installed Adafruit **nRF52 board package** from Boards Manager.

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `DoubleResetDetector_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [DoubleResetDetector_Generic](https://github.com/khoih-prog/DoubleResetDetector_Generic) page.
2. Download the latest release `DoubleResetDetector_Generic-master.zip`.
3. Extract the zip file to `DoubleResetDetector_Generic-master` directory 
4. Copy whole `DoubleResetDetector_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **DoubleResetDetector_Generic** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for DoubleResetDetector_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
3. Install [**DoubleResetDetector_Generic** library](https://platformio.org/lib/show/7240/DoubleResetDetector_Generic) by using [Library Manager](https://platformio.org/lib/show/7240/DoubleResetDetector_Generic/installation). Search for **DoubleResetDetector_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.12/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.12. This file must be copied into the directory:

- `./arduino-1.8.12/hardware/teensy/avr/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.10](Packages_Patches/arduino/hardware/samd/1.8.10) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.10).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.4) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.4). 

Supposing the Adafruit SAMD core version is 1.6.4. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.4/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

#### 7. For STM32 boards

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---
---

### Purpose

Detects a double reset so that an alternative start-up mode can be used. One example use is to allow re-configuration of a device's WiFi or Blynk Credentials.

### How It Works
  
   When the device starts up it checks the EEPROM, (Due)FlashStorage or LittleFS file `/drd.dat` for a flag to see if it has been recently reset within the configurable timeout seconds
   
---
   
### Examples: 

 1. [minimal](examples/minimal)


#### Many other libraries are depending on this library's DRD feature

  All examples of these following libraries are using DRD feature of this [DoubleResetDetector_Generic Library](https://github.com/khoih-prog/DoubleResetDetector_Generic)
   
* [ 1. BlynkEthernet_WM](https://github.com/khoih-prog/BlynkEthernet_WM)
* [ 2. Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM)
* [ 3. Blynk_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM)
* [ 4. WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
* [ 5. BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM)
* [ 6. ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite)
* [ 7. WIOTerminal_WiFiManager](https://github.com/khoih-prog/WIOTerminal_WiFiManager)
* [ 8. Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager)
* [ 9. Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)

  
---
   
#### Example [minimal](examples/minimal)

```cpp
#define DRD_GENERIC_DEBUG       true  //false

#include <DoubleResetDetector_Generic.h>

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

#ifndef LED_BUILTIN
#define LED_BUILTIN       13
#endif

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("DoubleResetDetector Example Program");
  Serial.println("-----------------------------------");

  drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);

  if (drd->detectDoubleReset()) {
    Serial.println("Double Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.println("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void loop()
{
  // Call the double reset detector loop method every so often,
  // so that it can recognise when the timeout expires.
  // You can also call drd.stop() when you wish to no longer
  // consider the next reset as a double reset.
  drd->loop();
}
```

---

### Debug Terminal Output Samples

This is the terminal output for a Nano 33 IoT using [`WiFiManager_NINA_Lite`](https://github.com/khoih-prog/WiFiManager_NINA_Lite) when DRD is detected and not detected

#### 1. DRD Not Detected

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
*NN: Hostname=SAMD-Master-Controller
Flag read = 0xd0d04321
No doubleResetDetected             <====== No DRD
SetFlag write = 0xd0d01234
*NN: bg: noConfigPortal = true
*NN: Connecting MultiWifi...
*NN: con2WF:spentMsec=0
WiFi-begin: return1 = 3
WiFi-begin: return2 = 3
*NN: con2WF:OK
*NN: SSID=HueNet1,RSSI=-34
*NN: IP=192.168.2.93
*NN: b:WOK
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
Your stored Credentials :
Blynk Server1 = new-account.duckdns.org
Token1 = new-token1
Blynk Server2 = new-account.ddns.net
Token2 = new-token2
Port = 8080
MQTT Server = new-mqtt.duckdns.org
```

#### 2. DRD detected and Config Portal opened

```
Start SAMD_WiFiNINA on SAMD NANO_33_IOT
*NN: Hostname=SAMD-Master-Controller
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
*NN: Double Reset Detected      <====== DRD detected
*NN: bg: noConfigPortal = false
*NN: b:OpenPortal               <====== Config Portal opened
*NN: SSID=WIFININA_51F485,PW=MyWIFININA_51F485
*NN: IP=192.168.4.1,CH=10

```

---

### Libraries using ESP_DoubleResetDetector or DoubleResetDetector_Generic library

You can also see how [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) and [`DoubleResetDetector_Generic`](https://github.com/khoih-prog/DoubleResetDetector_Generic) are applied in many other libraries, such as:

 1. [Blynk_WM](https://github.com/khoih-prog/Blynk_WM)
 2. [BlynkEthernet_WM](https://github.com/khoih-prog/BlynkEthernet_WM)
 3. [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
 4. [BlynkESP32_BT_WF](https://github.com/khoih-prog/BlynkESP32_BT_WF), 
 5. [Blynk_GSM_Manager](https://github.com/khoih-prog/Blynk_GSM_Manager),
 6. [Blynk_Esp8266AT_WM](https://github.com/khoih-prog/Blynk_Esp8266AT_WM), 
 7. [Blynk_WiFiNINA_WM](https://github.com/khoih-prog/Blynk_WiFiNINA_WM), 
 8. [Blynk_Async_WM](https://github.com/khoih-prog/Blynk_Async_WM),
 9. [Blynk_Async_ESP32_BT_WF](https://github.com/khoih-prog/Blynk_Async_ESP32_BT_WF), 
10. [Blynk_Async_GSM_Manager](https://github.com/khoih-prog/Blynk_Async_GSM_Manager),
11. [ESP_WiFiManager](https://github.com/khoih-prog/ESP_WiFiManager)
12. [ESPAsync_WiFiManager](https://github.com/khoih-prog/ESPAsync_WiFiManager)
13. [WiFiManager_NINA_Lite](https://github.com/khoih-prog/WiFiManager_NINA_Lite)
14. [BlynkEthernet_STM32_WM](https://github.com/khoih-prog/BlynkEthernet_STM32_WM),
15. [ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite)
16. [WIOTerminal_WiFiManager](https://github.com/khoih-prog/WIOTerminal_WiFiManager)
17. [Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager)
18. [Ethernet_Manager_STM32](https://github.com/khoih-prog/Ethernet_Manager_STM32)

and the list is growing fast.

---
---

### Debug

Debug is disabled by default. To enable debug:

```cpp
// Use this to output debug msgs to Serial
#define DRD_GENERIC_DEBUG       true
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Packages' Patches or this library latest version.


---
---

### Releases

### Releases v1.0.3

1. Clean-up all compiler warnings possible.
2. Add Table of Contents
3. Modify Version String 

### Releases v1.0.2

1. Fix not-detected DRD bug for SAMD21 and SAMD51 boards.

### Releases v1.0.1

1. Support **nRF52** boards such as **Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, NINA_B302_ublox**, etc.
2. nRF52 boards to save data in **Adafruit's InternalFS/LittleFS**.

### Releases v1.0.0

1. Support boards such as **AVR, Teensy, SAM DUE, SAMD21, SAMD51 and STM32F/L/H/G/WB/MP1, etc.**
2. **AVR Mega, Teensy, STM32F/L/H/G/WB/MP1** to save data in **EPPROM**
3. **SAMD** to save data in EEPROM-simulated [**FlashStorage_SAMD**](https://github.com/khoih-prog/FlashStorage_SAMD)
4. **SAM DUE** to save data in [**DueFlashStorage**](https://github.com/sebnil/DueFlashStorage)

---
---

### Issues

Submit issues to: [DoubleResetDetector_Generic issues](https://github.com/khoih-prog/DoubleResetDetector_Generic/issues)

---

### TO DO

1. Search for bug and improvement.
2. More examples and more supported boards.

### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)** using FlashStorage_SAMD.
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**  using FlashStorage_SAMD.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**  using FlashStorage_SAMD.
 4. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.** using LittleFS.
 5. Add support to SAM DUE using DueFlashStorage.
 6. Add support to Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless  using FlashStorage_SAMD.
 7. Add support to STM32F/L/H/G/WB/MP1 boards using EEPROM.
 8. Add support to Teensy boards using EEPROM.
 8. Add support to AVR Mega, Nano, UNO, etc boards using EEPROM.

---
---

### Contributions and thanks

1. Thanks to [Stephen Denne](https://github.com/datacute) for the [`DoubleResetDetector library`](https://github.com/datacute/DoubleResetDetector) this library is based upon.
2. Thanks to [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for help in debugging and testing. Without that, support to nRF52, especially **NINA_B302_ublox running as nRF52840**, has never been started and finished. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

<table>
  <tr>
    <td align="center"><a href="https://github.com/datacute"><img src="https://github.com/datacute.png" width="100px;" alt="datacute"/><br /><sub><b>⭐️ Stephen Denne</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>Miguel Wisintainer</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/DoubleResetDetector_Generic/blob/master/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang
