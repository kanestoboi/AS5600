#include "AS5600.h"

AS5600 encoder;
IntervalTimer AS5600Timer;

int encoderStatus;
long output = 0;
long lastOutput = 0;
long velocity = 0;


int encoderPos;
long setPoint = 4000;

uint8_t stepPin = 5;
uint8_t dirPin = 4;
uint8_t enPin = 6;
uint8_t cfg1Pin = 2;
uint8_t cfg2Pin = 3;

long startI = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  
  setStealthChop();
  setSpreadCycle();
  analogWriteFrequency(stepPin, 2000);
  AS5600Timer.begin(readAS5600, 15000);
}

void loop() {
  // put your main code here, to run repeatedly:
  encoderStatus = encoder.getStatus();

  //stepCheck();

  printEncoderStatus();
  
  
  
  
  
  if (output < setPoint && abs(getError()) > 5) {
    digitalWrite(dirPin, HIGH);
  }
  else if (abs(getError()) > 5) { 
    digitalWrite(dirPin, LOW);
  }

  if (abs(getError()) < 2) {
    analogWrite(stepPin, 0);
   // analogWrite(enPin,200);
  }
  else {
    analogWrite(stepPin, 100);
    digitalWrite(enPin, LOW);
  }

  setPWMFrequency();

  Serial.println(output);
}

void readAS5600() {
  output = encoder.getPosition();

  velocity = long((float)(output - lastOutput)/0.015);
  
  lastOutput = output;
}

void printEncoderStatus() {
  if (encoderStatus == 0b00001000)
    Serial.print("MH  ");
  else if (encoderStatus == 0b00010000)
    Serial.print("ML  ");
  else if (encoderStatus == 0b00100000)
    Serial.print("MD  ");
  else
    Serial.print("Error  ");
}

void stepCheck() {
  
  for (int i = 0; i < 200; i++) {
    output = encoder.getPosition();
    Serial.println(output);
  
    delay(1000);
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
  }
  
}

long getError() {
  return output - setPoint;
}

void setPWMFrequency() {
  long freq = 2000; //long((float)abs(getError()) * 2.0) + 300;
  if ( freq > 100 )
    analogWriteFrequency(stepPin, freq);
  else
    analogWriteFrequency(stepPin, 100);
}

void setStealthChop() {
  pinMode(cfg1Pin, INPUT);
  pinMode(cfg2Pin, INPUT);
}

void setSpreadCycle() {
  pinMode(cfg1Pin, OUTPUT);
  pinMode(cfg2Pin, INPUT);
  digitalWrite(cfg1Pin, LOW);
}

void setMicroStepA4988() {
  pinMode(cfg1Pin, OUTPUT);
  pinMode(cfg2Pin, OUTPUT);
  digitalWrite(cfg1Pin, HIGH);
  digitalWrite(cfg2Pin, HIGH);
}
