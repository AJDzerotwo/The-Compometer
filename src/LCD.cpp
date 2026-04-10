#include <LCD.h>

// initialize ports and LCD controller
void LCD_init(void)
{
    DDRD |= (1 << RS) | (1 << EN); // set RS and EN pin to output 
	PORTD &= ~( 1 << EN);		   // turn off EN 
	DDRC |= (1 << D4) | (1 << D5) | (1 << D6) | (1 << D7); // set pins for Port C to output 

	_delay_ms(20);	   

	LCD_command(0x33); /* Intialize in 8-bit mode first*/
	LCD_command(0x32); /* Send for 4 bit initialization of LCD  */
	LCD_command(0x28); /* Initialization of 16X2 LCD in 4bit mode */
	LCD_command(0x0C); /* Display ON Cursor OFF */
	LCD_command(0x06); /* Auto Increment cursor */
	LCD_command(0x01); /* Clear display */
    LCD_command(0x80); /* Cursor at home position */
	_delay_ms(300);

}

// Send Commands to LCD
void LCD_command(uint8_t command)
{
	PORTD &= ~(1 << RS); /* RS = 0 */
	PORTC = (PORTC & 0xF0) | (command >> 4);	/* put upper nibble of the command to PortD */

	PORTD |= (1 << EN);	 /* Enable pulse*/
  	_delay_us(1);
	PORTD &= ~(1 << EN); /* clear E */
  	_delay_ms(2);

	PORTC = (PORTC & 0xF0) | (command & 0x0F);	/* put lower nibble of the command to PortD */

	PORTD |= (1 << EN);	 /* Enable pulse*/
  	_delay_us(1);
	PORTD &= ~(1 << EN); /* clear E */
  	_delay_ms(2);


}

// Send Data to LCD
void LCD_data(uint8_t data)
{
	PORTD |= (1 << RS);	 /* RS = 1 */
	
	PORTC = (PORTC & 0xF0) | (data >> 4);	/* put upper nibble of the data to PortD */
 
	PORTD |= (1 << EN);	 /* Enable pulse */
  	_delay_us(1);
	PORTD &= ~(1 << EN); /* clear E */
	_delay_ms(1);

	PORTC = (PORTC & 0xF0) | (data & 0x0F);	/* put lower nibble of the data to PortD */
	
	PORTD |= (1 << EN);	 /* Enable pulse */
  	_delay_us(1);
	PORTD &= ~(1 << EN); /* clear E */
	_delay_ms(1);

}

//send string to LCD
void LCD_string(char *str)
{
  byte i;
  for(i=0; str[i] !='\0';i++)
  {
    LCD_data(str[i]);
  }
}

