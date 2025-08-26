#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>

// Pin definitions (adjust if needed for your board)
#define SS_PIN 5   // SDA/SS
#define RST_PIN 21 // optional, some boards tie it to EN

MFRC522DriverPinSimple ss_pin(SS_PIN);
MFRC522DriverSPI driver(ss_pin);
MFRC522 mfrc522(driver);

// Store last UID
byte lastUid[10];
byte lastUidSize = 0;

bool sameUid(const MFRC522::Uid &uid) {
  if (uid.size != lastUidSize) return false;
  for (byte i = 0; i < uid.size; i++) {
    if (uid.uidByte[i] != lastUid[i]) return false;
  }
  return true;
}

void rememberUid(const MFRC522::Uid &uid) {
  lastUidSize = uid.size;
  for (byte i = 0; i < uid.size; i++) {
    lastUid[i] = uid.uidByte[i];
  }
}

void setup() {
  Serial.begin(115200);
  mfrc522.PCD_Init();
}

void loop() {
  // Test each one of this functions
  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(250);
    return;
  }

  // // Test seperately
  // if (!mfrc522.PICC_ReadCardSerial()) {
  //   delay(250);
  //   return;
  // }

  // if (!sameUid(mfrc522.uid)) {
  //   Serial.print("UID:");
  //   for (byte i = 0; i < mfrc522.uid.size; i++) {
  //     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
  //     Serial.print(mfrc522.uid.uidByte[i], HEX);
  //   }
  //   Serial.println();
  //   rememberUid(mfrc522.uid);
  // }

  mfrc522.PICC_HaltA();
  delay(800);
}
