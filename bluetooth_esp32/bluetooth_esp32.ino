#include <BluetoothSerial.h>
BluetoothSerial serialbt;
const int motor1_pin = 14;
const int led2_pin= 12;
char mensaje;
float tiempoinicial=0;
float tiempoactual=0;
int potenciometro;
void setup() {
  // put your setup code here, to run once:
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  Serial.begin(115200);
  serialbt.begin("HESP32");
  Serial.println("El bluetooth se ha inicializado correctamente y está listo para emparejarse");
}

void loop() {
  // put your main code here, to run repeatedly:
tiempoactual=millis();
Serial.println(tiempoactual);
if(tiempoactual>=tiempoinicial+2000){
  tiempoinicial=millis();
  int potenciometro=analogRead(32);
  serialbt.println(potenciometro);
}
  if (serialbt.available()) {
    char mensaje = serialbt.read();
    if (mensaje == 'A') {
      digitalWrite(led1_pin, HIGH);
    }
    if (mensaje == 'B') {
      digitalWrite(led1_pin, LOW);
    }
    if (mensaje== 'C'){
      digitalWrite(led2_pin, HIGH);
    }
    if (mensaje== 'D'){
      digitalWrite(led1_pin, LOW);
      digitalWrite(led2_pin, LOW);
    }
  }
}