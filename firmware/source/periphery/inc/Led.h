/********************************************************************************
 * class        Initialization and contoller LED                                *
 *                                                                              *
 * file         Led.h                                                           *
 * author       @RedCommissary                                                  *
 * date         11.05.2020                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f3xx.h"
#include "Gpio.h"

/********************************************************************************
 * Class
 * 
 * PB5  -   Green   -   Led status signal
 * PA15 -   Yellow  -   Led fault signal
 * 
 ********************************************************************************/

class Led {

    public:
        enum class Color:int {
            green, yellow
        };

    public:
        static void Init (void);
        static void On (Color led);
        static void Off (Color led);
        static void Toggle (Color led);
};