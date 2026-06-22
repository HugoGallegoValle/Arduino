#include <IRremote.h>
int pin=18;
int mando=0;
int valor_final=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
IrReceiver.begin(pin);
pinMode()
}

void loop() {
  // put your main code here, to run repeatedly:
if(IrReceiver.decode()){
  mando=IrReceiver.decodedIRData.decodedRawData;
  Serial.println(mando);
  if(mando==-217252096){
    Serial.println("Andamos hacia delante");
  }
  if(mando==-417792256){
    Serial.println("Andamos hacia atrás");
  }
  if(mando==-1587609856){
    Serial.println("Hacia la izquierda");
  }
  if(mando==-150405376){
    Serial.println("Hacia la derecha");
  }
  if(mando==-484638976){
    Serial.println("paramos");
  }
  IrReceiver.resume();
}
}