int inputPin = 4;  // for ESP32 microcontroller
int voicePin = 2;
void setup() {
  pinMode(inputPin, INPUT);
  pinMode(voicePin, OUTPUT);

  delay(60 * 1000);
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(voicePin, HIGH);
  } else {
    digitalWrite(voicePin, LOW);
  }

  delay(10);
}