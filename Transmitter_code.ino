#define LASERPIN 7  
char message[1000];

void setup() {
  pinMode(LASERPIN, OUTPUT);
  Serial.begin(9600);
  send_message("lifi message");
}

void loop() {
  static char receivedMessage[1000];  // Static to retain its value between loop iterations
  static int messageIndex = 0;

  while (Serial.available() > 0) {
    char receivedChar = Serial.read();

    // Check for newline or max length
    if (receivedChar == '\n' || messageIndex >= sizeof(receivedMessage) - 1) {
      // Null-terminate the string
      receivedMessage[messageIndex] = '\0';

      // Send the complete message
      send_message(receivedMessage);

      // Reset messageIndex for the next message
      messageIndex = 0;
    } else {
      // Add the character to the message
      receivedMessage[messageIndex] = receivedChar;
      messageIndex++;
    }
  }
}


void send_message(char myText[]) {
  int length = strlen(myText);
  Serial.println(length);

  int ar[20];
  int m;
  int bits[8];

  for (int i = 0; i < length; i++) {
    ar[i] = int(myText[i]);
  }

  for (int n = 0; n < length; n++) {
    m = ar[n];
    int z;
    int bin[7];
    int newbin[7];

    for (z = 0; z < 8; z++) {
      bin[z] = m % 2;
      m = m / 2;
    }

    for (int j = 7; j >= 0; j--) {
      newbin[7 - j] = bin[j];
    }

    for (int p = 0; p < 8; p++) {
      if (newbin[p] == 1) {
        bits[p] = HIGH;
      } else {
        bits[p] = LOW;
      }
    }

    bits[0] = HIGH;

    for (int i = 0; i < 8; i++) {
      digitalWrite(LASERPIN, bits[i]);
      delay(10);
    }

    digitalWrite(LASERPIN, LOW);
    delay(50);
  }

  // Display the sent message on the Serial Monitor
  Serial.println("Sent Message: " + String(myText));
}
