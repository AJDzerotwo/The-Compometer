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
  
  USART_init();
	SONAR_init();
  while(true) {
    SONAR_dist();
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

