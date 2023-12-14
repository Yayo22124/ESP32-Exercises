//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

const int trigPin = 12;
const int echoPin = 14;

#include "BluetoothSerial.h"

// L298D Pins
int OUT1 = 2;
int OUT2 = 4;
int OUT3 = 16;
int OUT4 = 17;
int BUZZER_PIN = 5;


//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234";  // Change this to more secure PIN.

String device_name = "Amauri-Movil";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  // L298D
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);  // Configura el pin del buzzer como salida

  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
//Serial.printf("The device with name \"%s\" and MAC address %s is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str(), SerialBT.getMacString()); // Use this after the MAC method is implemented
#ifdef USE_PIN
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
#endif
}

char command;

void loop() {
  if (Serial.available()) {
    command = SerialBT.read();
    SerialBT.write(command);
  }
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.write(command);
    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the pulse duration from the echo pin
    long duration = pulseIn(echoPin, HIGH);

    // Calculate the distance based on the speed of sound (343 meters/second)
    // and the formula: distance = speed * time / 2
    float distance = (duration * 0.0343) / 2;

    // Print the measured distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Verifica la distancia antes de ejecutar el comando
    if (distance > 10) {
      // Solo permite retroceder si la distancia es mayor a 10 cm o si el comando es retroceder
      switch (command) {
        case 'F':
          Serial.write("Avanza");
          avanza();
          break;
        case 'B':
          Serial.write("Retrocede");
          retrocede();
          break;
        case 'R':
          Serial.write("Derecha");
          giraDerecha();
          break;
        case 'L':
          Serial.write("Izquierda");
          giraIzquierda();
          break;
        case 'S':
          Serial.write("Detener");
          detener();
          break;
        case 'H':
          Serial.write("Bocina");
          activarClaxon();
          break;
      }
    } else {
       activarClaxon();
      // Si la distancia es menor a 10 cm y el comando es retroceder, detén el vehículo
      if (command == 'B') {
        retrocede();
        Serial.write("Distancia muy corta, deteniendo el vehículo");
      } else if (command == 'S') {
        detener();
      } else if (command == 'H') {
        activarClaxon();
      }
    }
  }
  delay(20);
}


void giraDerecha() {
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, HIGH);
}

void avanza() {
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, HIGH);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, HIGH);
}

void giraIzquierda() {
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, HIGH);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);
}

void retrocede() {
  digitalWrite(OUT1, HIGH);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, HIGH);
  digitalWrite(OUT4, LOW);
}

void detener() {
  digitalWrite(OUT1, LOW);
  digitalWrite(OUT2, LOW);
  digitalWrite(OUT3, LOW);
  digitalWrite(OUT4, LOW);
}

void activarClaxon() {
  // Agrega aquí la lógica para activar el claxon (buzzer)
  digitalWrite(BUZZER_PIN, HIGH);  // Activa el buzzer  
  delay(100);                    // Cambia el tiempo según lo que desees
  digitalWrite(BUZZER_PIN, LOW);   // Desactiva el buzzer
}

float medirDistancia() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the speed of sound (343 meters/second)
  // and the formula: distance = speed * time / 2
  float distance = (duration * 0.0343) / 2;

  // Print the measured distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
  // Agrega lógica adicional según sea necesario
}
