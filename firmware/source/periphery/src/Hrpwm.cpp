/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Hrpwm.h"

/********************************************************************************
 * Class HRPWM
 ********************************************************************************/

void Hrpwm::Init (void) {

    Hrpwm::InitGpio();

    RCC->CFGR3   |= RCC_CFGR3_HRTIM1SW_PLL;                                                  // Enable multiplier x2 for PLL frequency
    RCC->APB2ENR |= RCC_APB2ENR_HRTIM1EN;                                                    // Enable clock for HRPWM

    HRTIM1->sCommonRegs.DLLCR |= HRTIM_DLLCR_CAL | HRTIM_DLLCR_CALEN;                        // Start timer's calibration
    while ((HRTIM1->sCommonRegs.ISR & HRTIM_ISR_DLLRDY) == RESET);                           // Waiting for the end fo calibration

    HRTIM1->sTimerxRegs[0].PERxR = Hrpwm::periodHrpwm;                                       // Set period for timer
    HRTIM1->sTimerxRegs[0].CMP1xR = 0;                                                       // Set starting duty

    HRTIM1->sTimerxRegs[0].OUTxR |= HRTIM_OUTR_DTEN;                                         // Enable dead-time
    HRTIM1->sTimerxRegs[0].DTxR  |= (3 << HRTIM_DTR_DTPRSC_Pos);                             // Set Tdtg = (2^3) * 868 ps = 6.94 ns
    HRTIM1->sTimerxRegs[0].DTxR  |= (15 << HRTIM_DTR_DTR_Pos) | (15 << HRTIM_DTR_DTF_Pos);   // Set dead-time rising and falling = 15 * Ttg = 104 ns
    HRTIM1->sTimerxRegs[0].DTxR  |= HRTIM_DTR_DTFSLK | HRTIM_DTR_DTRSLK;                     // Lock value dead-time

    HRTIM1->sTimerxRegs[0].SETx1R |= HRTIM_SET1R_PER;	                                     // Event forces the output to active state
    HRTIM1->sTimerxRegs[0].RSTx1R |= HRTIM_RST1R_CMP1;                                       // Event forces the output to inactive state

    HRTIM1->sTimerxRegs[0].TIMxCR |= HRTIM_TIMCR_CONT;                                       // Continuous mode

    HRTIM1->sCommonRegs.OENR |= HRTIM_OENR_TA1OEN | HRTIM_OENR_TA2OEN;                       // Enable output PWM channel A

    HRTIM1->sMasterRegs.MPER = Hrpwm::periodHrpwm;                                           // Period for master timer
    HRTIM1->sMasterRegs.MCR |= HRTIM_MCR_MCEN | HRTIM_MCR_TACEN;                             // Enable counter for Master and timer A
};

void Hrpwm::SetDuty (uint16_t duty) {
    HRTIM1->sTimerxRegs[0].CMP1xR = duty;
};

 void Hrpwm::InitGpio (void) {
    Gpio::Init<8,9>(GPIOA, Gpio::Mode::outputAF, Gpio::Type::PP, Gpio::Speed::veryHigh, Gpio::Pupd::pullDown, Gpio::AF::af13);
};