/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Feedback.h"

/********************************************************************************
 * Variables
 ********************************************************************************/

bool Feedback::statusOutputDivider = false;

/********************************************************************************
 * Class Feedback
 ********************************************************************************/

void Feedback::InitGpioDivider() {
    Gpio::Init<14>(GPIOB, Gpio::Mode::output, Gpio::Type::PP);
}

void Feedback::SetOutputDivider (Divider divider) {
    if (divider == Divider::div12V) { 
        GPIOB->BSRR |= GPIO_BSRR_BR_14; 
        statusOutputDivider = false;
    }

    if (divider == Divider::div24V) {
        GPIOB->BSRR |= GPIO_BSRR_BS_14;
        statusOutputDivider = true;
    }
} 

void Feedback::SelectDivider (float voltage) {
    InitGpioDivider();

    if (voltage > 16.0f) {
        Feedback::SetOutputDivider(Feedback::Divider::div24V);
    } else {
        Feedback::SetOutputDivider(Feedback::Divider::div12V);
    }
}

float Feedback::GetInputVoltage() {
    Adc::Status::stopInputVoltage = true;
    float inputVoltage = FilterWindowMedium::Compute(Adc::inputVoltage, Adc::sizeBuffer, sizeWindow);
    Adc::Status::stopInputVoltage = false;
    return (inputVoltage * voltageDivInput * sampleStepAdc + staticErrorInputVoltage);
}

float Feedback::GetInputCurrent() {
    Adc::Status::stopInputCurrent = true;
    float inputCurrent = FilterWindowMedium::Compute(Adc::inputCurrent, Adc::sizeBuffer, sizeWindow);
    Adc::Status::stopInputCurrent = false;
    return (inputCurrent * sampleStepAdc / gainCurrentSensor / currentShunt);
}

float Feedback::GetOutputVoltage() {
    if (statusOutputDivider) {
        Adc::Status::stopOutputVoltage = true;
        float outputVoltage = FilterWindowMedium::Compute(Adc::outputVoltage, Adc::sizeBuffer, sizeWindow);
        Adc::Status::stopOutputVoltage = false;
        return (outputVoltage * sampleStepAdc * voltageDivOutput24V + staticErrorOutputVoltage);
    } else {
        Adc::Status::stopOutputVoltage = true;
        float outputVoltage = FilterWindowMedium::Compute(Adc::outputVoltage, Adc::sizeBuffer, sizeWindow);
        Adc::Status::stopOutputVoltage = false;
        return (outputVoltage * sampleStepAdc * voltageDivOutput12V + staticErrorOutputVoltage);
    }
}

float Feedback::GetOutputCurrent() {
    Adc::Status::stopOutputCurrent = true;
    float outputCurrent = FilterWindowMedium::Compute(Adc::outputCurrent, Adc::sizeBuffer, sizeWindow);
    Adc::Status::stopOutputCurrent = false;
    return (outputCurrent * sampleStepAdc / gainCurrentSensor / currentShunt);
}