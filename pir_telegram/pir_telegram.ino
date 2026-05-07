#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
const char* nombre_wifi = "Livebox6-BDBD";
const char* contraseña = "2P9KFhk6oGdc";
const char* token = "8779274087:AAFsUdmRY06VRvewyfIMP3cckJngghY8nAA";
const char* id = "8782494249";
WiFiClientSecure client;
UniversalTelegramBot bot(token, client);
bool movimiento=false;
int pin_pir=27;
void IRAM_ATTR funcion() { 
  movimiento=true;
}
void setup() {
  pinMode(pin_pir, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin_pir),funcion, RISING);
  WiFi.mode(WIFI_STA);
  WiFi.begin(nombre_wifi, contraseña);
  Serial.begin(115200);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Certificado Raíz para api.telegram.org - Almacenado en la librería
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
  bot.sendMessage(id, "Hola", "");
  pinMode(25, OUTPUT);
}
void mensajes(int numeroMensajesNuevos) {
  for (int i = 0; i < numeroMensajesNuevos; i++) {
    String chat_id = String(bot.messages[i].chat_id);  //Guarda la ID del ususraio que escriba en la string chat_id
    if (chat_id != id) {                               //Comprueba si el usuario somos nosotros
      bot.sendMessage(id, "Usuario no autorizado. ACCESO DENEGADO", "");
      continue;
    }
    String mensaje = bot.messages[i].text;  //Guarda el mensaje i(último) en la variable mensaje
    if (mensaje == "/zumbador_on") {
      digitalWrite(25, HIGH);
      bot.sendMessage(id, "Encendiendo el zumbador", "");
    } else if (mensaje == "/zumbador_off") {
      digitalWrite(25, LOW);
      bot.sendMessage(id, "Apagando el zumabdor", "");
    } else {
      bot.sendMessage(id, "ERROR al interpretar el mensaje", "");
    }
  }
}
void loop() {
  int numeroMensajesNuevos = bot.getUpdates(bot.last_message_received + 1);
  mensajes(numeroMensajesNuevos);
  if (movimiento) {
    bot.sendMessage(id, "Hay gente en tu casa", "");
  }
  movimiento=false;
}
