#include <DHT.h>
#include <DHT_U.h>
DHT sensor(11,DHT11);
float temperatura=0;
float humedad=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
sensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
temperatura=sensor.readTemperature();
humedad=sensor.readHumidity();
Serial.print("Temperatura:");
Serial.print(temperatura);
Serial.print("  Humedad:");
Serial.println(humedad);
delay(2000);
}
