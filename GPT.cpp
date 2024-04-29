#include <WiFiS3.h>
#include <WifiLocation.h>

char ssid[] = SECRET_SSID;  // Reemplaza SECRET_SSID con el nombre de tu red Wi-Fi
char pass[] = SECRET_PASS;  // Reemplaza SECRET_PASS con la contraseña de tu red Wi-Fi
char apiKey[] = SECRET_KEY; // Reemplaza SECRET_KEY con tu clave API de Google Maps

WifiLocation location(apiKey);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
}

void loop() {
  location_t loc = location.getGeoFromWiFi();
  Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());
  Serial.println("Latitude: " + String(loc.lat, 7));
  Serial.println("Longitude: " + String(loc.lon, 7));
  Serial.println("Accuracy: " + String(loc.accuracy));
  delay(10000);
}
