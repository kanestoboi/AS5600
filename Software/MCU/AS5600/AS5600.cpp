#include "Arduino.h"
#include "AS5600.h"

AS5600::AS5600()
{
  //set up AS5600
  Wire.begin();
  
}

int AS5600::getPosition()
{
  return getRegisters2(RAWANGLEAddressMSB, RAWANGLEAddressLSB);  
}

int AS5600::getRegisters2(byte registerMSB, byte registerLSB)
{
  Wire.beginTransmission(AS5600Address);
  Wire.write(registerMSB);
  Wire.write(registerLSB);
  Wire.endTransmission();

  Wire.requestFrom(AS5600Address, 2);

  if(Wire.available() <=2) {
    msb = Wire.read();
    lsb = Wire.read();
  }

  return lsb | (msb & msbMask) << 8;
}

