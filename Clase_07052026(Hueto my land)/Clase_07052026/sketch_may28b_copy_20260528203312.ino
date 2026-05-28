#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <DHT_U.h>
DHT dht(25, DHT11);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
int TRIG=27;
int ECHO=16;
int temperatura;
int humedad;
int luz;
int humedad_tierra;
int humedo;
int nivel;
unsigned int tiempoin;
bool valido;
bool anotar_tiempo=true;
int seco = 2450;
const char* nombre_wifi = "Livebox6-BDBD";
const char* contraseña = "2P9KFhk6oGdc";
const char* token = "8779274087:AAFsUdmRY06VRvewyfIMP3cckJngghY8nAA";
const char* id = "8782494249";
WiFiClientSecure client;
UniversalTelegramBot bot(token, client);
int temperaturamaxima;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(nombre_wifi, contraseña);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar SSD1306"));
    for (;;)
      ;  // Bucle infinito si hay error
  }
  pinMode(25, INPUT);
  pinMode(33, INPUT);
  pinMode(17, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  dht.begin();
  oled.clearDisplay();
}
void mensajes(int numeroMensajesNuevos) {
  for (int i = 0; i < numeroMensajesNuevos; i++) {
    String chat_id = String(bot.messages[i].chat_id);  //Guarda la ID del ususraio que escriba en la string chat_id
    if (chat_id != id) {                               //Comprueba si el usuario somos nosotros
      bot.sendMessage(id, "Usuario no autorizado. ACCESO DENEGADO", "");
      continue;
    }
    String mensaje = bot.messages[i].text;  //Guarda el mensaje i(último) en la variable mensaje
    if (mensaje == "/bomba_on") {
      digitalWrite(17, HIGH);
      bot.sendMessage(id, "Encendiendo la bomba", "");
    }else if (mensaje == "/bomba_off") {
      digitalWrite(17, LOW);
      bot.sendMessage(id, "Apagando la bomba", "");
    }
    else if (mensaje== "/GetInfo"){
      /*bot.sendMessage(id,"Temperatura:",temperatura,"ºC");
      bot.sendMessage(id,"Humedad:",humedad,"%");
      bot.sendMessage(id,"Luminosidad",luminosidad,"%");
      bot.sendMessage(id,"Humedad de la tierra:",humedad_tierra,"%");
      */
    }
    else {
      bot.sendMessage(id, "ERROR al interpretar el mensaje");
    }
}
}
void loop() {
  humedad_tierra=analogRead(33);
  int humedad_tierramap=map(humedad_tierra,0,100,0,4095);
  temperatura = dht.readTemperature();
  if (temperatura > temperaturamaxima) {
    temperaturamaxima = temperatura;
  }
  humedad = dht.readHumidity();
  luz = analogRead(32);
  int luzmap = map(luz,0,100,0,4095);

  oled.clearDisplay();
  oled.setCursor(1, 0);
  oled.setTextSize(0.5);
  oled.setTextColor(WHITE);
  oled.write("Humedad:");
  oled.print(humedad);
  oled.print("%");
  oled.setCursor(1, 10);
  oled.print("Temperatura:");
  oled.print(temperatura);
  oled.drawCircle(86, 10, 1, WHITE);
  oled.setCursor(88, 10);
  oled.print("C");
  oled.setCursor(1, 20);
  oled.print("Luminosidad:");
  oled.print(luz);
  oled.print("%");
  oled.setCursor(1, 30);
  oled.print("Humedad de la tierra:");
  oled.setCursor(50, 40);
  oled.print(humedad_tierra);
  oled.print("%");
  oled.setCursor(1, 55);
  oled.print("Nivel:");
  oled.print(nivel);
  oled.display();

  int numeroMensajesNuevos = bot.getUpdates(bot.last_message_received + 1);
  mensajes(numeroMensajesNuevos);
  digitalWrite(TRIG,0);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  nivel=pulseIn(ECHO, HIGH);
  nivel=nivel/2;
  nivel=nivel*0.034;
  if(nivel>50){
    valido=false;
  }
  if (humedad_tierra > seco) {
    if (luz < 10 && temperaturamaxima >= 25) {
      digitalWrite(17, HIGH);
      if(anotar_tiempo){
        tiempoin=millis();
        anotar_tiempo=false;
      }
      unsigned long tiempo_actual=millis();
      unsigned long tiempo=tiempo_actual-tiempoin;
      if(tiempo>8){
        digitalWrite(17,LOW);
        Serial.println("Nada");
      }
      if (temperaturamaxima > 40) {
        humedo = 300;
        Serial.println(temperatura);
      } else if (temperaturamaxima > 35) {
        humedo = 500;
        Serial.println(temperatura);
      } else if (temperaturamaxima > 30) {
        humedo = 700;
        Serial.println(temperatura);
      } else if (temperaturamaxima > 25) {
        Serial.println(temperatura);
        humedo = 900;
      }

      if (humedad < 30) {
        humedo = humedo - 200;
        Serial.println(humedad);
      } else if (humedad < 50) {
        humedo = humedo - 100;
        Serial.println(humedad);
      } else if (humedad < 70) {
        humedo = humedo + 100;
        Serial.println(humedad);
      } else if (humedo < 90) {
        humedo = humedo + 300;
        Serial.println(humedad);
      } else if (humedo < 100) {
        humedo = humedo + 500;
        Serial.println(humedad);
      }
    }
    if(luz>100 && temperaturamaxima<25){
      if (temperatura>5){
        digitalWrite(17,HIGH);
      }
      if(temperatura<10){
        humedo=humedo+1700;
      }
      else if(temperatura<15){
        humedo=humedo+1500;
      }
      else if(temperatura<20){
        humedo=humedo+1300;
      }
      else{
        humedo=humedo+1100;
      }
    }
  }
  if(humedad_tierra<humedo){
    digitalWrite(17,LOW);
    anotar_tiempo=true;
  }
Serial.println(humedo);
}