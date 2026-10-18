#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <ezTime.h>
#include <WiFi.h>
const char* red="DIGIFIBRA-2133";
const char* contrasena="A7TJXB3Q4A";
Adafruit_SSD1306 pantalla(128,64,&Wire,-1);
Timezone reloj;
void setup() {
  // put your setup code here, to run once:
WiFi.begin(red,contrasena);
Serial.begin(9600);
  if (!pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar SSD1306"));
    for (;;)
      ;  // Bucle infinito si hay error
  }
while(WiFi.status()!=WL_CONNECTED){
  Serial.print(".");
  delay(500);
}
waitForSync();
reloj.setLocation(F("Europe/Madrid"));
pantalla.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
String hora=reloj.dateTime("H:i:s");
pantalla.clearDisplay();
pantalla.setCursor(20,28);
pantalla.setTextColor(WHITE);
pantalla.setTextSize(2);
pantalla.println(hora);
pantalla.display();
}
