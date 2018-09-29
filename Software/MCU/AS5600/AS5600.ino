#include "AS5600.h"

AS5600 encoder;
int encoderStatus;
long output = 0;
int encoderPos;
long setPoint = 2000;

uint8_t stepPin = 3;
uint8_t dirPin = 4;

long startI = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);
  //analogWrite(stepPin, 200);
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
  output = long(0.9332*(float)output + 0.06678*(float)encoderPos);

  if (output < setPoint && abs(output - setPoint) > 50) {
    digitalWrite(dirPin, HIGH);
    takeStep();
    takeStep();
  }
  else if (abs(output - setPoint) > 50) { 
    digitalWrite(dirPin, LOW);
    takeStep();
    takeStep();
  }
  //Serial.println(encoder.getPosition());

  Serial.println(output);
}

void takeStep() {
  digitalWrite(stepPin, HIGH);
  digitalWrite(stepPin, LOW); 
}

