#include <SONAR.h>

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;		/* Increment Timer Overflow count */
}

void SONAR_init() {
    DDRB |= 1 << Trigger_pin;
    DDRB &= ~(1<<echoPin);			
	PORTB |= 1 << echoPin;	

    sei();					/* Enable global interrupt */
	TIMSK1 = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;	
    USART_send_string("Ultrasonic");
}

int SONAR_dist() {
    char string[10];
	long count;
	double distance;
    USART_send_string("Distance");
    PORTB |= (1 << Trigger_pin);/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	_delay_us(10);
	PORTB &= (~(1 << Trigger_pin));
		
	TCNT1 = 0;			/* Clear Timer counter */
	TCCR1B = 0x41;		/* Setting to capture rising edge, No pre-scaler*/
	TIFR1 = 1<<ICF1;		/* Clear ICP flag (Input Capture flag) */
	TIFR1 = 1<<TOV1;		/* Clear Timer Overflow flag */

	/*Calculate width of Echo by Input Capture (ICP) on PortB PB0 */
		
	while ((TIFR1 & (1 << ICF1)) == 0);	/* Wait for rising edge */
	TCNT1 = 0;			/* Clear Timer counter */
	TCCR1B = 0x01;		/* Setting for capture falling edge, No pre-scaler */
	TIFR1 = 1<<ICF1;		/* Clear ICP flag (Input Capture flag) */
	TIFR1 = 1<<TOV1;		/* Clear Timer Overflow flag */
	TimerOverflow = 0;	/* Clear Timer overflow count */

	while ((TIFR1 & (1 << ICF1)) == 0); /* Wait for falling edge */
	count = ICR1 + (65535 * TimerOverflow);	/* Take value of capture register */
	/* 16MHz Timer freq, sound speed =343 m/s,  17150 x Timer value * 0.0625 x 10 ^ -6 = Timer value / 932.8*/
	distance = (double)count / 932.8;

	dtostrf(distance, 2, 2, string);/* Convert distance into string */
	strcat(string, " cm   ");
	USART_send_string("Dist = ");
	USART_send_string(string);	/* Print distance on serial monitor */
	USART_send('\n');
	_delay_ms(200);

    return (int)distance;
}
