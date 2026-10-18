#include <ezTime.h>
#include <WiFi.h>
Timezone reloj;//Creamos un objeto de tipo time
const char* nombre_wifi = "DIGIFIBRA-2133";
const char* contrasena = "A7TJXB3Q4A";
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
WiFi.begin(nombre_wifi,contrasena);
while(WiFi.status()!=WL_CONNECTED){
  Serial.println(".");
  delay(500);
}
Serial.println("Wifi conectado");
waitForSync();
reloj.setLocation(F("Europe/Madrid"));//Especificamos el uso horario https://en.wikipedia.org/wiki/List_of_tz_database_time_zones
}

void loop() {
  // put your main code here, to run repeatedly:
String hora=reloj.dateTime("H:i:s"); //Formato Hora, minuto y segundo
String fecha=reloj.dateTime("d/m/y");//Formato día,mes y año
int h=reloj.hour();//Obtengo la hora de mi ubicación
int m=reloj.minute();//Obtengo los minutos de mi ubicación
int s=reloj.second();//Obtengo los segundos de mi ubicación
int hutc=hour();//Obtengo la hora UTC
int mutc=minute();// Obtengo los minutos UTC
int sutc=second();//Obtengo los segundos UTC
Serial.println(hora);
delay(1000);
}
