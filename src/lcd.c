
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "lcd.h"
#include "gpio.h"
#include "delay.h"



// ----------------------------------
// ---- USER COMMAND DEFINITIONS ----
// ----------------------------------

void initDisplay( struct lcd *lcd, uint16_t D4i, uint16_t D5i, uint16_t D6i, uint16_t D7i, uint16_t RSi, uint16_t Ei ){

	// assign pins to struct, and set them to output
    lcd->D4 = D4i;
    lcd->D5 = D5i;
    lcd->D6 = D6i;
    lcd->D7 = D7i;
    lcd->RS = RSi;
    lcd->E = Ei;

    gpioPinmode(D4i, GPIO_MODE_OUTPUT);
    gpioPinmode(D5i, GPIO_MODE_OUTPUT);
    gpioPinmode(D6i, GPIO_MODE_OUTPUT);
    gpioPinmode(D7i, GPIO_MODE_OUTPUT);
    gpioPinmode(RSi, GPIO_MODE_OUTPUT);
    gpioPinmode(Ei, GPIO_MODE_OUTPUT);

	// need to wait 50ms before any init commands
	delay(50);

	gpioDigitalWrite(lcd->E, 0);
	gpioDigitalWrite(lcd->RS, 0);

	// flash 0x03 3 times to force 4-bit mode
    _write_fourbits(lcd, 0x03);
    delay(8);
    _write_fourbits(lcd, 0x03);
    delay(8);
    _write_fourbits(lcd, 0x03);
    delay(1);
    _write_fourbits(lcd, 0x02);


    // Now the LCD is in 4-bit mode, proceed with the rest of the initialization
    _write_command(lcd, 0x28);  // 4-bit mode, 2 lines, 5x8 font
    _write_command(lcd, 0x0C);  // display ON, cursor OFF, blink OFF
    _write_command(lcd, 0x06);  // cursor increments to the right
    _write_command(lcd, 0x01);  // clear display
    delay(2);                   // clear needs about 1.53 ms
}


void clearDisplay( struct lcd *lcd ) {
	// clear LCD command
	_write_command(lcd, 0b00000001);
	delay(2);
}


void setCursor( struct lcd *lcd, int row, int col ){
	if (row == 0){
		_write_command( lcd, ((col & 0x0F) | 0x80));
	}
	else if (row == 1){
		_write_command( lcd, ((col & 0x0F) | 0xC0));
	}
}


void writeDisplay(struct lcd *lcd, char *data, int length) {
    gpioDigitalWrite(lcd->RS, 1); // Set to data mode
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
	delay(1);
	gpioDigitalWrite(lcd->E, 0);
	delay(1);
}


void _write_command(struct lcd *lcd, uint8_t command) {
	gpioDigitalWrite(lcd->RS, 0); // Set to command mode
	_write_fourbits(lcd, command >> 4); // High nibble
	_write_fourbits(lcd, command & 0x0F); // Low nibble
}


void _write_fourbits(struct lcd *lcd, uint8_t command) {
    gpioDigitalWrite(lcd->D4, (command & 1) ? 1 : 0);
    gpioDigitalWrite(lcd->D5, (command & 2) ? 1 : 0);
    gpioDigitalWrite(lcd->D6, (command & 4) ? 1 : 0);
    gpioDigitalWrite(lcd->D7, (command & 8) ? 1 : 0);

    _toggle_en(lcd);
}
