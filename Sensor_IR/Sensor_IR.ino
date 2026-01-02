#include <IRremote.hpp>
int pin=11;
int data=0;
bool estado=HIGH;
void setup(){
  Serial.begin(9600);
  IrReceiver.begin(pin, ENABLE_LED_FEEDBACK);
  pinMode(3,OUTPUT);
}
void loop(){
  if(IrReceiver.decode()){
    data=IrReceiver.decodedIRData.decodedRawData,HEX;
    Serial.println(data);
  }
  else{
    data=0;
  }
  if(data==1359){
    Serial.println(estado);
    digitalWrite(3,estado);
    estado=!estado;
  }
  IrReceiver.resume();
  delay(500);
}