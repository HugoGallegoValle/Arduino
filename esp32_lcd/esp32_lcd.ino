#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int segundos=0;
void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.clear();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Hola mundo :-)");
}

void loop() {
  // put your main code here, to run repeatedly:
}