/********************************************************************************
 * Include
 ********************************************************************************/

#include "Battery.h"

/********************************************************************************
 * Class Battery
 ********************************************************************************/

void Battery::SetParameters(TypeBattery type, uint8_t cell, float current) {
    Parameters.typeBattery = type;
    Parameters.numberOfCells = cell;
    Parameters.chargeCurrent = current;
}

float Battery::GetVoltage() {
    float voltageCell = 0.0f;

    switch (Parameters.typeBattery) {
        case TypeBattery::SLA:
            voltageCell = MaxVoltageCell::SLA;
            break;
        case TypeBattery::AGM:
            voltageCell = MaxVoltageCell::AGM;
            break;
        case TypeBattery::GEL:
            voltageCell = MaxVoltageCell::GEL;
            break;
        case TypeBattery::Lithium:
            voltageCell = MaxVoltageCell::Lithium;
            break;
        case TypeBattery::LiPo:
            voltageCell = MaxVoltageCell::LiPo;
            break;
        case TypeBattery::LiFePO:
            voltageCell = MaxVoltageCell::LiFePO;
            break;
        case TypeBattery::LTO:
            voltageCell = MaxVoltageCell::LTO;
            break;
    }

    return (Parameters.numberOfCells * voltageCell);
}

float Battery::GetCurrent() {
    return Parameters.chargeCurrent;
}

float Battery::GetDischargeLimit() {
    float voltageCell = 0.0f;

    switch (Parameters.typeBattery) {
        case TypeBattery::SLA:
            voltageCell = MinVoltageCell::SLA;
            break;
        case TypeBattery::AGM:
            voltageCell = MinVoltageCell::AGM;
            break;
        case TypeBattery::GEL:
            voltageCell = MinVoltageCell::GEL;
            break;
        case TypeBattery::Lithium:
            voltageCell = MinVoltageCell::Lithium;
            break;
        case TypeBattery::LiPo:
            voltageCell = MinVoltageCell::LiPo;
            break;
        case TypeBattery::LiFePO:
            voltageCell = MinVoltageCell::LiFePO;
            break;
        case TypeBattery::LTO:
            voltageCell = MinVoltageCell::LTO;
            break;
    }

    return (Parameters.numberOfCells * voltageCell);
}