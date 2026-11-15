#include <Servo.h>
#include <Adafruit_PN532.h>
//#include <ESP32Servo.h>
#include <Wire.h>
#define PN532_IRQ (4)   
#define PN532_RESET (5) 
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
Servo myservo;
bool verificar_tarjeta;
const int servo=2;//13
const int pir=6;//19
const int zumbador=3;//14
const int rgb_rojo=4;//27
const int rgb_verde=5;//26
const int notas[]={784,659,523,392,523,659,784,0};
const int duracion[]={180,180,180,350,180,180,350,180};
const int posiciones_servo[]={90,180,90,0};
const int pin1_tarjeta[]={27,161,34,84};//{9,30,15,149};
unsigned long tiempo_referenciaZ;
unsigned long tiempo_referenciaS;
unsigned long tiempo_actual;
bool estado_servo=true;
bool estado_zumbador=true;
int indice_servo=0;
int indice_zumbador=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);//115200
Serial.println("Binevenido/a");
pinMode(rgb_rojo,OUTPUT);
pinMode(pir,INPUT);
pinMode(rgb_verde,OUTPUT);
myservo.attach(servo);
nfc.begin();
uint32_t versiondata = nfc.getFirmwareVersion();
if (!versiondata) {
  Serial.print("No se encontró la placa PN532. Revisa las conexiones y los interruptores.");
  while (1)
      ;  // Detener el programa si no se encuentra
  }
 // Mostrar datos del chip encontrado
Serial.print("¡Módulo encontrado! Chip PN5");
nfc.SAMConfig();
tiempo_referenciaS=millis()+3000;
tiempo_referenciaZ=millis()+180;

digitalWrite(rgb_rojo,LOW);
digitalWrite(rgb_verde,HIGH);
}
void susto(){
if(tiempo_referenciaS<=tiempo_actual && !estado_servo){
  tiempo_referenciaS=millis()+3000;
  estado_servo=false;
  myservo.write(posiciones_servo[indice_servo]);
  indice_servo=indice_servo+1;
  //Serial.println(posiciones_servo[indice_servo]);
  if(indice_servo>3){
    indice_servo=0;
    estado_servo=true;
  }
}
if(tiempo_referenciaZ<=tiempo_actual){
  tiempo_referenciaZ=millis()+duracion[indice_zumbador];
  tone(zumbador,notas[indice_zumbador]);
  indice_zumbador=indice_zumbador+1;
  if(indice_zumbador>7){
    indice_zumbador=0;
    estado_zumbador=true;
  }
}
}
void loop() {
  // put your main code here, to run repeatedly:
tiempo_actual=millis();
if(estado_servo && estado_zumbador){
  if(digitalRead(pir)!=HIGH){ //==
    estado_servo=false;
    estado_zumbador=false;
  }else{
    noTone(zumbador);
}
}
else{
  susto();
}
verificar_tarjeta=true;
uint8_t success;
uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer para guardar el ID único de la tarjeta
uint8_t uidLength;                        // Longitud del ID (suele ser 4 o 7 bytes)  
success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength,50);
if(success){
  Serial.println(uidLength);
  for(int i=0;i<uidLength;i++){
    Serial.println(uid[i]);
    if(uid[i]!=pin1_tarjeta[i]){
      Serial.println("Mal");
      verificar_tarjeta=false;
    }
  }
  if(verificar_tarjeta){
    digitalWrite(rgb_rojo,HIGH);
    digitalWrite(rgb_verde,LOW);
    Serial.println("ROJO");
    delay(15000);
    digitalWrite(rgb_rojo,LOW);
    digitalWrite(rgb_verde,HIGH);
  }
}
}