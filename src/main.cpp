#include <Arduino.h>
#include <ADC.h>
#include <USART.h>
#include <ShiftReg.h>
#include <Segment.h>
#include <servo.h>
#include <LCD.h>
#include <SONAR.h>

#define azimuth_range 180
#define distance_range 30
#define azimuth_step 5
#define array_size azimuth_range / azimuth_step + 1

//S for sweep, L for Lidar
byte modes[] = {0b01110111, 0b00100011};

void servo_rotate(double *dist_array);

void SONAR_print(double *dist_array);


int main () {
  // Add at the beginning of each project to enable debugging
	#ifdef __DEBUG__
		dbg_start();
	#endif
  
  double distance_array[array_size];
  double distance = 0.0;
  char string[10];
  //double distance_array[37] = {1.2, 30, 30, 30, 1.6, 0, 30, 9, 11, 19, 21, 29, 13, 3, 5.6, 7, 6.7, 12, 4, 3.23, 5.4, 5, 4, 21, 4, 0, 6, 5, 6, 5, 6, 4, 3.4};
  USART_init();
	//SONAR_init(); 
  servo_init();
  servo_rotate(distance_array);
 // SONAR_print(distance_array);  
  /*
  while(true) {
    distance = SONAR_dist();
    itoa((int)distance, string, 10);
    USART_send_string(string);
    USART_send('\n');
    _delay_ms(100);
  }*/

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


void servo_rotate(double *dist_array)
{
    servo_goto(0);
    _delay_ms(1000);
      for (d = 0; d <= 180; d+= azimuth_step) 
      {   			 
        //dist_array[d/azimuth_step] = SONAR_dist();
        OCR1A = degreeToDuty(d);
   		  _delay_ms(50 * azimuth_step);
	  }
   
}

void SONAR_print(double *dist_array) {
  char string[10];
  USART_send('\n');
  for (int row = 29; row > 0; row--) {
    for (int column = 0; column < array_size; column++) {
      if ((int)dist_array[column] == row) {
        USART_send_string("|?|");
      }
      else {
        USART_send_string(" - ");
      }
    }
    itoa(row, string, 10);
    USART_send(' ');
    USART_send_string(string);
    USART_send_string("cm");
    USART_send('\n');
  }
  for (int column = 0; column < array_size; column++) {
    int degree = abs(column * azimuth_step - (azimuth_range / 2));
    itoa(degree, string, 10);
    USART_send(' ');
    USART_send_string(string);
    if (degree < 10) {
      USART_send(' ');
    }
  }
}