#include <AS5600.h>

AS5600 encoder;

int encoderStatus;
long output;
long lastOutput = encoder.getPosition();
float velocity = 0;
long revolutions = 0;
long position = 0;
long deltaPos;
long lastPosition = 0;
long lastMicros = micros();
long PWMFreq = 0;


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
  //setSpreadCycleFull();
  //setStealthChopQuarter();
  //delay(10000);
  analogWriteFrequency(stepPin, 2000);
  analogWrite(stepPin, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
  encoderStatus = encoder.getStatus();

  //stepCheck();

  //printEncoderStatus();
  
  output = encoder.getPosition();
  if ((lastOutput - output) > 2047 )
    revolutions++;
  if ((lastOutput - output) < -2047 )
    revolutions--;

  

  position = revolutions * 4096 + output;
  deltaPos = position-lastPosition;
  lastPosition = position;

  /*
  if (position < setPoint && abs(getError()) > 5) {
    digitalWrite(dirPin, HIGH);
  }
  else if (abs(getError()) > 5) { 
    digitalWrite(dirPin, HIGH);
  }

  if (abs(getError()) < 2) {
    //analogWrite(stepPin, 0);
   // analogWrite(enPin,200);
  }
  else {
    analogWrite(stepPin, 100);
  }
  */

  //setPWMFrequency();

  digitalWrite(dirPin, HIGH);
  velocity = (((float)abs(deltaPos)/(float(11000/*micros() - lastMicros*/)/1000000.0) * 360.0/4096.0));
  lastMicros = micros();

  
  if ((228-velocity) > 100){
    //analogWriteFrequency(stepPin, 125);
    //setSpreadCycleFull();
    //setStealthChopQuarter();
  }
  else{
   //analogWriteFrequency(stepPin, 2000);
   //setStealthChop();
  }
  
  
  
  Serial.println(position);

  
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
  return position - setPoint;
}

void setPWMFrequency() {
  PWMFreq = long((float)abs(getError()) ) + 200;
  if ( PWMFreq > 100 )
    analogWriteFrequency(stepPin, PWMFreq);
  else
    analogWriteFrequency(stepPin, 100);
}

void setStealthChop() {
  pinMode(cfg1Pin, INPUT);
  pinMode(cfg2Pin, INPUT);
}

void setStealthChopQuarter() {
  pinMode(cfg1Pin, OUTPUT);
  pinMode(cfg2Pin, INPUT);
  digitalWrite(cfg1Pin, HIGH);
}

void setSpreadCycle() {
  pinMode(cfg1Pin, OUTPUT);
  pinMode(cfg2Pin, INPUT);
  digitalWrite(cfg1Pin, LOW);
}

void setSpreadCycleFull() {
  pinMode(cfg1Pin, OUTPUT);
  pinMode(cfg2Pin, OUTPUT);
  digitalWrite(cfg1Pin, LOW);
  digitalWrite(cfg2Pin, LOW);
}

void setMicroStepA4988() {
  pinMode(cfg1Pin, OUTPUT);
  pinMode(cfg2Pin, OUTPUT);
  digitalWrite(cfg1Pin, HIGH);
  digitalWrite(cfg2Pin, HIGH);
}
