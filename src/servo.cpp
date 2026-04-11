#include "servo.h"
int d = 0; // global variable to keep track of the current degree position of the servo
//lesson of the day, if you want to regularly update a variable you shouldn't put it in the header file
int degreeToDuty(int degree)
{
    double ratio = (double)degree / 180.0;
    return (int)(ratio * (DUTY_MAX - DUTY_MIN) + DUTY_MIN); 
    //hi. before you get mad at me for not using the formula for the servo lab
    //I want you to know it made a this jittery motion so i changed it to stop it
}

int servo_left()
{
    for (d = d; d >= 0; d--) 
    {
    	OCR2A = degreeToDuty(d);
   		_delay_ms(50);
	}
}

int servo_right()
{
    for (d = d; d <= 180; d++) 
    {   			 
        OCR2A = degreeToDuty(d);
   		_delay_ms(50);
	}

}

int servo_init()
{
    DDRB |= (1<<SERVO);	// Make OC1A pin as output 
	TCNT2 = 0;			// Set timer2 count zero 

	// Set Fast PWM, TOP in ICR2, Clear OC1A on compare match, clk/64 non-inverting mode
	TCCR2A = (1<<WGM21|1<<COM2A1);  // set required WGM and COM bits in register A to be filled
	TCCR2B =  (1<<CS22|1<<CS20|1<<WGM22); // set required WGM and CS bits to be filled
}

void servo_goto(int degree) {
    OCR2A = degreeToDuty(degree);
    _delay_ms(1000);

}