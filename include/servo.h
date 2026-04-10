#include <Arduino.h>
#include <avr_debugger.h>

#define SERVO PB1

const int DUTY_MIN = 130; //prescalar 64 for 0 degree
const int DUTY_MAX = 600; //prescalar 64 for 180 degree
const int DEGREE_MIN = 0;
const int DEGREE_MAX = 180;
extern int d; // global variable to keep track of the current degree position of the servo
int servo_init();
int degreeToDuty(int degree);
int servo_rotate();
int servo_left();
int servo_right();

void servo_rotate_degree(int degree);