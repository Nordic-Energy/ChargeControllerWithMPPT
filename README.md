## Solar charge controller with MPPT algorithm

The charge controller is controlled by a dedicated STM32F334C8T6 microcontroller with a High Resolution PWM (HRPWM) on board. The use of this device is possible a devkit for studying the algorithms for finding the maximum power point (TMM) and as a device for working in an solar power plant with a capacity of up to 500 W.

![Photo of MPPT](https://habrastorage.org/webt/yq/tc/fj/yqtcfjic5fkabvp-xis7-gtjlge.jpeg)

>

![Photo of MPPT](https://habrastorage.org/webt/du/by/js/dubyjsgjtipjnblorov5fmktdau.jpeg)

When developing a charge controller the main emphasis is on creating reliable hardware using the best components and on implementing the most efficient TMM search algorithms. There are no electrolytic capacitors in the controller, instead of them solid polymer capacitors with an increased service life are used and as well as the thermal modes of operation of the device are optimized. That together will provide a guaranteed service life of at least 10 years. This will increase the reliability of autonomous mini-power plants and reduce equipment maintenance costs.

## Features:

* Use 32-bit ARM MCU STM32F334C8 with HRPWM
* Voltage input: *15...60V*
* Voltage output: *12/24V*
* Max charge current: *20A*
* Conversion frequency: *100kHz*
* Efficiency: *>94%*
* MPPT algorithm
* Type battery: *SLA, AGM, GEL, Li-ion, LiFePo4, LTO*
* Interface: *CAN, Wi-Fi*

## Built-in protection:
* Overvoltage
* Undervoltage
* Overcurrent
* Overheat
* PV short circuit
* PV reverse polarity
* Battery reverse polarity

## Project structure:

* *docs* - documentation for project: ВОМ, schematic, etc
* *hardware* - source project for design PCB
* *manufacture* - gerber files for order PCB
* *mechanical* - source project for 3D design

## Firmware

* [Universal firmware project for MPPT solar charge](https://github.com/RedCommissary/mppt-charger-firmware)
* [Project HMI TFT display panel for controller](https://github.com/RedCommissary/display-tft-3.5)

## License

All source files for the project are distributed under the [MIT](./LICENSE "Text license") license and you can use the project for commercial activities. But you need remembering that the author of the project does not give any guarantees for the operability of the device or parts of the project and also does not bear no liability for claims or damages.
