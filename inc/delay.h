#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>


// TIM2 struct
#define CPU_CLOCK_HZ   16000000
#define PRESCALER      (CPU_CLOCK_HZ / 1000000) - 1  // prescaler

struct tim2 {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RESERVED0;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t RESERVED1;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
    volatile uint32_t OR;
};
#define TIM2 ((struct tim2 *) 0x40000000)



// ------ MS DELAY ------
void systickInit(uint32_t ticks);
void SysTick_Handler(void);
void delay(unsigned ms);


// ------ US DELAY ------
void usDelayInit(void);
void delayUs( uint32_t microseconds );


#endif
