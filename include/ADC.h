#pragma once
#include <Arduino.h>

void ADC_init(byte inputPins);

uint16_t readADC(byte channel);