/********************************************************************************
 * class        Initialization and read ADC                                     *
 *                                                                              *
 * file         Adc.h                                                           *
 * author       @RedCommissary                                                  *
 * date         15.05.2020                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f3xx.h"
#include "startupF334.h"
#include "Gpio.h"

/********************************************************************************
 * Class ADC
 * 
 * Pin voltage input    - PA0   - ADC1 IN1
 * Pin current input    - PA1   - ADC1 IN2
 * Pin current output   - PA2   - ADC1 IN3
 * Pin voltage output   - PA3   - ADC1 IN4
 * Pin temperature      - PA5   - ADC2 IN2
 * 
 ********************************************************************************/

class Adc {
    public:
        constexpr static uint8_t sizeBuffer = 50;

        static uint16_t inputVoltage [sizeBuffer];
        static uint16_t inputCurrent [sizeBuffer];
        static uint16_t outputVoltage [sizeBuffer];
        static uint16_t outputCurrent [sizeBuffer];
        static uint8_t step;

        struct Status {
            static bool stopInputVoltage;
            static bool stopInputCurrent;
            static bool stopOutputVoltage;
            static bool stopOutputCurrent;
        };

    public:
        static void Init();

    private:    
        static void GpioInit();
        static void StartCallibrationAdc();
        static void InitTimerEvent();
};