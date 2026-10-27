/*
  Rainbow — плавная радуга.
  Период шага и величина шага настраиваются сеттерами,
  значения по умолчанию: 100 мс и шаг 3.

  Чем меньше период и чем больше шаг — тем быстрее перелив.
  Настройку можно менять в любой момент, даже во время анимации.
*/

#include <LedStatus.h>

using namespace DenChela;

#define PIN_RED 9
#define PIN_GREEN 10
#define PIN_BLUE 11

LedStatus led(PIN_RED, PIN_GREEN, PIN_BLUE);

void setup() {
  led.setTimePeriodRainbow(150);
  led.setStepRainbow(2);
  led.setMode(LedStatus::RAINBOW);
}

void loop() {
  led.handle();
}