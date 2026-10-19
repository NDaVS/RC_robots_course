"""
Отправка нажатий стрелок на Arduino-передатчик через COM-порт.
Установка:  pip install pyserial pynput
Запуск:     python arrow_control.py
Выход:      Esc
"""
import serial
from pynput import keyboard

PORT = "COM3"        # Linux: "/dev/ttyUSB0", macOS: "/dev/cu.usbserial-XXXX"
BAUD = 9600

ser = serial.Serial(PORT, BAUD, timeout=0.1)

KEYS = {
    keyboard.Key.left:  b"L",
    keyboard.Key.right: b"R",
    keyboard.Key.up:    b"U",
    keyboard.Key.down:  b"D",
}

def on_press(key):
    if key == keyboard.Key.esc:
        return False
    if key in KEYS:
        ser.write(KEYS[key])

print("Стрелки: ← → меняют угол, ↑ центр (90°), ↓ 0°. Esc - выход.")
with keyboard.Listener(on_press=on_press) as listener:
    listener.join()
ser.close()
