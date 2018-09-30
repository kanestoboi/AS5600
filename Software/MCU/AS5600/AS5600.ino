#include "AS5600.h"

AS5600 encoder;
int encoderStatus;
long output = 0;
int encoderPos;
long setPoint = 2000;

uint8_t stepPin = 5;
uint8_t dirPin = 4;
uint8_t cfg1Pin = 2;
uint8_t cfg2Pin = 3;

long startI = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(cfg1Pin, INPUT);
  pinMode(cfg1Pin, INPUT);
  digitalWrite(dirPin, HIGH);
  analogWrite(stepPin, 200);
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
  
  output = encoder.getPosition();
  
  
  if (output < setPoint && abs(output - setPoint) > 5) {
    digitalWrite(dirPin, HIGH);
  }
  else if (abs(output - setPoint) > 5) { 
    digitalWrite(dirPin, LOW);
  }

  if (abs(output - setPoint) < 20) {
    analogWrite(stepPin, 0);
  }
  else {
    analogWrite(stepPin, 200);
  }

  Serial.println(output);
}
