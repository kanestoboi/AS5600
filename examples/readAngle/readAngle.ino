#include <AS5600.h>

AS5600 encoder;
double output;

void setup() {
  Serial.begin(9600);
}

void loop() {
  output = encoder.getPosition(); // get the absolute position of the encoder
  Serial.println(output);
}
