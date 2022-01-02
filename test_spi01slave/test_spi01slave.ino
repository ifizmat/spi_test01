
/*
  Test SPI v0.01: SLAVE
  RnD - Research and development
  for Technolab ARDU Vex V5
  with STL32L051 microcontrollers.
  Library Vex5 from author potor 10.05.2019
*/

#define BAUDRATE_SPI 1000

//#define CHIP_SELECT    39
//Arduino UNO: CHIP_SELECT 10
#define CHIP_SELECT    10
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Test SPI v0.01.");
  Serial.println("Date: 01.01.2022.");
  Serial.println("Goal: Technolab ARDU Vex V5.");
  Serial.println("With Git repository.");
  Serial.println("\nI am SLAVE!");
  delay(2000);
  SPI.begin();
  SPI.beginTransaction(SPISettings());
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
//  pinMode(CHIP_SELECT, INPUT);
//  digitalWrite(CHIP_SELECT, HIGH);
  SPI.attachInterrupt();
  delay(50);
}

static volatile uint8_t receivedByte = 0;
static volatile bool byteIsReady = false;

ISR(SPI_STC_vect) {
  receivedByte = SPDR;
//  receivedByte = receivedByte >> 4;
//  SPDR = receivedByte;
//  byteIsReady = true;
  if (!receivedByte) {
//    receivedByte = receivedByte >> 4;
//    SPDR = receivedByte;
    byteIsReady = true;
  }
}

void loop() {
  // Serial.println("Mock func: Slave received...");
  Serial.println("Received byte from Master: " + String(receivedByte));
  if (byteIsReady) {

    Serial.println("Received byte from Master: " + String(receivedByte));
    byteIsReady = false;
  }
  delay(1000);
}
