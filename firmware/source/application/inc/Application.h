/********************************************************************************
 * class        Control and algorithms for application                          *
 *                                                                              *
 * file         Application.h                                                   *
 * author       @RedCommissary                                                  *
 * date         23.06.2020                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "startupF334.h"

#include "Led.h"
#include "BuckConverter.h"
#include "Battery.h"

/********************************************************************************
 * Class Application
 * 
 * High speed handler   -   2 kHz
 * Low speed handler    -   1 Hz
 * 
 ********************************************************************************/

class Application {       
    public:
        static void Init();

    private:
        static void StartHighSpeedProcessing() {
            RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     

            TIM3->PSC = 36-1;
            TIM3->ARR = 500;
            TIM3->DIER |= TIM_DIER_UIE;
            TIM3->CR1  |= TIM_CR1_CEN;

            NVIC_EnableIRQ(TIM3_IRQn);
        }

        static void StartLowSpeedProcessing() {
            RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     

            TIM2->PSC = 36000-1;
            TIM2->ARR = 1000;
            TIM2->DIER |= TIM_DIER_UIE;
            TIM2->CR1  |= TIM_CR1_CEN;

            NVIC_EnableIRQ(TIM2_IRQn);
        }
};