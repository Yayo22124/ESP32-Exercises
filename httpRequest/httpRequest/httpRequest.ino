#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "StarTI";               // Nombre de tu red WiFi
const char* password = "H1p0dr0m0";        // Contraseña de tu red WiFi
const char* server = "192.168.1.45:2008";  // Dirección IP de tu servidor local

// DHT11
// Incluimos librería
#include <DHT.h>

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Comenzamos el sensor DHT
  dht.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }

  Serial.println("Conexión exitosa a la red WiFi");
}

float h, t, f, hif, hic;

void getData() {
  // put your main code here, to run repeatedly:
  // Esperamos 5 segundos entre medidas

  // Leemos la humedad relativa
  h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  t = dht.readTemperature();
  // Leemos la temperatura en grados Fahrenheit
  f = dht.readTemperature(true);

  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  // Calcular el índice de calor en Fahrenheit
  hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  hic = dht.computeHeatIndex(t, h, false);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    getData();
    HTTPClient http;
    String url = "http://" + String(server) + "/sensorData/insertOne";  // Reemplaza "ruta_del_servidor" con la ruta de tu servidor

    http.begin(url);
    
    http.addHeader("Content-Type","application/json");
    int httpCode = http.POST("{\"humidity\": , \"temperatureC\": 18, \"temperatureF\": 128, \"heathIndexC\": 25, \"heathIndexF\": 52 }");
    
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Respuesta del servidor: " + payload);
    } else {
      Serial.println("Error en la solicitud HTTP");
    }

    http.end();
  }

  delay(15000);  // Realiza la solicitud cada 5 segundos
}
