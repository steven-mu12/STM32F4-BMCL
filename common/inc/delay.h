#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

void systick_init(uint32_t ticks);
void SysTick_Handler(void);
void delay(unsigned ms);

#endif
