#include "AS5600.h"

AS5600 encoder;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(encoder.getPosition());

}
