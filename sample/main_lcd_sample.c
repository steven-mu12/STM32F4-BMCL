#include <stdint.h>
#include "lcd.h"
#include "gpio.h"
#include "delay.h"

int main(void) {

	// ----- SETUP -----

	// initialize systick for delay
	systickInit(16000);

	// make the string, and calculate length
	char data[] = "HELLO";
	int l = sizeof(data) / sizeof(data[0]) - 1;

	char data2[] = "WORLD";
	int m = sizeof(data2) / sizeof(data2[0]) - 1;

	// define pins
	uint16_t d4 = PIN('A', 8);
	uint16_t d5 = PIN('B', 10);
	uint16_t d6 = PIN('B', 4);
	uint16_t d7 = PIN('B', 5);
	uint16_t rs = PIN('B', 3);
	uint16_t e = PIN('A', 10);

	// set up your lcd struct
	struct lcd myLCD;

	// initialize the LCD, then you're set
	initDisplay( &myLCD, d4, d5, d6, d7, rs, e );
	clearDisplay( &myLCD );

	writeDisplay( &myLCD, data, l );
	setCursor( &myLCD, 1, 3 );
	writeDisplay( &myLCD, data2, m );

	// ----- LOOP -----
	for(;;);

// After the init is done in setup, then all functions are accessible in the loop too
  
//	while (1){
//
//		char data[] = "HELLO";
//		int l = sizeof(data) / sizeof(data[0]) - 1;
//		clearDisplay( &myLCD );
//		writeData( &myLCD, data, l );
//		delay(5000);
//
//		char data2[] = "WORLD";
//		int m = sizeof(data2) / sizeof(data2[0]) - 1;
//		clearDisplay( &myLCD );
//		writeData( &myLCD, data2, m );
//		delay(5000);
//	}
}
