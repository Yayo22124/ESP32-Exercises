#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64  // Alto de la pantalla OLED en píxeles
#define OLED_RESET    13  // Pin de reinicio (usar -1 si no se usa)

Adafruit_SSD1306 display(OLED_RESET);

const int trigPin = 4;  // Pin TRIG del sensor conectado al ESP32
const int echoPin = 5;  // Pin ECHO del sensor conectado al ESP32

#if (SSD1306_LCDHEIGHT != 32)
#error("Altura incorrecta, cambie en la libreria Adafruit")
#endif

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Limpiar la pantalla
  display.clearDisplay();
}

void loop() {
  long duration, distance;

  // Generar un pulso de 10 microsegundos en el pin TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medir el tiempo de eco (en microsegundos) del pin ECHO
  duration = pulseIn(echoPin, HIGH);

  // Convertir el tiempo a distancia en centímetros (la velocidad del sonido es aproximadamente 343 m/s)
  distance = duration * 0.034 / 2;

  // Limpiar la pantalla
  display.clearDisplay();

  // Mostrar la distancia medida en la pantalla OLED
  display.setTextSize(1.8);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 0);
  display.print("Distancia: ");
  display.print(distance);
  display.println(" cm");

  // Mostrar la pantalla
  display.display();

  delay(1000);  // Espera 1 segundo antes de realizar otra medición
}
