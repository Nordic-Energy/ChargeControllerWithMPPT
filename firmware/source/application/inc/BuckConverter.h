/********************************************************************************
 * class        Control power converter on the buck topology                    *
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

#include "Hrpwm.h"
#include "Feedback.h"
#include "Pid.h"

/********************************************************************************
 * 
 * Class Buck
 * 
 ********************************************************************************/

class BuckConverter {
    public:
        constexpr static float voltageDropConverter = 1.0f;

    public:
        void Converter();
        void SetReferenceVoltage (float voltage);
        void SetReferenceCurrent (float current);
        void Start();
        void Stop();

    private:
        uint16_t dutyResult;

        struct {
            float referenceVoltage;
            float referenceCurrent;
        } Parameters;

        struct {
            bool enable;
            bool error;
        } Status;
        
};