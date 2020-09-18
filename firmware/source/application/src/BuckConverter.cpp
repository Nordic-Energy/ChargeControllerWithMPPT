/********************************************************************************
 * Include 
 ********************************************************************************/

#include "BuckConverter.h"

/********************************************************************************
 * Variables
 ********************************************************************************/

PidController pidVoltageMode;
PidController pidCurrentMode;

/********************************************************************************
 * Class Buck
 ********************************************************************************/

void BuckConverter::Converter() {
    if (Status.enable != true) {
        dutyResult = 0;
        Hrpwm::SetDuty(dutyResult);
        return;
    }

    float resultPID = 0.0f;

    float outputVoltage = Feedback::GetOutputVoltage();
    float outputCurrent = Feedback::GetOutputCurrent();

    if (outputVoltage < (Parameters.referenceVoltage - 0.2f)) {
        pidCurrentMode
            .SetReference(Parameters.referenceCurrent)
            .SetSaturation(-40000, 40000)
            .SetFeedback(outputCurrent, 0.0002)
            .SetCoefficient(10, 0, 0, 0, 0)
            .Compute();
        resultPID = pidCurrentMode.Get();
    } else {
        pidVoltageMode
            .SetReference(Parameters.referenceVoltage)
            .SetSaturation(-40000, 40000)
            .SetFeedback(outputVoltage, 0.0002)
            .SetCoefficient(50, 0, 0, 0, 0)
            .Compute();
        resultPID = pidVoltageMode.Get();
    }

    dutyResult += resultPID;
    Hrpwm::SetDuty(dutyResult);
}

void BuckConverter::SetReferenceVoltage (float voltage) {
    Parameters.referenceVoltage = voltage;
}

void BuckConverter::SetReferenceCurrent (float current) {
    Parameters.referenceCurrent = current;
}

void BuckConverter::Start() {
    Status.enable = true;
}

void BuckConverter::Stop() {
    Status.enable = false;
}
