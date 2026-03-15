#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
Adafruit_SSD1306 oled(128,64,&Wire,-1);
int temperatura;
int humedad;
bool boton;
int ea=1;
DHT termometro(13,11);
void setup() {
  Serial.begin(9600);
  pinMode(5,INPUT);
  pinMode(23,OUTPUT);
  // put your setup code here, to run once:
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("ERROR 404");
    for(;;);
  }
termometro.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
temperatura=termometro.readTemperature();
humedad=termometro.readHumidity();
boton=digitalRead(5);
oled.clearDisplay();
oled.setTextSize(1);
oled.setTextColor(WHITE);
oled.setCursor(0,0);
oled.print("Hola");
oled.setCursor(0,10);
oled.print(humedad);
oled.display();
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
delay(1000);
}
