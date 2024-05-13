#include <MQUnifiedsensor.h>

// Define los pines de conexión
String pin = "32"; //Define el pin analógico donde se conectará el sensor
String type = "MQ-135"; //Define el tipo de sensor MQ
float voltage_Resolution = 3.3; //La resolución de tu ADC
int ADC_Bit_Resolution = 10; //La resolución de tu ADC
int RatioMQ135CleanAir = 3.6; //RS/RO esta es la relación del sensor en aire limpio

MQUnifiedsensor MQ135("Arduino", voltage_Resolution, ADC_Bit_Resolution, pin.toInt(), type);

void setup() {
  Serial.begin(115200);
  MQ135.init();
}

void loop() {
  float calcRatio = MQ135.readSensor(); //Lee el sensor y obtiene la relación RS/RO
  Serial.print("Ratio: ");
  Serial.println(calcRatio);

  float calcGas = MQ135.readSensor(); //Lee el sensor y calcula la concentración de gas
  Serial.print("Concentration: ");
  Serial.println(calcGas);

  delay(1000);
}
