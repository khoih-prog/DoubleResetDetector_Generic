## ESP_DoubleResetDetector

[![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)

DoubleResetDetector_Generic is a library for the Arduino AVR, Teensy, SAM-DUE, SAMD, STM32. etc. boards to enable trigger configure mode by resetting the boards twice within configurable timeout seconds.
   
### Releases v1.0.0

1. Support boards such as AVR, Teensy, SAM DUE, SAMD and STM32, etc.
2. AVR Mega, Teensy, STM32 to save data in EPPROM
3. SAMD to sve data in EEPROM-simulated FlashStorage
4. SAM DUE to save data in DueFlashStorage

This library is based on, modified, bug-fixed and improved from [`DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) and [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) to add support for AVR, Teensy, SAM DUE, SAMD, STM32 boards.

Currently, [`DoubleResetDetector`](https://github.com/datacute/DoubleResetDetector) only supports ESP8266 using RTC memory, and [`ESP_DoubleResetDetector`](https://github.com/khoih-prog/ESP_DoubleResetDetector) only ESP8266 and ESP32.
 
This library can be used to detect a double reset to enter a special, using :

1. EEPROM for AVR, Teensy, STM32 boards.
2. [`FlashStorage_SAMD library v1.0.0`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, ***NANO_33_IOT***, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
3. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE

## Prerequisite
 1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Teensy core 1.51 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 3. [`Arduino SAM DUE core 1.6.12 or later`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 4. [`Arduino SAMD core 1.8.5 or later`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 5. [`Adafruit SAMD core 1.5.11 or later`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 6. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 7. [`FlashStorage_SAMD library v1.0.0 or later`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
 8. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE

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

### Releases

#### Releases v1.0.0

1. Support boards such as AVR, Teensy, SAM DUE, SAMD and STM32, etc.
2. AVR Mega, Teensy, STM32 to save data in EPPROM
3. SAMD to sve data in EEPROM-simulated FlashStorage
4. SAM DUE to save data in DueFlashStorage

#### PURPOSE:

Detects a double reset so that an alternative start-up mode can be used. One example use is to allow re-configuration of a device's WiFi or Blynk Credentials.

#### Usage

How to use

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

Also see examples: 
1. [minimal](examples/minimal)

### TO DO

1. Search for bug and improvement.
2. More examples


### Contributing
If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

### Copyright
Copyright 2020- Khoi Hoang
