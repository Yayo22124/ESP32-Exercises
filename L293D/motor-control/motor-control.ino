// Pines del Puente H
int speedPin =  11;
int dirPin1 = 12;
int dirPin2 = 13;
int speedMotor = 225;

void setup() {
  // put your setup code here, to run once:
  // Iniciamos el monitor serial
  Serial.begin(9600);
  pinMode(speedPin, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // direccion
  digitalWrite(dirPin1, 0);
  digitalWrite(dirPin2, 1);
  analogWrite(speedPin, speedMotor);
}
