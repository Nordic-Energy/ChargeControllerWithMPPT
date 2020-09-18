/********************************************************************************
 * class        PID controller with limit and anti-windup                       *
 *                                                                              *
 * file         Pid.h                                                           *
 * author       @RedCommissary                                                  *
 * date         03.06.2020                                                      *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include <cmath>

/********************************************************************************
 * Class PID controller
 ********************************************************************************/

class PidController {
public:
    float error;
    float integralFilter;
    float derivativeFilter;
    float proportionalComponent;
    float integralComponent;
    float derivativeComponent;
    float tempPID;
    float outputPID;

    struct {
        float feedback;
        float reference;
        float deltaTimeSampling;
            
        struct {
            float proportional;
            float integral;
            float derivative;
            float coefficientBackSaturation;
            float filterDerivative;
        } coefficient;
            
        struct {
            float lowThershold;
            float highThershold;
        } saturation;
    } input;

public:
    PidController& SetReference (float reference) {
        input.reference = reference;
        return *this;
    }

    PidController& SetFeedback (float feedback, float deltaTimeSampling) {
        input.feedback = feedback;
        input.deltaTimeSampling = deltaTimeSampling;
        return *this;
    }

    PidController& SetCoefficient (float Kp, float Ki, float Kd, float BackSaturation, float filterDerivative) {
        input.coefficient.proportional = Kp;
        input.coefficient.integral = Ki;
        input.coefficient.derivative = Kd;
        input.coefficient.coefficientBackSaturation = BackSaturation;
        input.coefficient.filterDerivative = filterDerivative;
        return *this;
    }

    PidController& SetSaturation (float lowLimit, float highLimit) {
        input.saturation.lowThershold = lowLimit;
        input.saturation.highThershold = highLimit;
        return *this;
    }

    PidController& Compute() {
        error = input.reference - input.feedback;

        proportionalComponent = input.coefficient.proportional * error;

        integralComponent += input.deltaTimeSampling * integralFilter;
        integralFilter = input.coefficient.integral * error + input.coefficient.coefficientBackSaturation * (outputPID - tempPID);

        derivativeFilter += input.deltaTimeSampling * derivativeComponent;
        derivativeComponent = (input.coefficient.derivative * error - derivativeFilter) * input.coefficient.filterDerivative;

        outputPID = tempPID = proportionalComponent + integralComponent + derivativeComponent;
        outputPID = std::min(std::max(outputPID, input.saturation.lowThershold), input.saturation.highThershold);

        return *this;
    }

    float Get() {
        return outputPID;
    }
};