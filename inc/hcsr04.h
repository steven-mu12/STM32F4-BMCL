#include <stdint.h>
#include "gpio.h"
#include "delay.h"

// hcsr04 sensor struct
struct hcsr04 {
	uint16_t trigPin, echoPin;
};


// ----- USER FUNCTIONS DECLARATIONS -----
void hcsr04Init( struct hcsr04 *sensor, uint16_t trigger, uint16_t echo );
uint32_t measureDistance( struct hcsr04 *sensor );


// ----- LOW LEVEL FUNCTIONS DECLARATIONS -----
// note that the user should not use these directly

