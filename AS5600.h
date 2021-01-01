/*
  AS5600.h - Library for interacting with the AS5600.
  Created by Kane C. Stoboi, 22 August, 2018.
  Released into the public domain.
*/

#ifndef AS5600_h
#define AS5600_h

#include "Arduino.h"
#include <Wire.h>

class AS5600
{
  public:
    AS5600();
    uint16_t getPosition();

    uint16_t getAngle();
    uint16_t getRawAngle();
    float getScaledAngle();

    uint8_t getStatus();
    uint8_t getGain();
    uint8_t getMagnet();
    uint16_t getMagnitude();
    void setZero();

    bool isMagnetTooStrong();
    bool isMagnetTooWeak();
    bool isMagnetDetected();

    private:
      int _AS5600Address = 0x36;

      byte _ZMCOAddress = 0x00;
      byte _ZPOSAddressMSB = 0x01;
      byte _ZPOSAddressLSB = 0x02;
      byte _MPOSAddressMSB = 0x03;
      byte _MPOSAddressLSB = 0x04;
      byte _MANGAddressMSB = 0x05;
      byte _MANGAddressLSB = 0x06;
      byte _CONFAddressMSB = 0x07;
      byte _CONFAddressLSB = 0x08;
      byte _RAWANGLEAddressMSB = 0x0C;
      byte _RAWANGLEAddressLSB = 0x0D;
      byte _ANGLEAddressMSB = 0x0E;
      byte _ANGLEAddressLSB = 0x0F;
      byte _STATUSAddress = 0x0B;
      byte _AGCAddress = 0x1A;
      byte _MAGNITUDEAddressMSB = 0x1B;
      byte _MAGNITUDEAddressLSB = 0x1C;
      byte _BURNAddress = 0xFF;

      uint16_t _getRegisters2(byte registerMSB, byte registerLSB);
      uint8_t _getRegister(byte register1);
};

#endif
