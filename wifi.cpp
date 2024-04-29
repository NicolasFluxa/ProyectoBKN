#include "WiFiS3.h"
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;  // Nombre del WiFi
char pass[] = SECRET_PASS;  // Contraseña WiFi

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  while (!Serial) { // Espera que al monitor serial
    ;
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("¡Comunicación con el módulo WiFi fallida!");
    while (true);  // No continúa si no puede conectarse
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Por favor, actualiza el firmware");
  } // Comprueba la versión

  // Intenta conectarse a la red Wi-Fi
  while (status != WL_CONNECTED) {
    Serial.print("Intentando conectarse a la red: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // Espera 10 segundos antes de intentar de nuevo
    delay(1000);
  }

  Serial.println("¡Conectado a la red Wi-Fi!");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void loop() {
}
