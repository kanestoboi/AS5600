#include "AS5600.h"

AS5600 encoder;
int encoderStatus;
int output = 0;

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

  output = long(0.9896*(float)output + 0.01042*(float)encoder.getPosition());

  Serial.println(encoder.getPosition());

  delay(200);

}
