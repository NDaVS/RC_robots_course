/*
  ПЕРЕДАТЧИК (Arduino #1, подключена к ПК по USB)
  Модуль: SX1278 (Ra-02) 433 МГц, библиотека "LoRa" (Sandeep Mistry)

  Подключение (Uno/Nano)      LoRa модуль
    3.3V  ------------------  VCC   (НЕ 5V!)
    GND   ------------------  GND
    D10   ------------------  NSS
    D11   ------------------  MOSI
    D12   ------------------  MISO
    D13   ------------------  SCK
    D9    ------------------  RST
    D2    ------------------  DIO0
  Логика Uno 5 В, модуль 3.3 В: на линии D10, D11, D13, D9 поставьте
  делители напряжения (1k/2k) или level shifter.

  Команды из последовательного порта (шлёт Python-скрипт):
    'L' - стрелка влево  -> угол -= STEP_DEG
    'R' - стрелка вправо -> угол += STEP_DEG
    'U' - стрелка вверх  -> угол = 90 (центр)
    'D' - стрелка вниз   -> угол = 0
  Для проверки в Serial Monitor можно вводить a / d / w / s.
*/

#include <SPI.h>
#include <LoRa.h>

#define LORA_SS   10
#define LORA_RST  9
#define LORA_DIO0 2
#define LORA_FREQ 433E6

const int STEP_DEG = 5;
int angle = 90;

void sendAngle() {
  LoRa.beginPacket();
  LoRa.print("A:");
  LoRa.print(angle);
  LoRa.endPacket();
  Serial.print("Sent angle: ");
  Serial.println(angle);
}

void setup() {
  Serial.begin(9600);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed!");
    while (true);
  }
  LoRa.setSyncWord(0x12);
  Serial.println("LoRa TX ready");
  sendAngle();
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    bool changed = true;

    switch (c) {
      case 'L': case 'a': angle -= STEP_DEG; break;
      case 'R': case 'd': angle += STEP_DEG; break;
      case 'U': case 'w': angle = 90;        break;
      case 'D': case 's': angle = 0;         break;
      default: changed = false;
    }

    if (changed) {
      angle = constrain(angle, 0, 180);
      sendAngle();
    }
  }
}
