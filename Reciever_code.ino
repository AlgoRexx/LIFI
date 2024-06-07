#define SOLARPIN A0
#define THRESHOLD 250 //450

int ambientReading = 20;

void setup() {
  pinMode(SOLARPIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(SOLARPIN);
  int bits[10];

  // Listening for the start bit
  if (reading > THRESHOLD) {
    for (int i = 0; i < 10; i++) {
      if (analogRead(SOLARPIN) > THRESHOLD) {
        bits[i] = 1;
      } else {
        bits[i] = 0;
      }
      delay(10);
    }

    int m = 0;
    for (int j = 1; j < 10; j++) {
      if (bits[j] == 1) {
        m = m + (1 << (7 - j));
      }
    }

    char receivedChar = char(m);

    // Check for null or "." and print newline
    if (receivedChar == '\0' || receivedChar == '.') {
      Serial.println();
    } else {
      Serial.print(receivedChar);
    }
  }
}
