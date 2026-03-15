#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
int humedad_tierra;
int temperatura;
int humedad;
int luminosidad;
Adafruit_SSD1306 pantalla(128,64,&Wire,-1);
DHT dht(13,DHT11);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(33, INPUT);
  pinMode(32, INPUT);
  Serial.begin(9600);
  if(!pantalla.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
  Serial.println("ERROR 404");
  for(;;);
}
dht.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  pantalla.clearDisplay();
  humedad_tierra=map(100,4000,0,100,analogRead(33));
  temperatura=dht.readTemperature();
  humedad=dht.readHumidity();
  Serial.println(analogRead(32));
  luminosidad=map(analogRead(32),0,4000,0,100);
  pantalla.setCursor(1,10);
  pantalla.setTextSize(1);
  pantalla.setTextColor(WHITE);
  pantalla.write("Humedad:");
  pantalla.print(humedad);
  pantalla.print("%");
  pantalla.setCursor(1,20);
  pantalla.print("Temperatura:");
  pantalla.print(temperatura);
  pantalla.drawCircle(86,20,1,WHITE);
  pantalla.setCursor(88,20);
  pantalla.print("C");
  pantalla.setCursor(1,30);
  pantalla.print("Luminosidad:");
  pantalla.print(luminosidad);
  pantalla.print("%");
  pantalla.setCursor(1,40);
  pantalla.print("Humedad de la tierra:");
  pantalla.setCursor(50,50);
  pantalla.print(humedad_tierra);
  pantalla.display();
  delay(1000);
}