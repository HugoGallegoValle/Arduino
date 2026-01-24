#include <VoiceRecognitionV3.h>
#include <SoftwareSerial.h>
VR myvr(2,3);
uint8_t records[7];
uint8_t buf[64];  
void setup() {
  // put your setup code here, to run once:
myvr.begin(9600);
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
int ret=myvr.recognize(buf, 50);
if(ret>0){
  if(buf[1]==3){
    Serial.println("Enciende");
  }
  if(buf[1]==4){
    Serial.println("Apaga");
  }
}
}
