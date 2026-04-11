#include <Arduino.h>
#include <ADC.h>
#include <USART.h>
#include <ShiftReg.h>
#include <Segment.h>
#include <servo.h>
#include <LCD.h>
#include <SONAR.h>


//S for sweep, L for Lidar
byte modes[] = {0b01110111, 0b00100011};

int main () {
  // Add at the beginning of each project to enable debugging
	#ifdef __DEBUG__
		dbg_start();
	#endif
  
  double distance = 0.0;
  char string[10];

  USART_init();
	SONAR_init();
  while(true) {
    distance = SONAR_dist();
    itoa((int)distance, string, 10);
    USART_send_string(string);
    USART_send('\n');
    _delay_ms(100);
  }

  /*
  LCD_init();
  LCD_string("Test");
  //LCD_command(1);

  USART_init();
  USART_send_string("Test");

  init_shift(DATA, CLOCK, LATCH);
  while (true) {
  displyValue(modes[0]);
  _delay_ms(1000);
  displyValue(modes[1]);
  _delay_ms(1000);
  }
  */
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