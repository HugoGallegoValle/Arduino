#include <DFRobotDFPlayerMini.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
const char* nombre_wifi="DIGIFIBRA-2133";
const char* contraseña="A7TJXB3Q4A";
const char* token="8779274087:AAFsUdmRY06VRvewyfIMP3cckJngghY8nAA";
const char* id="8782494249";
WiFiClientSecure client;
UniversalTelegramBot bot(token,client);
DFRobotDFPlayerMini altavoz;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
WiFi.mode(WIFI_STA);
WiFi.begin(nombre_wifi,contraseña);
client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
while(WiFi.status()!=WL_CONNECTED){
  Serial.println(".");
  delay(500);
}
Serial.print("CONEXIÓN EXITOSA");
Serial1.begin(9600,SERIAL_8N1,26,25);
altavoz.begin(Serial1);
delay(2000);
altavoz.volume(30);
altavoz.EQ(DFPLAYER_EQ_NORMAL);
altavoz.outputDevice(DFPLAYER_DEVICE_SD);
}
void mensajes(int numeroMensajesNuevos){
  for(int i=0;i<numeroMensajesNuevos;i++){
    String chat_id=String(bot.messages[i].chat_id);
    if(chat_id!=id){
      bot.sendMessage(id,"Usuario no detectado. ACCESO DENEGADO","");
      continue;
    }
    String mensaje=bot.messages[i].text;
    if(mensaje=="llamar_mama"){
      altavoz.play(1);
      bot.sendMessage(id,"Llamando a mamá");
    }
    else{
      bot.sendMessage(id,"comando no reconocido","");
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
int numeroMensajesNuevos=bot.getUpdates(bot.last_message_received+1);
mensajes(numeroMensajesNuevos);
}
