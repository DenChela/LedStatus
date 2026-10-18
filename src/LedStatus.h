#pragma once
#include <Arduino.h>

namespace DenChela {

    class LedStatus {

        public:
            enum {
                NOT_BLINK = 0,
                BLINK = 1,
                RAINBOW = 2
            };
            LedStatus(const uint8_t _red, const uint8_t green, const uint8_t blue);
            ~LedStatus();
            //Постоянный мониторинг и события
            void handle();
            //Выбор режима и цвета
            void setMode(const uint8_t mode, const uint8_t color[3]);
            //Выбор режима без цвета (используется чёрный)
            void setMode(const uint8_t mode);
            //Установка полупериода мигания светодиода, мс
            void setTimePeriodBlink(const uint16_t timePeriod);
            //Установка периода изменения цвета радуги, мс
            void setTimePeriodRainbow(const uint16_t timePeriod);
            //Установка шага изменения цвета в радуге
            void setStepRainbow(const uint8_t step);

        private:
            const uint8_t red;                                      //Пин для красного канала
            const uint8_t green;                                    //Пин для зелёного канала
            const uint8_t blue;                                     //Пин для синего канала
            uint8_t thisStatus = 0;                                 //Текущий режим воспроизведения LED-RGB
            uint8_t ledRGB[3] = {0, 0, 0};                          //Установленный цвет для мигания диода
            uint8_t position[3] = {0, 0, 0};                        //Текущие значения каналов светодиода (зеркало пинов)
            uint32_t time = 0;                                      //Переменная для отсчёта времени
            uint8_t positionRainbow = 1;                            //Номер текущей фазы радуги
            uint16_t timePeriodBlink = 300;                         //Полупериод мигания светодиода, мс
            uint16_t timePeriodRainbow = 100;                       //Период изменения цвета радуги, мс
            uint8_t stepRainbow = 3;                                //Шаг изменения цвета в радуге

            // Установка цвета светодиода
            void setColor(const uint8_t color[3]);
    };
}
