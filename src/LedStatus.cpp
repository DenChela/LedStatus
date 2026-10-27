#include "LedStatus.h"
using namespace DenChela;

LedStatus::LedStatus(const uint8_t _red, const uint8_t _green, const uint8_t _blue):red(_red),green(_green),blue(_blue) {
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
}

LedStatus::~LedStatus() {
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    pinMode(red, INPUT);
    pinMode(green, INPUT);
    pinMode(blue, INPUT);
}

void LedStatus::handle() {
    if (thisStatus == NOT_BLINK) return;
    else if (thisStatus == BLINK && millis() - time >= timePeriodBlink) {
        time = millis();
        bool isTrue = false;
        for (uint8_t i = 0; i < 3; i++) {
            if (position[i] > 0) {
                isTrue = true;
                break;
            }
        }
        if (isTrue) {
            const uint8_t color[] = {0, 0, 0};
            setColor(color);
        }
        else setColor(ledRGB);
    } else if (thisStatus == RAINBOW && millis() - time >= timePeriodRainbow) {
        switch (positionRainbow) {
            case 1:
                if (position[1] < 255 - stepRainbow) position[1] += stepRainbow;
                else {
                    position[1] = 255;
                    positionRainbow++;
                }
                analogWrite(green, position[1]);
                break;
            case 2:
                if (position[0] > stepRainbow) position[0] -= stepRainbow;
                else {
                    position[0] = 0;
                    positionRainbow++;
                }
                analogWrite(red, position[0]);
                break;
            case 3:
                if (position[2] < 255 - stepRainbow) position[2] += stepRainbow;
                else {
                    position[2] = 255;
                    positionRainbow++;
                }
                analogWrite(blue, position[2]);
                break;
            case 4:
                if (position[1] > stepRainbow) position[1] -= stepRainbow;
                else {
                    position[1] = 0;
                    positionRainbow++;
                }
                analogWrite(green, position[1]);
                break;
            case 5:
                if (position[0] < 255 - stepRainbow) position[0] += stepRainbow;
                else {
                    position[0] = 255;
                    positionRainbow++;
                }
                analogWrite(red, position[0]);
                break;
            case 6:
                if (position[2] > stepRainbow) position[2] -= stepRainbow;
                else {
                    position[2] = 0;
                    positionRainbow = 1;
                }
                analogWrite(blue, position[2]);
                break;
            default:
                positionRainbow = 1;
        }
    }
}

void LedStatus::setMode(Mode mode, const uint8_t color[3]) {
    thisStatus = mode;
    for (uint8_t i = 0; i < 3; i++) ledRGB[i] = color[i];
    if (mode == NOT_BLINK || mode == BLINK) setColor(ledRGB);
    else if (mode == RAINBOW) {
        positionRainbow = 1;
        const uint8_t col[] = {255, 0, 0};
        setColor(col);
    }
    time = millis();
}

void LedStatus::setMode(Mode mode) {
    uint8_t col[3];
    if (mode == RAINBOW) for (uint8_t i = 0; i < 3; i++) col[i] = 0;
    else for (uint8_t i = 0; i < 3; i++) col[i] = 255;
    setMode(mode, col);
}

void LedStatus::setMode_P(Mode mode, const uint8_t color[3]) {
    const uint8_t col[3] = {pgm_read_byte(&color[0]), pgm_read_byte(&color[1]), pgm_read_byte(&color[2])};
    setMode(mode, col);
}

void LedStatus::setTimePeriodBlink(const uint16_t timePeriod) {
    if (timePeriod <= 10) return;
    timePeriodBlink = timePeriod;
}

void LedStatus::setTimePeriodRainbow(const uint16_t timePeriod) {
    if (timePeriod <= 10) return;
    timePeriodRainbow = timePeriod;
}

void LedStatus::setStepRainbow(const uint8_t step) {
    if (step == 0) return;
    stepRainbow = step;
}

void LedStatus::setColor(const uint8_t color[3]) {
    for (uint8_t i = 0; i < 3; i++) position[i] = color[i];
    analogWrite(red, position[0]);
    analogWrite(green, position[1]);
    analogWrite(blue, position[2]);
}