#include <ezTime.h>
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
int TRIG = 27;
int ECHO = 16;
int temperatura;
int humedad;
int luz;
int humedad_tierra;
int humedo;
int nivel;
int seco = 2400;
const char* nombre_wifi = "DIGIFIBRA-2133";
const char* contrasena = "A7TJXB3Q4A";
const char* token = "8779274087:AAFsUdmRY06VRvewyfIMP3cckJngghY8nAA";
const char* id = "8782494249";
bool correcto=true;
WiFiClientSecure client;
UniversalTelegramBot bot(token, client);
int temperaturamaxima;
Timezone reloj;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(nombre_wifi, contrasena);
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
  waitForSync();
  reloj.setLocation(F("Europe/Madrid"));
}
void comprobar_humedad(int humedad) {
  if (humedad < 30) {
    humedo = humedo - 200;
  } else if (humedad < 50) {
    humedo = humedo - 100;
  } else if (humedad < 70) {
    humedo = humedo + 100;
  } else if (humedad < 90) {
    humedo = humedo + 300;
  } else if (humedad < 100) {
    humedo = humedo + 500;
  }
  bot.sendMessage(id,"Regando","");
  info();
  int tiempo_inicial=millis();
  while(humedo<humedad_tierra && correcto){
    int tiempo=millis();
    general();
    delay(1000);
    if(tiempo-tiempo_inicial>10000){
      if(humedad_tierra>seco){
        bot.sendMessage(id,"El sistema de riego está experimentando un error, cuando solucione el rpoblema reinicie el sistema");
        digitalWrite(17,LOW);
        correcto=false;
      }
    }
  }
  digitalWrite(17,LOW);
}
void general(){
  humedad = dht.readHumidity();
  luz = analogRead(32);
  humedad_tierra = analogRead(33);
  digitalWrite(TRIG, 0);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  nivel = pulseIn(ECHO, HIGH);
  nivel = nivel / 2;
  nivel = nivel * 0.034;
  temperatura = dht.readTemperature();
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
  oled.setCursor(1, 55);
  oled.print("Nivel:");
  oled.print(nivel);
  oled.display();
}
void info(){
      String info;
      info +="Temperatura:";
      info +=temperatura;
      info +="ºC";
      info +="Humedad:";
      info +=humedad;
      info +="%";
      info +="Humedad de la tierra";
      info +=humedad_tierra;
      info +="Luminosidad ambiental";
      info +=luz;
      info +="Nivel de agua:";
      info +=nivel;
      info +="Importante:";
      info +=humedo;
      bot.sendMessage(id,info,"");
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
    } else if (mensaje == "/bomba_off") {
      digitalWrite(17, LOW);
      bot.sendMessage(id, "Apagando la bomba", "");
    } 
    else if(mensaje=="/get_info"){
      info();
    }
    else {
      bot.sendMessage(id, "ERROR al interpretar el mensaje");
    }
  }
}
void loop() {
  general();
  humedo=0;
  if(nivel>12 && correcto){
    bot.sendMessage(id,"El nivel de agua es muy bajo","");
    correcto=false;
  }
  if (temperatura > temperaturamaxima) {
    temperaturamaxima = temperatura;
  }
  if(reloj.hour()==0){
    temperaturamaxima=0;
    String tm;
    tm = temperaturamaxima;
    bot.sendMessage(id,tm,"");
  }
  int numeroMensajesNuevos = bot.getUpdates(bot.last_message_received + 1);
  mensajes(numeroMensajesNuevos);
  if (humedad_tierra > seco) {
    if (luz < 10 && temperaturamaxima > 25) {
      if (temperaturamaxima > 40) {
        humedo = 800;
      } else if (temperaturamaxima > 35) {
        humedo = 1000;
      } else if (temperaturamaxima > 30) {
        humedo = 1200;
      } else if (temperaturamaxima > 25) {
        humedo = 1400;
      }
      comprobar_humedad(humedad);
      digitalWrite(17, HIGH);
    }

    if (luz > 100 && temperaturamaxima < 25) {
      if (temperatura > 5) {
        if (temperatura < 10) {
          humedo = humedo + 2000;
        } else if (temperatura < 15) {
          humedo = humedo + 1800;
        } else if (temperatura < 20) {
          humedo = humedo + 1600;
        } else {
          humedo = humedo + 2000;
        }
        digitalWrite(17,HIGH);
        comprobar_humedad(humedad);
      }
    }
  }
}
//8779274087:AAFsUdmRY06VRvewyfIMP3cckJngghY8nAA