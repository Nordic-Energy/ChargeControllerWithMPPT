/********************************************************************************
 * Include
 ********************************************************************************/

#include "startupF334.h"

/********************************************************************************
 * Default reset
 ********************************************************************************/

static INLINE void InitializeData() {

    uint32_t *pSrc;
    uint32_t *pDest;

    // Load initialized data from FLASH to RAM
    pSrc = &__etext;
    pDest = &__data_start__;

    while (pDest < &__data_end__)
    *pDest++ = *pSrc++;

    // Clear uninitialized data
    pDest = &__bss_start__;

    while (pDest < &__bss_end__)
    *pDest++ = 0;

    #ifdef _FPU_ENABLE
        __asm(
            "  LDR.W R0, =0xE000ED88\n"
            "  LDR R1, [R0]\n"
            "  ORR R1, R1, #(0xF << 20)\n"
            "  STR R1, [R0]"
        );
    #endif
}

extern "C" void ResetHandler() {
    InitializeData();
    main();
}

/********************************************************************************
 * Vector table
 ********************************************************************************/

__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {

/************* Core exceptions ******************/

    pvf(&__StackTop),
    ResetHandler,
    sNMI::handler,
    sHardFault::handler,
    sMemManage::handler,
    sBusFault::handler,
    sUsageFault::handler,
    0,0,0,0,
    sSVC::handler,
    sDebugMon::handler,
    0,
    sPendSV::handler,
    sSysTick::handler,

/********** External exceptions ***************/

    sWWDG::handler,
    sPendSV::handler,
    sTampStamp::handler,
    sRtc::weakeUp,
    sFlash::handler,
    sRcc::handler,
    sExti::line0Handler,
    sExti::line1Handler,
    sExti::line2Handler,
    sExti::line3Handler,
    sExti::line4Handler,
    sDma::channel1Handler,
    sDma::channel2Handler,
    sDma::channel3Handler,
    sDma::channel4Handler,
    sDma::channel5Handler,
    sDma::channel6Handler,
    sDma::channel7Handler,
    sAdc::handler,
    sCan::txHandler,
    sCan::rx0Handler,
    sCan::rx1Handler,
    sCan::sceHandler,
    sExti::line5Handler,
    sTim1::breakeTim15Handler,
    sTim1::upTim16Handler,
    sTim1::triggerTim17Handler,
    sTim1::ccTim1Handler,
    sTim2::handler,
    sTim3::handler,
    0,
    sI2C1::eventHandler,
    sI2C1::errorHandler,
    0,0,
    sSpi1::handler,
    0,
    sUsart1::handler,
    sUsart2::handler,
    sUsart3::handler,
    sExti::line10Handler,
    sRtc::alarmHandler,
    0,0,0,0,0,0,0,0,0,0,0,0,
    sTim6::handler,
    sTim7::handler,
    0,0,0,0,0,0,0,0,
    sComp2::handler,
    sComp4_6::handler,
    0,
    sHrtim::masterHandler,
    sHrtim::channelAhandler,
    sHrtim::channelBhandler,
    sHrtim::channelChandler,
    sHrtim::channelDhandler,
    sHrtim::channelEhandler,
    sHrtim::faultHandler,
    0,0,0,0,0,0,0,
    sFpu::handler
};

/********************************************************************************
 * Default interrupt
 ********************************************************************************/

WEAK void sNMI::handler()               { while (1) {} }
WEAK void sHardFault::handler()         { while (1) {} }
WEAK void sMemManage::handler()         { while (1) {} }
WEAK void sBusFault::handler()          { while (1) {} }
WEAK void sUsageFault::handler()        { while (1) {} }
WEAK void sSVC::handler()               { while (1) {} }
WEAK void sDebugMon::handler()          { while (1) {} }
WEAK void sPendSV::handler()            { while (1) {} }
WEAK void sSysTick::handler()           { while (1) {} }

WEAK void sWWDG::handler()              { while (1) {} }
WEAK void sPVD::handler()               { while (1) {} }
WEAK void sTampStamp::handler()         { while (1) {} }
WEAK void sRtc::weakeUp()               { while (1) {} }
WEAK void sFlash::handler()             { while (1) {} }
WEAK void sRcc::handler()               { while (1) {} }
WEAK void sExti::line0Handler()         { while (1) {} }
WEAK void sExti::line1Handler()         { while (1) {} }
WEAK void sExti::line2Handler()         { while (1) {} }
WEAK void sExti::line3Handler()         { while (1) {} }
WEAK void sExti::line4Handler()         { while (1) {} }
WEAK void sDma::channel1Handler()       { while (1) {} }
WEAK void sDma::channel2Handler()       { while (1) {} }
WEAK void sDma::channel3Handler()       { while (1) {} }
WEAK void sDma::channel4Handler()       { while (1) {} }
WEAK void sDma::channel5Handler()       { while (1) {} }
WEAK void sDma::channel6Handler()       { while (1) {} }
WEAK void sDma::channel7Handler()       { while (1) {} }
WEAK void sAdc::handler()               { while (1) {} }
WEAK void sCan::txHandler()             { while (1) {} }
WEAK void sCan::rx0Handler()            { while (1) {} }
WEAK void sCan::rx1Handler()            { while (1) {} }
WEAK void sCan::sceHandler()            { while (1) {} }
WEAK void sExti::line5Handler()         { while (1) {} }
WEAK void sTim1::breakeTim15Handler()   { while (1) {} }
WEAK void sTim1::upTim16Handler()       { while (1) {} }
WEAK void sTim1::triggerTim17Handler()  { while (1) {} }
WEAK void sTim1::ccTim1Handler()        { while (1) {} }
WEAK void sTim2::handler()              { while (1) {} }
WEAK void sTim3::handler()              { while (1) {} }
WEAK void sI2C1::eventHandler()         { while (1) {} }
WEAK void sI2C1::errorHandler()         { while (1) {} }
WEAK void sSpi1::handler()              { while (1) {} }
WEAK void sUsart1::handler()            { while (1) {} }
WEAK void sUsart2::handler()            { while (1) {} }
WEAK void sUsart3::handler()            { while (1) {} }
WEAK void sExti::line10Handler()        { while (1) {} }
WEAK void sRtc::alarmHandler()          { while (1) {} }
WEAK void sTim6::handler()              { while (1) {} }
WEAK void sTim7::handler()              { while (1) {} }
WEAK void sComp2::handler()             { while (1) {} }
WEAK void sComp4_6::handler()           { while (1) {} }
WEAK void sHrtim::masterHandler()       { while (1) {} }
WEAK void sHrtim::channelAhandler()     { while (1) {} }
WEAK void sHrtim::channelBhandler()     { while (1) {} }
WEAK void sHrtim::channelChandler()     { while (1) {} }
WEAK void sHrtim::channelDhandler()     { while (1) {} }
WEAK void sHrtim::channelEhandler()     { while (1) {} }
WEAK void sHrtim::faultHandler()        { while (1) {} }
WEAK void sFpu::handler()               { while (1) {} }