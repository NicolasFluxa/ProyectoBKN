#include <SDS011.h>

// Define los pines de conexión
#define RXD2 34
#define TXD2 35

// Crea una instancia de SDS011
SDS011 my_sds;

void setup() {
  // Inicia la comunicación serial
  Serial.begin(115200);

  // Inicia la comunicación serial con el sensor SDS011
  my_sds.begin(RXD2, TXD2);
}

void loop() {
  // Lee los datos del sensor SDS011
  float p25, p10;
  int error = my_sds.read(&p25, &p10);
  if (!error) {
    Serial.print("PM2.5: ");
    Serial.print(p25);
    Serial.print("\tPM10: ");
    Serial.println(p10);
  }
  delay(1000);
}
