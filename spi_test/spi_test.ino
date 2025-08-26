#include <SPI.h>

#define RST_PIN 21
#define SS_PIN 5

void setup() {
  Serial.begin(115200);
  while (!Serial);

  SPI.begin(18, 19, 23); // SCK=18, MISO=19, MOSI=23

  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);

  delay(1000);
  // Serial.println("Starting MFRC522 version test...");
}

uint8_t readReg(uint8_t addr) {
  digitalWrite(SS_PIN, LOW);
  SPI.transfer((addr << 1) & 0x7E | 0x80);  // Read command
  uint8_t val = SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);
  return val;
}

void loop() {
  uint8_t ver = readReg(0x37);
  Serial.printf("VersionReg = 0x%02X\n", ver);
  delay(1000);
}
