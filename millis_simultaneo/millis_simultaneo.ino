#include <Servo.h>
int tiempo_actual;
int tiempo_referenciaS;
int tiempo_referenciaZ;
Servo myservo;
const int posiciones_servo[]={0,90,180,90};
int indice_servo=0;
int indice_zumbador=0;
const int notas[]={784,659,523,392,523,659,784,0};
const int duracion[]={180,180,180,350,180,180,350,180};
void setup() {
  // put your setup code here, to run once:
myservo.attach(2);
tiempo_referenciaS=millis()+2000;
tiempo_referenciaZ=millis()+500;
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
tiempo_actual=millis();
if(tiempo_referenciaS<=tiempo_actual){
  tiempo_referenciaS=millis()+2000;
  myservo.write(posiciones_servo[indice_servo]);
  indice_servo=indice_servo+1;
  Serial.println(posiciones_servo[indice_servo]);
  if(indice_servo>3){
    indice_servo=0;
  }
}
if(tiempo_referenciaZ<=tiempo_actual){
  tiempo_referenciaZ=millis()+500;
  tone(3,notas[indice_zumbador],duracion[indice_zumbador]);
  indice_zumbador=indice_zumbador+1;
  if(indice_zumbador>7){
    indice_zumbador=0;
  }
}
}