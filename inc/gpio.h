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

#include <stdbool.h>
#ifndef GPIO_H
#define GPIO_H

// -- BASIC DEFINITIONS --
#define BIT(x) (1U << (x))                                              // makes a mask, with a 1 at the xth position starting right
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))                  // makes 16 bit value, top 8 being bank, bottom 8 being pin number
#define PINNUM(pin) ((pin & 0b11111111))                       // extract last 8 bits (the pin number)
#define PINBANK(pin) ((pin >> 8))                              // extract first 8 bits (the bank number)

enum {GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG};


// -- RCC struct
struct rcc {
  volatile uint32_t CR, PLLCFGR, CFGR, CIR, AHB1RSTR, AHB2RSTR, AHB3RSTR,
      RESERVED0, APB1RSTR, APB2RSTR, RESERVED1[2], AHB1ENR, AHB2ENR, AHB3ENR,
      RESERVED2, APB1ENR, APB2ENR, RESERVED3[2], AHB1LPENR, AHB2LPENR,
      AHB3LPENR, RESERVED4, APB1LPENR, APB2LPENR, RESERVED5[2], BDCR, CSR,
      RESERVED6[2], SSCGR, PLLI2SCFGR;                                                      // all RCC utils. Ngl what are all these
};
#define RCC ((struct rcc *) 0x40023800)                                                     // makes 0x40023800 (start add of RCC) a pointer to the RCC struct


// -- GPIO struct
struct gpio {
    volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];          // inits 32bit unsigned ints for all these
};
#define GPIO(bank) ((struct gpio *) (0x40020000 + 0x400*(bank)))                            // get start address of a bank, stores as a pointer. Now that address represents a GPIO struct with the declared variables



// -- MEMBER FUNCTIONS --
void gpioPinmode(uint16_t pin, uint8_t mode);
void gpioDigitalWrite( uint16_t pin, bool value) ;
bool gpioDigitalRead( uint16_t pin );


#endif
