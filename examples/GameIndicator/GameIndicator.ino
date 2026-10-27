/*
  GameIndicator — эталонная схема индикатора состояния игры.
  Демонстрирует переключение режимов по состояниям прошивки.

  Карта состояний:
    поиск сети / загрузка   -> RAINBOW (перелив)
    ожидание игрока         -> BLINK  + зелёный (мигание)
    игра идёт               -> NOT_BLINK + зелёный (постоянный)
    низкий заряд            -> BLINK  + красный, быстрый (мигание)

  ВАЖНО: если в setup() есть блокирующий цикл (например, ожидание Wi-Fi),
  вызывайте led.handle() прямо внутри него — иначе радуга замрёт ровно там,
  где игрок ждёт подключения.
*/

#include <LedStatus.h>

using namespace DenChela;

#define PIN_RED 9
#define PIN_GREEN 10
#define PIN_BLUE 11

LedStatus led(PIN_RED, PIN_GREEN, PIN_BLUE);

const uint8_t green[3] PROGMEM = {0, 255, 0};
const uint8_t red[3] PROGMEM = {255, 0, 0};

// Демо-конечный автомат: 0=поиск сети, 1=ожидание игрока, 2=игра, 3=низкий заряд
uint8_t state = 0;
uint32_t stateTime = 0;

void applyState(uint8_t s) {
  switch (s) {
    case 0:  // поиск сети
      led.setMode(LedStatus::RAINBOW);
      Serial.println(F("State: searching network (rainbow)"));
      break;
    case 1:  // ожидание игрока: медленное мигание зелёным
      led.setStepRainbow(20);           // на радугу не влияет, задан для полноты
      led.setTimePeriodBlink(400);
      led.setMode_P(LedStatus::BLINK, green);
      Serial.println(F("State: waiting for player (slow green blink)"));
      break;
    case 2:  // игра идёт: постоянный зелёный
      led.setMode_P(LedStatus::NOT_BLINK, green);
      Serial.println(F("State: game running (solid green)"));
      break;
    case 3:  // низкий заряд: быстрое мигание красным
      led.setTimePeriodBlink(120);
      led.setMode_P(LedStatus::BLINK, red);
      Serial.println(F("State: low battery (fast red blink)"));
      break;
  }
}

void setup() {
  Serial.begin(115200);
  applyState(state);
}

void loop() {
  led.handle();  // обязательно в каждом витке loop()

  // Демо-переключение состояний каждые 6 секунд
  if (millis() - stateTime >= 6000) {
    stateTime = millis();
    state = (state + 1) % 4;
    applyState(state);
  }

  // В реальном проекте applyState() вызывается из мест,
  // где меняется состояние прошивки, а не по таймеру.
}
