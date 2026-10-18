#include <Keypad.h>
const byte filas=4;
const byte columnas=4;
char teclas[filas][columnas]{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte filas_pines[filas]={9,8,7,6};//La librería no admite que estas variables sean constantes
byte columnas_pines[columnas]={5,4,3,2};//La librería no admite que estas variables sean constantes
Keypad teclado = Keypad(makeKeymap(teclas),filas_pines,columnas_pines,filas,columnas);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
char key=teclado.getKey();
if(key){
  Serial.println(key);
}
}
