#include "delay.h"
#include "gpio.h"


// ---------------------
// ------ HANDLER ------
// ---------------------
volatile uint32_t ms_ticks;

struct systick {
  volatile uint32_t CTRL, LOAD, VAL, CALIB;
};
#define SYSTICK ((struct systick *) 0xE000E010)

void SysTick_Handler(void) {
	ms_ticks++;
}


// ----------------------
// ------ MS DELAY ------
// ----------------------

// -- tick = 16000 should be used
void systickInit( uint32_t ticks ) {
	if ((ticks - 1) > 0xffffff) return;  		// systick timer is 24 bit
	SYSTICK->LOAD = ticks - 1;
	SYSTICK->VAL = 0;
	SYSTICK->CTRL = BIT(0) | BIT(1) | BIT(2);  	// enable systick
	RCC->APB2ENR |= BIT(14);                   	// enable SYSCFG
}

void delay(unsigned ms) {
	uint32_t until = ms_ticks + ms;      			// future "stoppage time"
	while (ms_ticks < until) (void) 0;   			// polling
}



// ----------------------
// ------ US DELAY ------
// ----------------------

void usDelayInit(void) {
    RCC->APB1ENR |= 0x1;

    // reset the timer
    TIM2->CR1 = 0;
    TIM2->CNT = 0;

    // apply prescaler + start timer
    TIM2->PSC = PRESCALER;
    TIM2->ARR = 0xFFFFFFFF;
    TIM2->EGR = 0x01;
    TIM2->CR1 |= 0x01;
}

void delayUs( uint32_t microseconds ) {
    uint32_t start_time = TIM2->CNT;
    while ((TIM2->CNT - start_time) < microseconds);
}
