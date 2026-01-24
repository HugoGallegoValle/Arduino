int sensor_izq;
int sensor_der;
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
  sensor_izq=analogRead(A4);
  sensor_der=analogRead(A5);
  if(sensor_der>200 && sensor_izq>200){
    Serial.println("2");
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
  }
  else if(sensor_der>200){
    Serial.println("1");
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
  }
  else if(sensor_izq>200){
    Serial.println("1,5");
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
  }
  else{
    Serial.println("Ninguno");
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(9,HIGH);
  }
}