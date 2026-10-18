/*
  Rainbow — плавная радуга.
  Период шага и величина шага настраиваются сеттерами,
  значения по умолчанию: 70 мс и шаг 20.

  Чем меньше период и чем больше шаг — тем быстрее перелив.
  Настройку можно менять в любой момент, даже во время анимации.
*/

#include <LedStatus.h>

using namespace DenChela;

const uint8_t PIN_RED = 9;
const uint8_t PIN_GREEN = 10;
const uint8_t PIN_BLUE = 11;

LedStatus led(PIN_RED, PIN_GREEN, PIN_BLUE);

void setup() {
  // Разгон перелива: шаг 30, шаг каждые 50 мс
  led.setStepRainbow(30);
  led.setTimePeriodRainbow(50);
  led.setMode(LedStatus::RAINBOW);
}

void loop() {
  led.handle();  // вызывать в каждом витке loop()
}
