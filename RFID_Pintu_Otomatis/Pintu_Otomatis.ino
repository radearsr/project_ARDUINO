/* 
 *  Code By RADEARSR
 Pin RFID-RC522  |   Arduino
      3,3v              3,3v
      RST               9
      GND               GND
     SDA/SS             10
      MOSI              11
      MISO              12
      SCK               13
      
Pin Servo = 7
*/
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

Servo myservo; 
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myservo.attach(7);
}

void loop() {
 if ( ! mfrc522.PICC_IsNewCardPresent()){ //Membaca IDcard Baru
  return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()){ //Membaca IDcard yang sudah ada
  return;
  }

 Serial.print("UID tag: ");
 String content = "";
 byte letter;
 
 for (byte i = 0; i < mfrc522.uid.size; i++)
 {
  Serial.print(mfrc522.uid.uidByte[i] <0x10 ? " 0" : " ");
  Serial.print(mfrc522.uid.uidByte[i]);
  content.concat(String(mfrc522.uid.uidByte[i] <0x10 ? " 0" : " "));
  content.concat(String(mfrc522.uid.uidByte[i]));
  }
  Serial.println();
  Serial.print("Pesan: ");
  content.toUpperCase();

  if (content.substring(1) == "119 03 166 181"){
    Serial.println("AKSES MASUK DITERIMA...");
    myservo.write(160);
    delay(4000);
    myservo.write(40);
    delay(1000);
    }
  else{
    Serial.println("AKSES DITOLAK");
    
    }
}
