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

int servo_rotate()
{
    while(1)
    {
        for (d = d; d <= 180; d++) 
        {   			 
            OCR1A = degreeToDuty(d);
   		    _delay_ms(50);
	    }

	    for (d = d; d >= 0; d--) 
        {
    	    OCR1A = degreeToDuty(d);
   		    _delay_ms(50);
	    }
    }
    
}

int servo_left()
{
    for (d = d; d >= 0; d--) 
    {
    	OCR1A = degreeToDuty(d);
   		_delay_ms(50);
	}
}

int servo_right()
{
    for (d = d; d <= 180; d++) 
    {   			 
        OCR1A = degreeToDuty(d);
   		_delay_ms(50);
	}

}

int servo_init()
{
    DDRB |= (1<<SERVO);	// Make OC1A pin as output 
	TCNT1 = 0;			// Set timer1 count zero 
	ICR1 = 4999;		// Set TOP count for timer1 in ICR1 register to be filled

	// Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 non-inverting mode
	TCCR1A = (1<<WGM11|1<<COM1A1);  // set required WGM and COM bits in register A to be filled
	TCCR1B =  (1<<CS11|1<<CS10|1<<WGM13|1<<WGM12); // set required WGM and CS bits to be filled
}