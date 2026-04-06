#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <WiFiClient.h>
#define BLYNK_TEMPLATE_ID "TMPL5gyDWKdfL"
#define BLYNK_TEMPLATE_NAME "LED y DHT11"
#define BLYNK_AUTH_TOKEN "ma7aNuBwOQAWFeSys38Hc6X50Mit9faT"
#include <BlynkSimpleEsp32.h>
DHT dht(5,11);
BlynkTimer timer;
const char* nombre_wifi="DIGIFIBRA-2133";
const char* contraseña="A7TJXB3Q4A";
BLYNK_WRITE(V0){
  int valor=param.asInt();
  digitalWrite(13,valor);
}
void dht11(){
  int temperatura=dht.readTemperature();
  int humedad=dht.readHumidity();
  Blynk.virtualWrite(V1, temperatura);
  Blynk.virtualWrite(V2, humedad);
}
void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
Blynk.begin(BLYNK_AUTH_TOKEN,nombre_wifi,contraseña);
dht.begin();
timer.setInterval(1000L,dht11);
}
void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
timer.run();
}
