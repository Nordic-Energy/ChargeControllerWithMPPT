/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Led.h"

/********************************************************************************
 * Class Led
 ********************************************************************************/

void Led::Init (void) {
    Gpio::Init<5>(GPIOB, Gpio::Mode::output, Gpio::Type::PP);
    Gpio::Init<15>(GPIOA, Gpio::Mode::output, Gpio::Type::PP); 
};

void Led::On (Color led) {
    if (led == Color::green) { Gpio::Set<5>(GPIOB); }
    if (led == Color::yellow) { Gpio::Set<15>(GPIOA); }
};

void Led::Off (Color led) {
    if (led == Color::green) { Gpio::Reset<5>(GPIOB); }
    if (led == Color::yellow) { Gpio::Reset<15>(GPIOA); }
};

void Led::Toggle (Color led) {
    if (led == Color::green) { Gpio::Toggle<5>(GPIOB); }
    if (led == Color::yellow) { Gpio::Toggle<15>(GPIOA); }  
};