#include "Arduino.h"
#include "AS5600.h"

AS5600::AS5600()
{
  //set up AS5600
  Wire.begin();

}
long AS5600::getPosition()
{
  return getRegisters2(RAWANGLEAddressMSB, RAWANGLEAddressLSB);  
}

int AS5600::getAngle()
{
  return getRegisters2(ANGLEAddressMSB, ANGLEAddressLSB);  
}

int AS5600::getStatus()
{
  return getRegister(STATUSAddress) & 0b00111000;
}

int AS5600::getGain()
{
  return getRegister(AGCAddress);
}

int AS5600::getMagnitude()
{
  return getRegisters2(MAGNITUDEAddressMSB, MAGNITUDEAddressLSB);
}

int AS5600::getRegister(byte register1)
{
  Wire.beginTransmission(AS5600Address);
  Wire.write(register1);
  Wire.endTransmission();

  Wire.requestFrom(AS5600Address, 1);

  if(Wire.available() <=1) {
    msb = Wire.read();
  }

  return msb;
}

long AS5600::getRegisters2(byte registerMSB, byte registerLSB)
{
  lsb = 0;
  msb = 0;
  
  Wire.beginTransmission(AS5600Address);
  Wire.write(registerMSB);
  Wire.write(registerLSB);
  Wire.endTransmission();
  delay(10);

  Wire.requestFrom(AS5600Address, 2);

  if(Wire.available() <=2) {
    lsb = Wire.read();
    msb = Wire.read();
  }

  return (lsb) + (msb & msbMask) * 256;
}
