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
    int getPosition();
    void setZero();
    
    
    private: 
      int AS5600Address = 0x36;
      
      byte ZMCOAddress = 0x00;
      byte ZPOSAddressMSB = 0x01;
      byte ZPOSAddressLSB = 0x02;
      byte MPOSAddressMSB = 0x03;
      byte MPOSAddressLSB = 0x04;
      byte MANGAddressMSB = 0x05;
      byte MANGAddressLSB = 0x06;
      byte CONFAddressMSB = 0x07;
      byte CONFAddressLSB = 0x08;
      byte RAWANGLEAddressMSB = 0x0C;
      byte RAWANGLEAddressLSB = 0x0D;
      byte ANGLEAddressMSB = 0x0E;
      byte ANGLEAddressLSB = 0x0F;
      byte STATUSAddress = 0x0B;
      byte AGCAddress = 0x1A;
      byte MAGNITUDEAddressMSB = 0x1B;
      byte MAGNITUDEAddressLSB = 0x1C;
      byte BURNAddress = 0xFF;

      byte msb;
      byte lsb;
      byte msbMask = 0b00001111;

      int getRegisters2(byte registerMSB, byte registerLSB);
};

#endif
