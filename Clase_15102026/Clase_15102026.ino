#include <Wire.h>
#include <Adafruit_PN532.h>

// Definimos los pines I2C por defecto del ESP32
#define PN532_IRQ (4)    // No es obligatorio conectarlo para I2C básico, pero la librería lo pide
#define PN532_RESET (5)  // No es obligatorio conectarlo, se maneja por software

// Inicializamos el módulo usando comunicación I2C
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
int sofia[10]={107,152,66,85};//6B984255
int longitud;
void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);  // Esperar a que se abra el monitor serie

  Serial.println("Buscando módulo NFC PN532...");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("No se encontró la placa PN532. Revisa las conexiones y los interruptores.");
    while (1)
      ;  // Detener el programa si no se encuentra
  }

  // Mostrar datos del chip encontrado
  Serial.print("¡Módulo encontrado! Chip PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);

  // Configurar el módulo para leer etiquetas RFID/NFC
  nfc.SAMConfig();

  Serial.println("Esperando una tarjeta ISO14443A (NFC)...");
}

void loop(void) {
  longitud=0;
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer para guardar el ID único de la tarjeta
  uint8_t uidLength;                        // Longitud del ID (suele ser 4 o 7 bytes)

  // Esperar a que pase una tarjeta por el lector
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("¡Tarjeta NFC detectada!");
    Serial.print("Longitud del código (UID): ");
    Serial.print(uidLength);
    Serial.println(" bytes");
    Serial.print("Código de la tarjeta (HEX): ");
    for (uint8_t i = 0; i < uidLength; i++) {
      if (uid[i] < 0x10) Serial.print("0");
      Serial.print(uid[i]);
      longitud=longitud+1;
    }
    for(int x=0;x<longitud+1;x++){
      if(uid[x]!=sofia[x]){
        Serial.println("Fuera");
        break;
      }
      else{
        if(x==longitud){
          Serial.println("Hola Sofía");
        }
      }
    }
    // Esperar 1 segundo antes de la siguiente lectura para no saturar
    delay(1000);
  }
}