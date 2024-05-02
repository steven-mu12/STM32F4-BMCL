#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "gpio.h"
#include "delay.h"
#include "hcsr04.h"
#include "lcd.h"

int main(void) {

	// --- VARIABLES ---
	uint32_t distance;

	// ----- SETUP -----
	systickInit(16000);
	usDelayInit();

	// setup sensor
	uint16_t trig = PIN('C', 10);
	uint16_t echo = PIN('C', 12);
	struct hcsr04 sensor;
	hcsr04Init( &sensor, trig, echo );


	// setup LCD
	uint16_t d4 = PIN('A', 8);
	uint16_t d5 = PIN('B', 10);
	uint16_t d6 = PIN('B', 4);
	uint16_t d7 = PIN('B', 5);
	uint16_t rs = PIN('B', 3);
	uint16_t e = PIN('A', 10);

	struct lcd myLCD;
	initDisplay( &myLCD, d4, d5, d6, d7, rs, e );
	clearDisplay( &myLCD );


    // ----- LOOP -----
//	for(;;);

	while (1){
		clearDisplay( &myLCD );

		distance = measureDistance( &sensor );
		char data[11];
		sprintf(data, "%lu", distance);
		int l = strlen(data);

		writeDisplay( &myLCD, data, l );
		delay(500);
	}
}
