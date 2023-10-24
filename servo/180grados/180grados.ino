//Agregamos las libreriras del servo
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 32  // Alto de la pantalla OLED en píxeles
#define OLED_RESET 37   // Pin de reinicio (usar -1 si no se usa)

Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Altura incorrecta, cambie en la libreria Adafruit")
#endif
//Instanciamos nuestro servo
Servo servo;
int pinServo = 26;
int pinBoton = 13;
int pinBoton2 = 4;

void setup() {
  //Inicializamos la posicion del servo
  servo.attach(pinServo, 500, 2500);
  Serial.begin(9600);
  pinMode(pinBoton, INPUT_PULLUP);
  pinMode(pinBoton2, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Limpiar la pantalla
  display.clearDisplay();
}
//Inicializamos la posicion (en grados) del servo
int pos = 0;
void loop() {
  // leer el boton
  int estadoBoton = digitalRead(pinBoton);
  int estadoBoton2 = digitalRead(pinBoton2);

  if (estadoBoton == LOW) {
    if (pos == 180) {
      pos = 180;
    } else {
      pos += 30;
    }
    Serial.println("Boton1 detectado");
  }
  if (estadoBoton2 == LOW) {
    if (pos == 0) {
      pos = 0;
    } else {
      pos -= 30;
    }
    Serial.println("Boton2 detectado");
  }

  servo.write(pos);
  // Limpiar la pantalla
  display.clearDisplay();

  // Mostrar la distancia medida en la pantalla OLED
  display.setTextSize(1.8);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(1, 0);
  display.print("Posicion: ");
  display.print(pos);
  display.println(" °");

  // Mostrar la pantalla
  display.display();

  delay(100);
  /*
  //Movemos el servo a 0 grados
  servo.write(0);
  //Esperamos 1.5 segundos
  delay(1500);
  //Movemos el servo a 180 grados
  servo.write(180);
  //Esperamos 1.5 segundos
  delay(1500);
  */
}