
/*
  Test SPI v0.01: MASTER
  RnD - Research and development
  for Technolab ARDU Vex V5
  with STL32L051 microcontrollers.
  Library Vex5 from author potor 10.05.2019
*/

#define BAUDRATE_SPI 1000
// www.arduino.cc/en/Reference/SPI
// Arduino Mega2560 pin SS == 53
// ??? lib vex5: pin SS == 39

//#define CHIP_SELECT    39
#define CHIP_SELECT    53
#define ID_COUNT        5
#define ID_MIN          0
#define ID_MAX          ID_COUNT - 1
#define ID_STEP         1
#include <SPI.h>

uint8_t buf[ID_COUNT] = {0xC0, 0xD0, 0xE0, 0xFF, 0xFA};
uint8_t id = ID_MIN;
void setup() {
  Serial.begin(115200);
  Serial.println("Test SPI v0.01.");
  Serial.println("Date: 31.12.2021.");
  Serial.println("Goal: Technolab ARDU Vex V5.");
  Serial.println("With Git repository.");
  Serial.println("\nI am MASTER!");
  delay(2000);
  // Settings for SPI
  // ?? In lib vex5 first SPI.begin();
//  pinMode(CHIP_SELECT, OUTPUT);
//  digitalWrite(CHIP_SELECT, HIGH);
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
  // In example arduino.ru/forum/programmirovanie/dvustoronnii-obmen-po-spi 
  // ...after set SS
  SPI.begin();
  delay(50);
}

void loop() {
  // From technolab-examen lib: 
  // SPI.beginTransaction(SPISettings(speed, MSBFIRST, SPI_MODE0));
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
//  digitalWrite(CHIP_SELECT, LOW);
  digitalWrite(SS, LOW);
  delay(50);

  // Serial.println("Mock func: SPI transfer()...");
  Serial.println("SPI transfer() buf[] to slave...");
  // Slave side: buf[id] >> 4, e. g. 0xC0 -> 0x0C, 0xFF -> 0x0F etc.
  uint8_t slaveResponse = SPI.transfer(buf[id]);
  delay(1);
  Serial.println("buf[" + String(id) + "]: " + String(buf[id]));
  Serial.println("slaveResponse: " + String(slaveResponse));
  id++;
  if (id > ID_MAX) {
    id = ID_MIN;
  }
  delay(1000);
//  digitalWrite(CHIP_SELECT, HIGH);
  digitalWrite(SS, HIGH);
  SPI.endTransaction();
  delay(100);
}
