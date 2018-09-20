

const uint8_t CLOCK_PIN = 5;
const uint8_t DATA_PIN = 6;
const uint8_t NCS_PIN = 7;
const uint8_t BIT_COUNT = 16;

void setup() {
  //setup our pins
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(NCS_PIN, OUTPUT);


  //give some default values
  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(NCS_PIN, LOW);

  Serial.begin(115200);
}


void loop() {
  float reading = readPosition();

  if (reading >= -0.5) {
      Serial.print("Reading: ");
       Serial.println(reading,2);
  }

  delay(500);
}

//read the current angular position
float readPosition() {
  // Read the same position data twice to check for errors
  unsigned long sample1 = shiftIn(DATA_PIN, CLOCK_PIN, BIT_COUNT);
  unsigned long sample2 = shiftIn(DATA_PIN, CLOCK_PIN, BIT_COUNT);
  delayMicroseconds(25);  // Clock mus be high for 20 microseconds before a new sample can be taken

  if (sample1 != sample2)
    return -1.0;

  return ((sample1 & 0x0FFF) * 360UL) / 4096.0;
}

//read in a byte of data from the digital input of the board.
unsigned long shiftIn(const int data_pin, const int clock_pin, const int bit_count) {
  unsigned long data = 0;

  for (int i=0; i<bit_count; i++) {
    data <<= 1;
    digitalWrite(clock_pin,LOW);
    delayMicroseconds(1);
    digitalWrite(clock_pin,HIGH);
    delayMicroseconds(1);

    data |= digitalRead(data_pin);
  }

  return data;
}
