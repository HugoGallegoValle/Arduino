#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "DIGIFIBRA-2133";
const char* password = "A7TJXB3Q4A";

WebServer server(80);

const int reléPin = 12;

bool estadoLED = false;

void paginaPrincipal() {

String pagina = "<!DOCTYPE html><html>";
pagina += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
pagina += "<style>";
pagina += "body {font-family: Arial; text-align: center; margin-top: 40px;}";
pagina += "button {padding:20px;font-size:20px;margin:10px;}";
pagina += "</style></head>";

pagina += "<body>";
pagina += "<h1>Control LED ESP32</h1>";

if (estadoLED) {
pagina += "<p>MOTOR ENCENDIDO</p>";
pagina += "<a href='/off'><button>APAGAR</button></a>";
} else {
pagina += "<p>MOTOR APAGADO</p>";
pagina += "<a href='/on'><button>ENCENDER</button></a>";
}

pagina += "</body></html>";

server.send(200, "text/html", pagina);
}

void encenderMOTOR() {

estadoLED = true;
digitalWrite(reléPin, HIGH);

paginaPrincipal();
}

void apagarMOTOR() {

estadoLED = false;
digitalWrite(reléPin, LOW);

paginaPrincipal();
}

void setup() {

Serial.begin(115200);

pinMode(reléPin, OUTPUT);

WiFi.begin(ssid, password);

Serial.print("Conectando a WiFi");

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

Serial.println("");
Serial.println("Conectado");

Serial.print("IP del ESP32: ");
Serial.println(WiFi.localIP());

server.on("/", paginaPrincipal);
server.on("/on", encenderMOTOR);
server.on("/off", apagarMOTOR);

server.begin();
}

void loop() {

server.handleClient();

}