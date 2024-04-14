#include "delay.h"
#include "gpio.h"

struct systick {
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};
#define SYSTICK ((struct systick *) 0xe000e010)

volatile uint32_t s_ticks;

void systick_init(uint32_t ticks) {
	if ((ticks - 1) > 0xffffff) return;  		// systick timer is 24 bit
	SYSTICK->LOAD = ticks - 1;
	SYSTICK->VAL = 0;
	SYSTICK->CTRL = BIT(0) | BIT(1) | BIT(2);  	// enable systick
	RCC->APB2ENR |= BIT(14);                   	// enable SYSCFG
}

void SysTick_Handler(void) {
	s_ticks++;
}

void delay(unsigned ms) {
	uint32_t until = s_ticks + ms;      			// future "stoppage time"
	while (s_ticks < until) (void) 0;   			// polling
}
