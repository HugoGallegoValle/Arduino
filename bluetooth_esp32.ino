#include <BluetoothSerial.h>
BluetoothSerial serialbt;
const int led_pin = 14;
char mensaje;
void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  Serial.begin(115200);
  serialbt.begin("HESP32");
  Serial.println("El bluetooth se ha inicializado correctamente y está listo para emparejarse");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (serialbt.available()) {
    char mensaje = serialbt.read();
    if (mensaje == 'A') {
      digitalWrite(led_pin, HIGH);
    }
    if (mensaje == 'B') {
      digitalWrite(led_pin, LOW);
    }
  }
}