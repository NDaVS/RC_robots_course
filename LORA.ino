#include <SoftwareSerial.h>

// RX подключается к TXD модуля (D2)
// TX подключается к RXD модуля (D3)
SoftwareSerial loraSerial(2, 3); 

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600); 
  Serial.println("System Ready!");
}

void loop() {
  // Если пришли данные от LoRa, выводим их в компьютер
  if (loraSerial.available()) {
    Serial.write(loraSerial.read());
  }
  // Если пришли данные от компьютера, отправляем их в LoRa
  if (Serial.available()) {
    loraSerial.write(Serial.read());
  }
}