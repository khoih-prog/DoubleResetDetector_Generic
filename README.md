## DoubleResetDetector_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/DoubleResetDetector_Generic.svg)](https://github.com/khoih-prog/DoubleResetDetector_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/DoubleResetDetector_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/DoubleResetDetector_Generic.svg)](http://github.com/khoih-prog/DoubleResetDetector_Generic/issues)

DoubleResetDetector_Generic is a library for the Arduino AVR, Teensy, SAM DUE, SAMD21, SAMD51, STM32, nRF52, etc. boards to enable trigger configure mode by resetting the boards twice within configurable timeout (default 10s) seconds.
   
### Releases v1.0.2

1. Fix not-detected DRD bug for SAMD21 and SAMD51 boards.

### Releases v1.0.1

1. Support nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, ***NINA_B302_ublox***, etc.
2. nRF52 boards to save data in ***Adafruit's InternalFS/LittleFS***.

### Releases v1.0.0

1. Support boards such as AVR, Teensy, SAM DUE, SAMD21, SAMD51 and STM32, etc.
2. AVR Mega, Teensy, STM32 to save data in EPPROM
3. SAMD to sve data in EEPROM-simulated FlashStorage
4. SAM DUE to save data in DueFlashStorage

This library is based on, modified, bug-fixed and improved from [`DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) and [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to add support for AVR, Teensy, SAM DUE, SAMD, STM32 boards.

Currently, [`DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) only supports ESP8266 using RTC memory, and [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) only ESP8266 and ESP32.
 
This library can be used to detect a double reset within apredetermined time to force the program to enter a special operation such as Config Portal, Clear Default Data, etc., using :

1. EEPROM for AVR, Teensy, STM32 boards.
2. [`FlashStorage_SAMD library v1.0.0`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, ***NANO_33_IOT***, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
3. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
4. [Adafruit's LittleFS/InternalFS](www.adafruit.com)) for nRF52

## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Teensy core 1.51 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 3. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 4. [`Arduino SAMD core 1.8.5 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 5. [`Adafruit SAMD core 1.5.11 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 6. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 7. [`FlashStorage_SAMD library v1.0.0 or later`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
 8. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
 9. [`Adafruit nRF52 v0.20.1 or later`](www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, ***NINA_B302_ublox***, etc.
 
### Quick Start

#### Installing use Arduino Library Manager

1. The easiest way is to use `Arduino Library Manager`. Search for `DoubleResetDetector_Generic`, then select / install the latest version.
2. More detailed instructions at [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)

#### Manual Install

1. Navigate to [DoubleResetDetector_Generic](https://github.com/khoih-prog/DoubleResetDetector_Generic) page.
2. Download the latest release `DoubleResetDetector_Generic-master.zip`.
3. Extract the zip file to `DoubleResetDetector_Generic-master` directory 
4. Copy whole 
  - `DoubleResetDetector_Generic-master` folder to Arduino libraries directory such as `~/Arduino/libraries`.

#### Important notes for Adafruit nRF52 boards 

1. To add NINA_B302_ublox boards running as nRF52840, you have to copy the whole nRF52 directory into Adafruit nRF52 directory. Supposing the Adafruit nRF52 version is 0.20.1

These files must be copied into the directory:
- `nRF52/0.20.1/boards.txt`
- `nRF52/0.20.1/variants/variant.h`
- `nRF52/0.20.1/variants/variant.cpp`
Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:
- `nRF52/x.yy.z/boards.txt`
- `nRF52/x.yy.z/variants/variant.h`
- `nRF52/x.yy.z/variants/variant.cpp`

### Releases

### Releases v1.0.2

1. Fix not-detected DRD bug for SAMD21 and SAMD51 boards.

### Releases v1.0.1

1. Support nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, ***NINA_B302_ublox***, etc.
2. nRF52 boards to save data in ***Adafruit's InternalFS/LittleFS***.

#### Releases v1.0.0

1. Support boards such as AVR, Teensy, SAM DUE, SAMD and STM32, etc.
2. AVR Mega, Teensy, STM32 to save data in EPPROM
3. SAMD to sve data in EEPROM-simulated FlashStorage
4. SAM DUE to save data in DueFlashStorage

#### PURPOSE:

Detects a double reset so that an alternative start-up mode can be used. One example use is to allow re-configuration of a device's WiFi or Blynk Credentials.

### How It Works
  
   When the device starts up it checks the EEPROM or (Due)FlashStorage for a flag to see if it has been recently reset within the configurable timeout seconds
   
#### Sample Code [minimal example](examples/minimal)

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

You can also see how [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) and [`DoubleResetDetector_Generic`](https://github.com/khoih-prog/DoubleResetDetector_Generic) are applied in many other libraries, such as:

1. [`Blynk_WM`](https://github.com/khoih-prog/Blynk_WM)
2. [`BlynkEthernet_WM`](https://github.com/khoih-prog/BlynkEthernet_WM)
3. [`WiFiManager_NINA_Lite`](https://github.com/khoih-prog/WiFiManager_NINA_Lite)

and many more to come.

### TO DO

1. Search for bug and improvement.
2. More examples and more supported boards.

### Contributions and thanks

1. Thanks to [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for help in debugging and testing. Without that, support to nRF52, especially ***NINA_B320_ublox running as nRF52840***, has never been started and finished. See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

### Contributing
If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

### Copyright

Copyright 2020- Khoi Hoang
