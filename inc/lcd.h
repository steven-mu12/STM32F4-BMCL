#include <stdio.h>
#include <stdint.h>

// ------ MACROS -----
#define BIT(x) (1U << (x))


// ----- STRUCTURES -----
struct lcd {
	uint16_t D7, D6, D5, D4, RS, E;
};


// ----- USER FUNCTIONS DECLARATIONS -----
void initDisplay( struct lcd *lcd, uint16_t D4i, uint16_t D5i, uint16_t D6i, uint16_t D7i, uint16_t RSi, uint16_t Ei );
void clearDisplay( struct lcd *lcd );
void writeDisplay( struct lcd *lcd, char *data, int length );
void setCursor( struct lcd *lcd, int row, int col );


// ----- LOW LEVEL FUNCTIONS DECLARATIONS -----
// note that the user should not use these directly
void _toggle_en( struct lcd *lcd );
void _write_command( struct lcd *lcd, uint8_t command);
void _write_fourbits( struct lcd *lcd, uint8_t command );
