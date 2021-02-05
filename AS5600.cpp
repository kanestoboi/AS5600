#include "Arduino.h"
#include "AS5600.h"

AS5600::AS5600() {
  Wire.begin();
}

/*
 * Function: getPosition
 * ----------------------------
 *   returns: the unscaled and unmodified angle from the RAW ANGLE register.
 */
uint16_t AS5600::getPosition() {
  return getRawAngle();
}

/*
 * Function: getAngle
 * ----------------------------
 *   returns: the scaled output value available in the ANGLE register.
 */
uint16_t AS5600::getAngle() {
  return _getRegisters2(_ANGLEAddressMSB, _ANGLEAddressLSB);
}

/*
 * Function: getRawAngle
 * ----------------------------
 *   returns: the unscaled and unmodified angle from the RAW ANGLE register.
 */
uint16_t AS5600::getRawAngle() {
  return _getRegisters2(_RAWANGLEAddressMSB, _RAWANGLEAddressLSB);
}

/*
 * Function: getScaledAngle
 * ----------------------------
 *   returns: the raw angle as a value between 0 and 360 degrees.
 */
float AS5600::getScaledAngle() {
  int ang_hi = _getRegister(_RAWANGLEAddressMSB);
  int ang_lo = _getRegister(_RAWANGLEAddressLSB);
  return ang_hi * 22.5 + ang_lo * 0.087890625;
}

/*
 * Function: getStatus
 * ----------------------------
 *   returns: The the value in the STATUS register. The STATUS register provides bits that indicate the current state of the AS5600.
 *
 *   register format: X X MD ML MH X X X
 *            
 *   MH: AGC minimum gain overflow, magnet too strong
 *   ML: AGC maximum gain overflow, magnet too weak
 *   MD: Magnet was detected
 *
 */
uint8_t AS5600::getStatus() {
  return _getRegister(_STATUSAddress) & 0b00111000;
}

/*
 * Function: isMagnetTooStrong
 * ----------------------------
 *   returns: true if magnet is too close to AS5600.
 */
bool AS5600::isMagnetTooStrong() {
  uint8_t _b=0;
  _b = getStatus();
  if (_b & (1<<5)) { return true; }
  return false;
}

/*
 * Function: isMagnetDetected
 * ----------------------------
 *   returns: true if magnet is too far to AS5600.
 */
bool AS5600::isMagnetTooWeak() {
  uint8_t _b=0;
  _b = getStatus();
  if (_b & (1<<4)) { return true; }
  return false;
}

/*
 * Function: isMagnetDetected
 * ----------------------------
 *   returns: true if magnet is detected by AS5600.
 */
bool AS5600::isMagnetDetected() {
  uint8_t _b=0;
  _b = getStatus();
  if (_b & (1<<3)) { return true; }
  return false;
}

/*
 * Function: getGain
 * ----------------------------
 *   returns: the value contained in the Automatic Gain Control (AGC) register.
 *    
 *   In 5V operation, the AGC range is 0-255 
 *   In 3.3V operation, the AGC range is 0-128
 */
uint8_t AS5600::getGain() {
  return _getRegister(_AGCAddress);
}

/*
 * Function: getMagnet
 * ----------------------------
 *   returns: getGain().
 */
uint8_t AS5600::getMagnet() {
  return getGain();
}

/*
 * Function: getMagnitude
 * ----------------------------
 *   returns: the value contained in the MAGNITUDE REGISTER. The MAGNITUDE register indicates the magnitude value of the
 *            internal Coordinate Rotation Digital Computer (CORDIC). 
 */
uint16_t AS5600::getMagnitude() {
  return _getRegisters2(_MAGNITUDEAddressMSB, _MAGNITUDEAddressLSB);
}

/*
 * Function: _getRegister
 * ----------------------------
 *   register1: register address
 *
 *   returns: the value within a register.
 */
uint8_t AS5600::_getRegister(byte register1) {
  uint8_t _b=0;

  Wire.beginTransmission(_AS5600Address);
  Wire.write(register1);
  Wire.endTransmission();

  Wire.requestFrom(_AS5600Address, 1, 0);

  while (Wire.available() == 0) { }
  _b = Wire.read();

  return _b;
}

/*
 * Function: _getRegister
 * ----------------------------
 *   registerMSB: register address of Most Significant Byte (MMSB)
 *   registerLSB: register address of Least Significant Byte (MMSB)
 *
 *   returns: the value of the 16 bit number stored in registerMSB and registerLSB.
 */
uint16_t AS5600::_getRegisters2(byte registerMSB, byte registerLSB) {
  uint16_t _hi=0, _lo=0;

  _hi = _getRegister(registerMSB);
  _lo = _getRegister(registerLSB);
  return (_hi<<8) | (_lo);
}
