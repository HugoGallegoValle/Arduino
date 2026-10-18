//ÁNODO COMÚN; para cátodo común invertir 0s y 1s
byte numero[10][7]={
  {0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1},
  {0,0,1,0,0,1,0},
  {0,0,0,0,1,1,0},
  {1,0,0,1,1,0,0},
  {0,1,0,0,1,0,0},
  {0,1,0,0,0,0,0},
  {0,0,0,1,1,1,1},
  {0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0},
};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
for(int i=2;i<9;i++){
  pinMode(i,OUTPUT);
}
}

void loop() {
  // put your main code here, to run repeatedly:
for(int x=0;x<10;x++){
  for(int y=2;y<9;y++){
    digitalWrite(y,numero[x][y-2]);
    Serial.println(numero[x][1]);
  }
  delay(1000);
}
}
