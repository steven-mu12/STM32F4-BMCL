#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "hcsr04.h"
#include "gpio.h"
#include "delay.h"

// -- variables
uint32_t timer_output;


// ----------------------------------
// ---- USER COMMAND DEFINITIONS ----
// ----------------------------------

void hcsr04Init( struct hcsr04 *sensor, uint16_t trigger, uint16_t echo ){
	// -- init the pins, and assign to struct
	gpioPinmode(trigger, GPIO_MODE_OUTPUT);
	gpioPinmode(echo, GPIO_MODE_INPUT);
	sensor->trigPin = trigger;
	sensor->echoPin = echo;
}


uint32_t measureDistance( struct hcsr04 *sensor ){

	// -- send the pulse
	gpioDigitalWrite( sensor->trigPin, 0 );
	delayUs(2);

	gpioDigitalWrite( sensor->trigPin, 1 );
	delayUs(10);
	gpioDigitalWrite( sensor->trigPin, 0 );

	// -- read the response & calculate the distance & return it
	// basically pulseIn() + calculateDistance()

	// poll until echo pin is high, then start TIM2, then poll until echo pin is low, then stop TIM2
	while (gpioDigitalRead(sensor->echoPin) != 1);
	uint32_t start_time = TIM2->CNT;
	while (gpioDigitalRead(sensor->echoPin) != 0);
	timer_output = TIM2->CNT - start_time;

	// use timer_output (time in us) to calculate the distance
	return(	(int)(timer_output*0.034/2) );

}



// ---------------------------------------
// ---- LOW LEVEL COMMAND DEFINITIONS ----
// ---------------------------------------
// note that user should not use these directly


