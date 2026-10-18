//NOTA IMPORTANTE: para hacer funcionar el proyecto se debe conectar a ordenador o alimentar 5,5V
#include "DFRobotDFPlayerMini.h"  // Incluye la biblioteca para el módulo DFPlayer Mini.
//#include <SoftwareSerial.h>  // Incluye la biblioteca para crear puertos seriales software.

//SoftwareSerial softSerial(4,5);  // Crea un puerto serial usando los pines 4 (RX) y 5 (TX).
DFRobotDFPlayerMini myDFPlayer;  // Crea un objeto para controlar el DFPlayer Mini.

void setup() {
  //softSerial.begin(9600);  // Inicia la comunicación serial en el puerto Serial1 a 9600 bps.
  Serial.begin(9600);
  Serial1.begin(9600);//Para esp 32 borrar líneas:2,4 y 8 y cambiar softSerial por Serial1
  //Serial1 solo funciona a 9600baud.
  myDFPlayer.begin(Serial1);  // esp32:Serial1  Arduino:softSerial
  delay(2000);  // Espera 2 segundos para que el módulo esté listo.
  myDFPlayer.volume(15);  // Establece el volumen a 15.
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);  // Establece el ecualizador a normal.
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);  // Selecciona la tarjeta SD como dispositivo de salida.
}

void loop() {
  myDFPlayer.play(1);  // Reproduce el primer archivo en el primer folder.
  Serial.println("Reproduciendo pista 1");  // Imprime un mensaje en el monitor serial.
  delay(10000);  // Espera 10 segundos.

  myDFPlayer.play(2);  // Reproduce el segundo archivo en el primer folder.
  Serial.println("Reproduciendo pista 2");  // Imprime un mensaje en el monitor serial.
  delay(10000);  // Espera 10 segundos.
}