#include "AS5600.h"

AS5600 encoder;
int encoderStatus;
long output = 0;
int encoderPos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  encoderStatus = encoder.getStatus();

  if (encoderStatus == 0b00001000)
    Serial.print("MH  ");
  else if (encoderStatus == 0b00010000)
    Serial.print("ML  ");
  else if (encoderStatus == 0b00100000)
    Serial.print("MD  ");
  else
    Serial.print("Error  ");
  encoderPos = encoder.getPosition();
  output = long(0.5335*(float)output + 0.4665*(float)encoderPos);

  //Serial.println(encoder.getPosition());

  Serial.println(output);
}
