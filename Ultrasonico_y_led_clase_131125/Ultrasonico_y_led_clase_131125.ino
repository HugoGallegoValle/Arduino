int echo=11;
int trig=12;
int tiempo=0;
int distancia=0;
int led=2;
void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig, 0);
delayMicroseconds(5);
digitalWrite(trig, HIGH);
tiempo=pulseIn(echo, HIGH);
tiempo=tiempo/2;
distancia=0.034*tiempo;
delay(200);
Serial.println(distancia);
if(distancia<5){
  digitalWrite(led, HIGH);
}
else{
  digitalWrite(led, LOW);
}
}