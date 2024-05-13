#include "DHTesp.h"

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  dht.setup(15, DHTesp::DHT22); // Configura el pin 15 como entrada del sensor DHT22
}

void loop()
{
  float humedad = dht.getHumidity();
  float temperatura = dht.getTemperature();

  Serial.print("Humedad: ");
  Serial.print(humedad, 1);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.println("°C");

  delay(2000);
}
