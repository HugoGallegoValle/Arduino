#include <BluetoothSerial.h>
BluetoothSerial serialbt;
const int vel_motor1 = 26;
const int pin1_motor1=25;
const int pin2_motor1=17;
const int pin1_motor2=16;
const int pin2_motor2=27;
const int vel_motor2=14;
char mensaje;
void setup() {
  // put your setup code here, to run once:
  pinMode(vel_motor1, OUTPUT);
  pinMode(pin1_motor1, OUTPUT);
  pinMode(pin2_motor1, OUTPUT);
  pinMode(pin1_motor2, OUTPUT);
  pinMode(pin2_motor2, OUTPUT);
  pinMode(vel_motor2, OUTPUT);
  Serial.begin(115200);
  serialbt.begin("HESP32");
  Serial.println("El bluetooth se ha inicializado correctamente y está listo para emparejarse");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (serialbt.available()) {
    char mensaje = serialbt.read();
    if (mensaje == 'A') {
      digitalWrite(vel_motor1, HIGH);
      digitalWrite(pin1_motor1, HIGH);
      digitalWrite(pin2_motor1, LOW);
      digitalWrite(vel_motor2, HIGH);
      digitalWrite(pin1_motor2, HIGH);
      digitalWrite(pin2_motor2, LOW);
    }
    if (mensaje == 'B') {
      digitalWrite(vel_motor1, HIGH);
      digitalWrite(pin1_motor1, LOW);
      digitalWrite(pin2_motor1, HIGH);
      digitalWrite(vel_motor2, HIGH);
      digitalWrite(pin1_motor2, HIGH);
      digitalWrite(pin2_motor2, LOW);
    }
    if (mensaje == 'C') {
      digitalWrite(vel_motor1, HIGH);
      digitalWrite(pin1_motor1, HIGH);
      digitalWrite(pin2_motor1, LOW);
      digitalWrite(vel_motor2, HIGH);
      digitalWrite(pin1_motor2, LOW);
      digitalWrite(pin2_motor2, HIGH);
    }
    if (mensaje == 'D') {
      digitalWrite(vel_motor1, HIGH);
      digitalWrite(pin1_motor1, LOW);
      digitalWrite(pin2_motor1, HIGH);
      digitalWrite(vel_motor2, HIGH);
      digitalWrite(pin1_motor2, LOW);
      digitalWrite(pin2_motor2, HIGH);
    }
    if(mensaje=='E'){
      digitalWrite(vel_motor1,LOW);
      digitalWrite(vel_motor2,LOW);
    }
  }
}