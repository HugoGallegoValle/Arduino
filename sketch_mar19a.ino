#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <WiFi.h>
#include <WebServer.h>
Adafruit_SSD1306 display(128,64,&Wire,-1);
const char* ssid = "Livebox6-BDBD";
const char* password = "2P9KFhk6oGdc";
WebServer server(80);
int temperatura;
int humedad;
bool boton;
int ea=1;
int luminsoidad;
int tierrahum;
void paginaPrincipal(){
  String pagina = "<!DOCTYPE html><html>";
  pagina += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  pagina += "<style>";
  pagina += "body {font-family: Arial; text-align: center; margin-top: 40px;}";
  pagina += "button {padding:20px;font-size:20px;margin:10px;}";
  pagina += "</style></head>";

  pagina += "<body>";
  pagina += "<h1>Valores actuales</h1>";
  pagina += "<p>Temperatura:"+String(temperatura)+"</p>";
  pagina += "<p>Humedad:" +String(humedad)+"</p>";
  pagina += "<p>Luminosidad:"+String(luminsoidad)+"</p>";
  pagina += "<p>Humedad de la tierra:"+String(tierrahum)+"</p>";
  pagina += "</body></html>";
  server.send(200,"text/html",pagina);
}
DHT termometro(13,11);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("Conectando a WIFI...");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println("¡Estás conectado¡");
  Serial.println("IP");
  Serial.println(WiFi.localIP());
  pinMode(5,INPUT);
  pinMode(33,INPUT);
  pinMode(34,INPUT);
  pinMode(23,OUTPUT);
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar SSD1306"));
    for(;;); // Bucle infinito si hay error
  }
termometro.begin();
server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
temperatura=termometro.readTemperature();
humedad=termometro.readHumidity();
luminsoidad=analogRead(34);
boton=digitalRead(5);
tierrahum=analogRead(33);
server.handleClient();
if(boton){
  if(ea==1){
    digitalWrite(23,HIGH);
    ea=0;
  }
  else{
    digitalWrite(23,LOW);
    ea=1;
    }
}
paginaPrincipal();
}