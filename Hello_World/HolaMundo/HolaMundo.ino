  const int LED_PIN = 2;
void setup()
{
  pinMode(LED_PIN, OUTPUT); // Configurar el pin del LED incorporado como salida
}

void loop()
{
  digitalWrite(LED_PIN, HIGH); // Encender el LED
  delay(100); // Esperar un segundo
  digitalWrite(LED_PIN, LOW); // Apagar el LED
  delay(100); // Esperar un segundo
}