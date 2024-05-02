/**
 * MIT License
 *
 * Copyright (c) 2024 Steven Mu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdint.h>
#include "gpio.h"

// -- Function Definitions --

void gpioPinmode(uint16_t pin, uint8_t mode) {

    struct gpio *gpio = GPIO( PINBANK(pin) );       // extract the pin bank from pin passed from call from main, then assign to gpio*. basicall accesses a gpio bank
    int n = PINNUM(pin);                            // same as above but pin number
    RCC->AHB1ENR |= BIT( PINBANK(pin) );             // generates a mask of 1 followed by pinbank amount of 0's (a=1, b=2... h=7). ORs it into AHb1ENR, which basically sets that bit to 1 (enables clock on that bank). Again if thats confusing stare at AHB1ENR on datasheet for a bit
    gpio->MODER &= ~(3U << (n * 2));             // to access the right 2 bits, you shift 0b11 left by pin# * 2 bits (since 2 bits control each pin, so for A5 you get 110000000000. if this is confusing stare at the MODER on datasheet for a bit). You then NOT this and AND it with what's already at the MODER, so those bits with the 0's after AND are now also 0's. This just resets the mode essentially.
    gpio->MODER |= (mode & 3U) << (n * 2);        // the & is to mask for the last 2 bits of mode in case there's stuff before. Shift that 2 digits to the right spot an OR it in, same logic as above
}


void gpioDigitalWrite(uint16_t pin, bool val) {

    struct gpio *gpio = GPIO(PINBANK(pin));
    gpio->BSRR = (1U << PINNUM(pin)) << (val ? 0 : 16);     // shift 0b1 left by the amount of pins. Then shift it left by another 0 or 16 (if val == 0 then 16). Basically we access the "set" bit if true, "reset" bit if false. Again stare at datasheet BSRR for a sec if confused.
                                                            // it's also atomic (cant be interrupted, and when done it auto "clears" itself so we don't need to clear BSRR beore using
}

bool gpioDigitalRead( uint16_t pin ) {

	struct gpio *gpio = GPIO(PINBANK(pin));
	return( (gpio->IDR) & ( BIT( PINNUM(pin) ) ) );			// access the pin-th bit in gpio's IDR register to see if specific pin is high or not

}

