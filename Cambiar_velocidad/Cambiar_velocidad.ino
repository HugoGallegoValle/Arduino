int velocidades[4]={200,220,235,255};
void setup()
{
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  for(int i=0;i<4;i++){
    analogWrite(6,velocidades[i]);
    analogWrite(3,velocidades[i]);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
    delay(4000);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
    delay(750);
  }
}