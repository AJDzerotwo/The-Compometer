#include <Arduino.h>
#include <avr_debugger.h>
#include <USART.h>

#define  Trigger_pin	PB5	/* Trigger pin */
#define  echoPin        PB0


void SONAR_init();

double SONAR_dist();