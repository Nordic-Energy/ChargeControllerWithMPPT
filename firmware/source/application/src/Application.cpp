/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Application.h"

/********************************************************************************
 * Variables 
 ********************************************************************************/

BuckConverter Buck;
Battery UserBattery;

/********************************************************************************
 * Class Application
 ********************************************************************************/

void Application::Init() {
    UserBattery.SetParameters(Battery::TypeBattery::SLA, _1S, 2.0f);

    float referenceVoltage = UserBattery.GetVoltage();
    Buck.SetReferenceVoltage(referenceVoltage);
    float referenceCurrent = UserBattery.GetCurrent();
    Buck.SetReferenceCurrent(referenceCurrent);

    Feedback::SelectDivider(referenceVoltage);

    StartLowSpeedProcessing();
    StartHighSpeedProcessing();
}

/********************************************************************************
 * High speed processing #1
 ********************************************************************************/

void sTim3::handler (void) {
    TIM3->SR &= ~TIM_SR_UIF;
    Buck.Converter();
}

/********************************************************************************
 * Low speed processing #1
 ********************************************************************************/

void sTim2::handler (void) {
    TIM2->SR &= ~TIM_SR_UIF;
    Led::Toggle(Led::Color::yellow);

    // UVLO input voltage
    float inputVoltage = Feedback::GetInputVoltage();
    float maxVoltageBattery = UserBattery.GetVoltage();
    if (inputVoltage > (maxVoltageBattery + Buck.voltageDropConverter)) {
        Buck.Start();
    } else {
        Buck.Stop();
    }
}