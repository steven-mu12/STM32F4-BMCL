
#include <stdio.h>
#include <stdint.h>
#include "lcd.h"
#include "gpio.h"
#include "delay.h"



// ----------------------------------
// ---- USER COMMAND DEFINITIONS ----
// ----------------------------------

void initDisplay( struct lcd *lcd, uint16_t D4i, uint16_t D5i, uint16_t D6i, uint16_t D7i, uint16_t RSi, uint16_t Ei ){

	uint16_t *pins = &lcd->D7;

	// --- GPIO initializations
	gpioPinmode(D7i, GPIO_MODE_OUTPUT);
	pins[0] = D7i;
	gpioPinmode(D6i, GPIO_MODE_OUTPUT);
	pins[1] = D6i;
	gpioPinmode(D5i, GPIO_MODE_OUTPUT);
	pins[2] = D5i;
	gpioPinmode(D4i, GPIO_MODE_OUTPUT);
	pins[3] = D4i;
	gpioPinmode(RSi, GPIO_MODE_OUTPUT);
	pins[4] = RSi;
	gpioPinmode(Ei, GPIO_MODE_OUTPUT);
	pins[5] = Ei;

	// need to wait 50ms before any init commands
	delay(50);

	gpioDigitalWrite(lcd->E, 0); // Data mode
	gpioDigitalWrite(lcd->RS, 0); // Data mode
	delay(1);


	// still have no idea why this
    _write_fourbits(lcd, 0x03);
    delay(8);
    _write_fourbits(lcd, 0x03);
    delay(8);
    _write_fourbits(lcd, 0x03);
    delay(1);
    _write_fourbits(lcd, 0x02);


    // Now the LCD is in 4-bit mode, proceed with the rest of the initialization
    _write_command(lcd, 0x28);  // Function Set: 4-bit mode, 2 lines, 5x8 font
    _write_command(lcd, 0x0C);  // Display ON, Cursor OFF, Blink OFF
    _write_command(lcd, 0x06);  // Entry Mode Set: Increment cursor, no display shift
    _write_command(lcd, 0x01);  // Clear display
    delay(2);                   // clear needs about 1.53 ms
}




void clearDisplay( struct lcd *lcd ) {
	gpioDigitalWrite(lcd->RS, 0); // Data mode
	delay(1);

	// clear LCD command
	_write_command(lcd, 0b00000001);
	delay(5);

	// go home
	_write_command(lcd, 0b10000000);
	delay(5);
}




void writeData(struct lcd *lcd, char *data, int length) {
    gpioDigitalWrite(lcd->RS, 1); // Data mode
    delay(1);

    for (int i = 0; i < length; i++) {
        _write_fourbits(lcd, data[i] >> 4); // High nibble
        _write_fourbits(lcd, data[i] & 0x0F); // Low nibble
    }
}







// ---------------------------------------
// ---- LOW LEVEL COMMAND DEFINITIONS ----
// ---------------------------------------
// note that user should not use these directly

void _toggle_en( struct lcd *lcd ){
	gpioDigitalWrite(lcd->E, 1);
	delay(2);
	gpioDigitalWrite(lcd->E, 0);
	delay(5);
}


void _write_command(struct lcd *lcd, uint8_t command) {
	_write_fourbits(lcd, command >> 4);
	_write_fourbits(lcd, command & 0x0F);
}



void _write_fourbits(struct lcd *lcd, uint8_t command) {
    for (int i = 0; i < 4; i++) {
        gpioDigitalWrite((&lcd->D7)[i], (command >> i) & 1);
    }
    _toggle_en(lcd);
}
