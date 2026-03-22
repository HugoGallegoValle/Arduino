#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <WiFi.h>
#include <WebServer.h>
Adafruit_SSD1306 display(128,64,&Wire,-1);
const char* ssid = "DIGIFIBRA-2133_EXT";
const char* password = "A7TJXB3Q4A";
WebServer server(80);
int temperatura;
int humedad;
bool boton;
bool ea=true;
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
  pagina += "<p>Temperatura:"+String(temperatura)+"*C</p>";
  pagina += "<p>Humedad:" +String(humedad)+"%</p>";
  pagina += "<p>Luminosidad:"+String(luminsoidad)+"%</p>";
  pagina += "<p>Humedad de la tierra:"+String(tierrahum)+"%</p>";
  pagina +="<h1>Control del rele</h1>";
  if(ea){
     pagina +="<a href='/on'><button>ENCENDER<button></a>";
  }
  else{
    pagina +="<a href='/off'><button>APAGAR<button></a>";
  }
  pagina +="</body></html>";
  server.send(200,"text/html",pagina);
}
void encenderRele(){
    digitalWrite(23,HIGH);
    ea=false;
    paginaPrincipal();
}
void apagarRele(){
  digitalWrite(23,LOW);
  ea=true;
  paginaPrincipal();
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
server.on("/",paginaPrincipal);
server.on("/on",encenderRele);
server.on("/off",apagarRele);
server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
temperatura=termometro.readTemperature();
humedad=termometro.readHumidity();
luminsoidad=map(analogRead(34),0,4095,0,100);
boton=digitalRead(5);
tierrahum=map(analogRead(33),3500,1400,0,100); //1400-3500
if(boton){
  if(ea){
  encenderRele();
  }
  else{
    apagarRele();
  }
}
server.handleClient();
delay(1000);
}