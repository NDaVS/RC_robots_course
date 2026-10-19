#include <SoftwareSerial.h>

// RX -> TXD модуля (D2)
// TX -> RXD модуля (D3)
SoftwareSerial loraSerial(2, 3);

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  Serial.println("Transmitter Ready!");
}

void loop() {
  // Чтение команды из USB COM-порта и отправка в LoRa
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    // Фильтруем управляющие символы
    if (cmd == 'L' || cmd == 'R' || cmd == 'U' || cmd == 'D') {
      loraSerial.write(cmd);
      Serial.print("Sent: ");
      Serial.println(cmd);
    }
  }

  // Вывод ответов/статусов от LoRa в монитор порта при наличии
  if (loraSerial.available() > 0) {
    Serial.write(loraSerial.read());
  }
}
