#include <IRremote.h>
int pin=18;
int mando=0;
int valor_final=0;
const int vel_motor1 = 26;
const int pin1_motor1=25;
const int pin2_motor1=17;
const int pin1_motor2=16;
const int pin2_motor2=27;
const int vel_motor2=14;
void setup() {
  // put your setup code here, to run once:
pinMode(vel_motor1, OUTPUT);
pinMode(pin1_motor1, OUTPUT);
pinMode(pin2_motor1, OUTPUT);
pinMode(pin1_motor2, OUTPUT);
pinMode(pin2_motor2, OUTPUT);
pinMode(vel_motor2, OUTPUT);
Serial.begin(115200);
IrReceiver.begin(pin);
}

void loop() {
  // put your main code here, to run repeatedly:
if(IrReceiver.decode()){
  mando=IrReceiver.decodedIRData.decodedRawData;
  Serial.println(mando);
  if(mando==-217252096){
    digitalWrite(vel_motor1, HIGH);
    digitalWrite(pin1_motor1, HIGH);
    digitalWrite(pin2_motor1, LOW);
    digitalWrite(vel_motor2, HIGH);
    digitalWrite(pin1_motor2, HIGH);
    digitalWrite(pin2_motor2, LOW);
  }
  if(mando==-417792256){
    Serial.println("Andamos hacia atrás");
    digitalWrite(vel_motor1, HIGH);
    digitalWrite(pin1_motor1, LOW);
    digitalWrite(pin2_motor1, HIGH);
    digitalWrite(vel_motor2, HIGH);
    digitalWrite(pin1_motor2, HIGH);
    digitalWrite(pin2_motor2, LOW);
  }
  if(mando==-1587609856){
    digitalWrite(vel_motor1, HIGH);
    digitalWrite(pin1_motor1, HIGH);
    digitalWrite(pin2_motor1, LOW);
    digitalWrite(vel_motor2, HIGH);
    digitalWrite(pin1_motor2, LOW);
    digitalWrite(pin2_motor2, HIGH);
  }
  if(mando==-150405376){
    digitalWrite(vel_motor1, HIGH);
    digitalWrite(pin1_motor1, LOW);
    digitalWrite(pin2_motor1, HIGH);
    digitalWrite(vel_motor2, HIGH);
    digitalWrite(pin1_motor2, LOW);
    digitalWrite(pin2_motor2, HIGH);
  }
  if(mando==-484638976){
    digitalWrite(vel_motor1,LOW);
    digitalWrite(vel_motor2,LOW);
  }
  IrReceiver.resume();
}
}