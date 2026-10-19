/*
  ПРИЁМНИК (Arduino #2, с сервоприводом)
  Модуль: SX1278 (Ra-02) 433 МГц, библиотека "LoRa" (Sandeep Mistry)

  Подключение LoRa - так же, как у передатчика (3.3V, D10, D11, D12, D13, D9, D2).
  Сервопривод:
    сигнал (жёлтый/белый) -> D6
    питание (красный)     -> внешние 5 В (не от пина Arduino при нагрузке)
    GND (коричневый)      -> GND, общий с Arduino
*/

#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>

#define LORA_SS   10
#define LORA_RST  9
#define LORA_DIO0 2
#define LORA_FREQ 433E6
#define SERVO_PIN 6

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(90);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed!");
    while (true);
  }
  LoRa.setSyncWord(0x12);   // должно совпадать с передатчиком
  Serial.println("LoRa RX ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize == 0) return;

  String msg = "";
  while (LoRa.available()) {
    msg += (char)LoRa.read();
  }

  if (msg.startsWith("A:")) {
    int angle = constrain(msg.substring(2).toInt(), 0, 180);
    servo.write(angle);
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print("  RSSI: ");
    Serial.println(LoRa.packetRssi());
  }
}
