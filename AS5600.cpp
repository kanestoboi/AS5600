#include "Arduino.h"
#include "AS5600.h"

AS5600::AS5600()
{
  //set up AS5600
  Wire.begin();

}
long AS5600::getPosition()
{
  return _getRegisters2(_RAWANGLEAddressMSB, _RAWANGLEAddressLSB);  
}

int AS5600::getAngle()
{
  return _getRegisters2(_ANGLEAddressMSB, _ANGLEAddressLSB);  
}

int AS5600::getStatus()
{
  return _getRegister(_STATUSAddress) & 0b00111000;
}

int AS5600::getGain()
{
  return _getRegister(_AGCAddress);
}

int AS5600::getMagnitude()
{
  return _getRegisters2(_MAGNITUDEAddressMSB, _MAGNITUDEAddressLSB);
}

int AS5600::_getRegister(byte register1)
{
  Wire.beginTransmission(_AS5600Address);
  Wire.write(register1);
  Wire.endTransmission();

  Wire.requestFrom(_AS5600Address, 1);

  if(Wire.available() <=1) {
    _msb = Wire.read();
  }

  return _msb;
}

long AS5600::_getRegisters2(byte registerMSB, byte registerLSB)
{
  _lsb = 0;
  _msb = 0;
  
  Wire.beginTransmission(_AS5600Address);
  Wire.write(registerMSB);
  Wire.endTransmission();
  delay(10);

  Wire.requestFrom(_AS5600Address, 1);

  if(Wire.available() <=1) {
    _msb = Wire.read();
  }

  Wire.requestFrom(_AS5600Address, 1);

  Wire.beginTransmission(_AS5600Address);
  Wire.write(registerLSB);
  Wire.endTransmission();

  if(Wire.available() <=1) {
    _lsb = Wire.read();
  }

  return (_lsb) + (_msb & _msbMask) * 256;
}
