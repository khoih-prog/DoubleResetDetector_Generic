/****************************************************************************************************************************
   DoubleResetDetector_Generic.h
   For ESP8266 / ESP32 boards

   DoubleResetDetector_Generic is a library for the Arduino AVR, Teensy, SAM-DUE, SAMD, STM32. etc. boards
   to enable trigger configure mode by resetting the boards twice within configurable timeout seconds.

   Based on and modified from DataCute https://github.com/datacute/DoubleResetDetector and 
   https://github.com/khoih-prog/ESP_DoubleResetDetector 

   Built by Khoi Hoang https://github.com/khoih-prog/DoubleResetDetector_Generic
   Licensed under MIT license
   Version: 1.0.2

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
   1.0.0   K Hoang      14/04/2020 Initial coding for boards such as AVR, Teensy, SAM DUE, SAMD and STM32, etc.
   1.0.1   K Hoang      01/05/2020 Add support to Adafruit nRF52 boards, such as Feather, Itsy-Bitsy nRF52840, NINA_W302_ublox.
   1.0.2   K Hoang      04/05/2020 Fix not-detected DRD bug for SAMD boards.
 *****************************************************************************************************************************/

#ifndef DoubleResetDetector_Generic_H
#define DoubleResetDetector_Generic_H

#if ( defined(ESP32) || defined(ESP8266) )
  #error Please use ESP_DoubleResetDetector library (https://github.com/khoih-prog/ESP_DoubleResetDetector) for ESP8266 and ESP32!
#endif

// For AVR, Teensy, STM32 boards, use EEPROM
// For SAM DUE, use DueFlashStorage. For SAMD, use FlashStorage_SAMD

#define  DRD_FILENAME     "/drd.dat"
#define  DRD_FLAG_OFFSET  0

#if defined(ARDUINO) && (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#define DRD_GENERIC_USE_EEPROM      true

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(DRD_GENERIC_USE_SAM_DUE)
    #undef DRD_GENERIC_USE_SAM_DUE
  #endif
  #define DRD_GENERIC_USE_SAM_DUE     true
  #if defined(DRD_GENERIC_USE_EEPROM)
    #undef DRD_GENERIC_USE_EEPROM
  #endif
  #define DRD_GENERIC_USE_EEPROM    false
  #warning Use SAM-DUE and DueFlashStorage
#elif ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )
  #if defined(DRD_GENERIC_USE_SAMD)
    #undef DRD_GENERIC_USE_SAMD
  #endif
  #define DRD_GENERIC_USE_SAMD      true
  #if defined(DRD_GENERIC_USE_EEPROM)
    #undef DRD_GENERIC_USE_EEPROM
  #endif
  #define DRD_GENERIC_USE_EEPROM    false
  #warning Use SAMD and FlashStorage
  
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) | defined(NINA_B302_ublox) )    

  #if defined(DRD_GENERIC_USE_NRF52)
    #undef DRD_GENERIC_USE_NRF52
  #endif
  #define DRD_GENERIC_USE_NRF52      true
  #if defined(DRD_GENERIC_USE_EEPROM)
    #undef DRD_GENERIC_USE_EEPROM
  #endif
  #define DRD_GENERIC_USE_EEPROM    false
  #warning Use NRF52 and LittleFS / InternalFS

#else
  #if defined(CORE_TEENSY)
    #warning Use TEENSY and EEPROM
  #elif ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) )
    #warning Use STM32 and EEPROM
  #elif ( defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_BT) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_ESPLORA) \
      || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_GEMMA) || defined(ARDUINO_AVR_LEONARDO) \
      || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_LILYPAD_USB) || defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) \
      || defined(ARDUINO_AVR_MICRO) || defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_NG) \
      || defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_ROBOT_CONTROL) || defined(ARDUINO_AVR_ROBOT_MOTOR) || defined(ARDUINO_AVR_UNO) \
      || defined(ARDUINO_AVR_YUN) )        
    #warning Use AVR and EEPROM
  #else
    #warning Use Unknown board and EEPROM
  #endif  
#endif
 
//default to use EEPROM, otherwise, use DueFlashStorage or FlashStorage_SAMD
#if DRD_GENERIC_USE_EEPROM
  #include <EEPROM.h>

  #define  FLAG_DATA_SIZE     4

  #ifndef DRD_EEPROM_SIZE
    // Please change according to your application to avoid overwriting or being overwritten
    #define DRD_EEPROM_SIZE     (E2END + 1)
  #endif

#elif DRD_GENERIC_USE_SAMD
  // Include EEPROM-like API for FlashStorage
  //#include <FlashAsEEPROM.h>                //https://github.com/cmaglie/FlashStorage
  #include <FlashAsEEPROM_SAMD.h>             //https://github.com/khoih-prog/FlashStorage_SAMD
#elif DRD_GENERIC_USE_SAM_DUE
  //Use DueFlashStorage to simulate EEPROM
  #include <DueFlashStorage.h>                 //https://github.com/sebnil/DueFlashStorage
  DueFlashStorage dueFlashStorage;
  
#elif DRD_GENERIC_USE_NRF52
  // Include LittleFS similar to SPIFFS
  #include <Adafruit_LittleFS.h>
  #include <InternalFileSystem.h>
  using namespace Adafruit_LittleFS_Namespace;
  
  File DRD_file(InternalFS);
  
#endif    //#if DRD_GENERIC_USE_EEPROM

#ifndef DRD_GENERIC_DEBUG
#define DRD_GENERIC_DEBUG       false
#endif

#define DOUBLERESETDETECTOR_GENERIC_VERSION "1.0.0"

#define DOUBLERESETDETECTOR_GENERIC_FLAG_SET    0xD0D01234
#define DOUBLERESETDETECTOR_GENERIC_FLAG_CLEAR  0xD0D04321

class DoubleResetDetector_Generic
{
  public:
    DoubleResetDetector_Generic(int timeout, int address)
    {
      this->timeout = timeout * 1000;
      this->DRD_EEPROM_START = address;
      doubleResetDetected = false;
      waitingForDoubleReset = false;
          
#if DRD_GENERIC_USE_EEPROM
      EEPROM.begin();
  #if (DRD_GENERIC_DEBUG)
      Serial.println("\nEEPROM size = " + String(DRD_EEPROM_SIZE) + ", start = " + String(DRD_EEPROM_START));
  #endif
        
#elif DRD_GENERIC_USE_SAMD
      // Do something to init FlashStorage
#elif DRD_GENERIC_USE_SAM_DUE
      // Do something to init DueFlashStorage
      
#elif DRD_GENERIC_USE_NRF52
      // Do something to init LittleFS / InternalFS
      // Initialize Internal File System
      InternalFS.begin();
#else
      #error Un-identifiable board selected. Please check your Tools->Board setting.
#endif
    };

    bool detectDoubleReset()
    {
      doubleResetDetected = detectRecentlyResetFlag();

      if (doubleResetDetected)
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("doubleResetDetected");
#endif

        clearRecentlyResetFlag();
      }
      else
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("No doubleResetDetected");
#endif

        setRecentlyResetFlag();
        waitingForDoubleReset = true;
      }

      return doubleResetDetected;

    };

    void loop()
    {
      if (waitingForDoubleReset && millis() > timeout)
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("Stop doubleResetDetecting");
#endif

        stop();
      }
    };

    void stop()
    {
      clearRecentlyResetFlag();
      waitingForDoubleReset = false;
    };

    bool doubleResetDetected;


  private:
    uint32_t DOUBLERESETDETECTOR_FLAG;
    int timeout;
    int DRD_EEPROM_START;
    bool waitingForDoubleReset;

#if (DRD_GENERIC_USE_SAMD)    
    uint32_t readFlagSAMD(void)
    {        
      uint16_t offset   = DRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &DOUBLERESETDETECTOR_FLAG;
      
      for (int i = 0; i < sizeof(DOUBLERESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        *_pointer = EEPROM.read(offset);
      }
      
      return DOUBLERESETDETECTOR_FLAG;
    }
#elif (DRD_GENERIC_USE_SAM_DUE)
    uint32_t readFlagSAM_DUE(void)
    {           
      byte* dataPointer = (byte* ) dueFlashStorage.readAddress(DRD_EEPROM_START);
      
      memcpy(&DOUBLERESETDETECTOR_FLAG, dataPointer, sizeof(DOUBLERESETDETECTOR_FLAG));  
      
      return DOUBLERESETDETECTOR_FLAG;
    }
#elif DRD_GENERIC_USE_NRF52
    uint32_t readFlagNRF52(void)
    {           
      DRD_file.open(DRD_FILENAME, FILE_O_READ);
      
      if (DRD_file)
      {
        DRD_file.seek(DRD_FLAG_OFFSET);
        DRD_file.read((char *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));

#if (DRD_GENERIC_DEBUG)
        Serial.println("LittleFS Flag read = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
#endif

        DRD_file.close(); 
      }
      else
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("Loading DRD file failed");
#endif
      }
           
      return DOUBLERESETDETECTOR_FLAG;
    }
#endif
      
    bool detectRecentlyResetFlag()
    {
#if (DRD_GENERIC_USE_EEPROM)
      EEPROM.get(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);
      doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG;

#elif (DRD_GENERIC_USE_SAMD)
      // SAMD code  
      doubleResetDetectorFlag = readFlagSAMD();
         
#elif (DRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code    
      doubleResetDetectorFlag = readFlagSAM_DUE();
      
#elif DRD_GENERIC_USE_NRF52
      // nRF52 code    
      doubleResetDetectorFlag = readFlagNRF52(); 
        
#endif    //(DRD_GENERIC_USE_EEPROM)

#if (DRD_GENERIC_DEBUG)
      Serial.println("Flag read = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
#endif

      doubleResetDetected = (doubleResetDetectorFlag == DOUBLERESETDETECTOR_GENERIC_FLAG_SET);
      return doubleResetDetected;
    };

    void setRecentlyResetFlag()
    {
      doubleResetDetectorFlag = DOUBLERESETDETECTOR_GENERIC_FLAG_SET;

      DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_GENERIC_FLAG_SET;

#if (DRD_GENERIC_USE_EEPROM)
      EEPROM.put(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);

#if (DRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);
#endif

#elif (DRD_GENERIC_USE_SAMD)
      // SAMD code     
      uint16_t offset   = DRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &DOUBLERESETDETECTOR_FLAG;
      
      for (int i = 0; i < sizeof(DOUBLERESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
      
      EEPROM.commit();
      
#if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAMD();
#endif      

#elif (DRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(DRD_EEPROM_START, (byte *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));
      
#if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
#endif

#elif DRD_GENERIC_USE_NRF52
      // nRF52 code
      DRD_file.open(DRD_FILENAME, FILE_O_WRITE);
      
#if (DRD_GENERIC_DEBUG)
      Serial.print("Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0x");
      Serial.println(String(DOUBLERESETDETECTOR_FLAG, HEX));
#endif

      if (DRD_file)
      {
        DRD_file.seek(DRD_FLAG_OFFSET);
        DRD_file.write((uint8_t *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));
        DRD_file.close();
#if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file OK");
#endif
      }
      else
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file failed");
#endif
      }      
#endif    //(DRD_GENERIC_USE_EEPROM)

#if (DRD_GENERIC_DEBUG)
      Serial.println("SetFlag write = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
#endif
    };

    void clearRecentlyResetFlag()
    {
      doubleResetDetectorFlag = DOUBLERESETDETECTOR_GENERIC_FLAG_CLEAR;
      DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_GENERIC_FLAG_CLEAR;

#if (DRD_GENERIC_USE_EEPROM)
      EEPROM.put(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);

#if (DRD_GENERIC_DEBUG)
      delay(1000);
      EEPROM.get(DRD_EEPROM_START, DOUBLERESETDETECTOR_FLAG);
#endif

#elif (DRD_GENERIC_USE_SAMD)
      // SAMD code     
      uint16_t offset   = DRD_EEPROM_START;               
      uint8_t* _pointer = (uint8_t *) &DOUBLERESETDETECTOR_FLAG;
      
      for (int i = 0; i < sizeof(DOUBLERESETDETECTOR_FLAG); i++, _pointer++, offset++)
      {              
        EEPROM.write(offset, *_pointer);
      }
      
      EEPROM.commit();
      
#if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAMD();
#endif      

#elif (DRD_GENERIC_USE_SAM_DUE)
      // SAM DUE code           
      dueFlashStorage.write(DRD_EEPROM_START, (byte *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG));
      
#if (DRD_GENERIC_DEBUG)
      delay(1000);
      readFlagSAM_DUE();
#endif

#elif DRD_GENERIC_USE_NRF52

      // nRF52 code
      DRD_file.open(DRD_FILENAME, FILE_O_WRITE);
#if (DRD_GENERIC_DEBUG)
      Serial.print("Saving to DRD file : 0x");
      Serial.println(String(DOUBLERESETDETECTOR_FLAG, HEX));
#endif

      if (DRD_file)
      {
        DRD_file.seek(DRD_FLAG_OFFSET);
        DRD_file.write((uint8_t *) &DOUBLERESETDETECTOR_FLAG, sizeof(DOUBLERESETDETECTOR_FLAG)); 
   
        DRD_file.close();
#if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file OK");
#endif
      }
      else
      {
#if (DRD_GENERIC_DEBUG)
        Serial.println("Saving DRD file failed");
#endif
      }   
      
      delay(1000);
      readFlagNRF52();
      
#endif    //(DRD_GENERIC_USE_EEPROM)

#if (DRD_GENERIC_DEBUG)
      Serial.println("ClearFlag write = 0x" + String(DOUBLERESETDETECTOR_FLAG, HEX) );
#endif

//#endif    //(DRD_GENERIC_USE_EEPROM)
    };

    uint32_t doubleResetDetectorFlag;
};
#endif // DoubleResetDetector_Generic_H
