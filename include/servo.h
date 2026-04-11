#include <Arduino.h>
#include <avr_debugger.h>

#define SERVO PB3

const int DUTY_MIN = 16;  // approx 1 ms pulse at Timer2 prescaler 1024
const int DUTY_MAX = 32;  // approx 2 ms pulse at Timer2 prescaler 1024
const int DEGREE_MIN = 0;
const int DEGREE_MAX = 180;
extern int d; // global variable to keep track of the current degree position of the servo
void servo_init();
int degreeToDuty(int degree);
void servo_left();
void servo_right();

void servo_goto(int degree);