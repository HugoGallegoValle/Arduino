int aleatorio=0;
int led[4]={2,3,4,5};
float tonos[4]={261.626,293.665,329.628,391.995};
int pulsados[100]={};
int posicion=0;
int repeticion=0;
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A2));
}

void loop()
{ 
  //Mostrar la secuencia
for(int i=0;i<posicion;i++){
  digitalWrite(led[pulsados[i]], HIGH);
  tone(6,tonos[pulsados[i]]);
  delay(500);
  digitalWrite(led[pulsados[i]], LOW);
  noTone(6);
  delay(500);
  }
  
  //Nuevo número aleatorio
aleatorio=random(0,4);
digitalWrite(led[aleatorio], HIGH);
tone(6,tonos[aleatorio],200);
delay(200);
digitalWrite(led[aleatorio], LOW);
pulsados[posicion]=aleatorio;
  
  //Comprobar secuencia jugador
for(int i=-1;i<posicion;i++){
  while(digitalRead(7)==LOW && digitalRead(8)==LOW && digitalRead(9)==LOW && digitalRead(10)==LOW); {
  }
  Serial.println(pulsados[i+1]);
  if(digitalRead(7)==HIGH){
    digitalWrite(2,HIGH);
    delay(150);
    digitalWrite(2,LOW);
    if (pulsados[i+1]!=0){
      tone(6,130.81,1500);
      pulsados[50]={};
      posicion=-1;
      delay(1500);
    }
  }
   if(digitalRead(8)==HIGH){
     digitalWrite(3,HIGH);
     delay(150);
     digitalWrite(3,LOW);
     if (pulsados[i+1]!=1){
      	tone(6,130.81,1500);
      	pulsados[50]={};
      	posicion=-1;
        delay(1500);
    }
  }
   if(digitalRead(9)==HIGH){
    	digitalWrite(4,HIGH);
     	delay(150);
     	digitalWrite(4,LOW);
    	if (pulsados[i+1]!=2){
      		tone(6,130.81,1500);
      		pulsados[50]={};
      		posicion=-1;
            delay(1500);
    }
  }
   if(digitalRead(10)==HIGH){
     digitalWrite(5,HIGH);
     delay(150);
     digitalWrite(5,LOW);
     if (pulsados[i+1]!=3){
      	tone(6,130.81,1500);
      	pulsados[50]={};
      	posicion=-1;
        delay(1500);
    }
  }
  delay(500);
  }
  posicion=posicion+1;
  delay(500);
}