#include <Arduino.h>

// Defines Variables
#define RS PD7 // Register Select is connected to PB1
#define EN PD6 // Enable pin is connected to PB0

#define D4 PC0 // D4 is connected to PC0
#define D5 PC1 // D5 is connected to PC1
#define D6 PC2 // D6 is connected to PC2
#define D7 PC3 // D7 is connected to PC3

#define CLEAR 1

// Function prototypes
void LCD_init(void);
void LCD_command(uint8_t command);
void LCD_data(uint8_t data);
void LCD_string(char *str);