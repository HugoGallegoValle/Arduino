#include <DHT.h>
#include <DHT_U.h>

#define BLYNK_TEMPLATE_ID "TMPL5oUHy5rNZ"
#define BLYNK_TEMPLATE_NAME "LED WiFi"
#define BLYNK_AUTH_TOKEN "tCGYY3F4I0VOzr6o58es36kGfUi--Che"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const char* wifi_nombre="Livebox6-BDBD";
const char* contraseña="2P9KFhk6oGdc";
const int pin_LED=19;
DHT termometro(11,15);
BLYNK_WRITE(V0){
  int valor=param.asInt();
  digitalWrite(pin_LED,valor);
}
BLYNK_WRITE(A0){
  int temperatura=termometro.readTemperature();
  Blynk.virtualWrite(A0,temperatura);
}
BLYNK_WRITE(A1){
  int humedad=termometro.readHumidity();
  Blynk.virtualWrite(A1,humedad);
}
void setup() {
  // put your setup code here, to run once:
pinMode(pin_LED, OUTPUT);
Blynk.begin(BLYNK_AUTH_TOKEN, wifi_nombre, contraseña);
termometro.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_LED, HIGH);
  Blynk.run();
}
