#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include "DHTesp.h"
#include <SDS011.h>


#define WIFI_SSID "Andres_2.4"
#define WIFI_PASSWORD "Alicia97"
#define API_KEY "AIzaSyBEnIgOIGNnni0xBfT7E9XrwQsxkFgyoFs"
#define DATABASE_URL "https://medicioncalidaddeaire-default-rtdb.firebaseio.com/" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "4m813n74l@gmail.com"
#define USER_PASSWORD "Proyecto01"

#define MQ135_PIN 32 // Conecta tu MQ135 a la entrada analógica 2

#define RXD2 34 // Define los pines de conexión "al revez funciona"
#define TXD2 35

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Crea una instancia de SDS011
DHTesp dht;
SDS011 my_sds;



void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;

  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);

  // Configura el pin 15 como entrada del sensor DHT22
  dht.setup(15, DHTesp::DHT22);
  // Inicia la comunicación serial con el sensor SDS011
  my_sds.begin(RXD2, TXD2);

}

void loop()
{
  float humedad = dht.getHumidity();
  float temperatura = dht.getTemperature();
  int mq135_value = analogRead(MQ135_PIN)/4;
  float p25, p10;
  int error = my_sds.read(&p25, &p10);


  // Genera una clave única con push() para cada sensor
  String pathMQ135 = "/Sensores/MQ-135/";
  String pathPM25 = "/Sensores/PM-2,5/";
  String pathPM10 = "/Sensores/PM-10/";
  String pathHumedad = "/Sensores/Humedad/";
  String pathTemperatura = "/Sensores/Temperatura/";

  if (!error) {
    Firebase.pushInt(fbdo, pathPM25, p25);

    Firebase.pushInt(fbdo, pathPM10, p10);

  }

  if (Firebase.ready()) { // Si Firebase está listo...

    Firebase.pushFloat(fbdo, pathHumedad, humedad);

    Firebase.pushFloat(fbdo, pathTemperatura, temperatura);

    Firebase.pushInt(fbdo, pathMQ135, mq135_value);
    delay(60000);
  }
}