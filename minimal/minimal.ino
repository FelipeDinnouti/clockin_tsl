#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22   // Reset pin
#define SS_PIN  5    // SDA/SS pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(115200);
  while (!Serial);

  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 reader
  Serial.println("Scan a card...");
}

void loop() {
  // Look for a new card
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return; // No new card
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return; // Could not read
  }

  // Print UID
  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Print card type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print("PICC Type: ");
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  // Halt communication with this card so you can scan again
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
