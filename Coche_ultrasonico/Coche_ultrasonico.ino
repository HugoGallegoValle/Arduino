const int TRIG=7;
const int ECHO=8;
int tiempo=0;
int distancia=0;
void setup()
{
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  analogWrite(3,255);
  analogWrite(6,255);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(TRIG, 0);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  tiempo=pulseIn(ECHO, HIGH);
  tiempo=tiempo/2;
  distancia=tiempo*0.034;
  Serial.println(distancia);
  if(distancia<7){
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
  }
  else{
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
  }
}