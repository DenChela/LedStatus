/*
  Blink — минимальная проверка библиотеки и монтажа.
  Светодиод мигает красным каждые 600 мс.

  Подключение (общий катод): R -> пин красного, G -> пин зелёного,
  B -> пин синего, общий катод -> GND. Резисторы 330–470 Ом на каждый канал.

  На AVR (Uno/Nano) берите PWM-пины: 3, 5, 9, 10, 11 (пин 6 использует
  Timer0 вместе с millis() — возможен лёгкий джиттер ШИМ).
*/

#include <LedStatus.h>

using namespace DenChela;

const uint8_t PIN_RED = 9;
const uint8_t PIN_GREEN = 10;
const uint8_t PIN_BLUE = 11;

LedStatus led(PIN_RED, PIN_GREEN, PIN_BLUE);

uint8_t red[3] = {255, 0, 0};

void setup() {
  led.setMode(LedStatus::BLINK, red);
}

void loop() {
  led.handle();  // вызывать в каждом витке loop()
}
