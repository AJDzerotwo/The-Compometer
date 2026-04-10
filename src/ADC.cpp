#include <ADC.h>

void ADC_init(byte inputPins) {
  PRR &= ~(1 << PRADC); //Turn on ADC in Power Reduction Register
  ADCSRA |= 1 << ADEN | 1 << ADPS0 | 1 << ADPS1; //Turn on ADC, Output Prescalar division 128
  DDRC &= ~inputPins; //Set Pins as input
  DIDR0 = inputPins; //Disable Digital Input
}

uint16_t readADC(byte channel) {
  ADMUX = 0x40 | (channel & 0x07);
  ADCSRA |= 1 << ADSC;
  while (!(ADCSRA & (1 << ADSC)));
  _delay_ms(1);
  return ADCW;
}
