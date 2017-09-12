#include "Atm_enc_button.h"

int enc_button_counter_1;
int enc_button_counter_2;
int enc_button_counter_3;
int enc_button_counter_4;
int enc_button_counter_5;
int last_enc_button_counter_1;
int last_enc_button_counter_2;
int last_enc_button_counter_3;
int last_enc_button_counter_4;
int last_enc_button_counter_5;

Atm_enc_button& Atm_enc_button::begin(int encButton) {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*             	ON_ENTER    ON_LOOP  ON_EXIT  EVT_BTN_1  EVT_ENC_UP   EVT_ENC_DOWN	 ELSE */
	/* IDLE		*/    -1,  		   -1,      -1,   COUNT_UP,   COUNT_UP,   COUNT_DOWN,	-1,
	/* COUNT_UP */ ENT_COUNT_UP,   -1,      -1,  	-1,   		-1,			-1,			IDLE,
  /* COUNT_DOWN */ ENT_COUNT_DOWN, -1,      -1,     -1,   		-1,			-1,			IDLE,
  };
  // clang-format on
  Machine::begin( state_table, ELSE );
  encBtn = encButton;
  enc_button_counter_1 = 0;
  enc_button_counter_2 = 0;
  enc_button_counter_3 = 0;
  enc_button_counter_4 = 0;
  enc_button_counter_5 = 0; 
  return *this;          
}

/* Add C++ code for each internally handled event (input) 
 * The code must return 1 to trigger the event
 */

int Atm_enc_button::event( int id ) {
  switch ( id ) {
    case EVT_BTN_1:
      return 0;
    case EVT_ENC_UP:
      return 0;
    case EVT_ENC_DOWN:
      return 0;
  }
  return 0;
}

/* Add C++ code for each action
 * This generates the 'output' for the state machine
 */

void Atm_enc_button::action( int id ) {
  switch ( id ) {
	case ENT_COUNT_UP:
		countUp();
		return;
	case ENT_COUNT_DOWN:
		countDown();
		return;
	
  }
}

/* Optionally override the default trigger() method
 * Control how your machine processes triggers
 */

Atm_enc_button& Atm_enc_button::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_enc_button::state( void ) {
  return Machine::state();
}

Atm_enc_button& Atm_enc_button::countUp( void ) {  //==========changed button ranges since worked
	if ( encBtn == 1 ) {				
		enc_button_counter_1++;
	}
	else if ( encBtn == 2){
		enc_button_counter_2++;
	}
	else if ( encBtn == 3){
		enc_button_counter_3++;
	}
	else if ( encBtn == 4){
		enc_button_counter_4++;
	}
	else if ( encBtn == 5){
		enc_button_counter_5++;
	}				
  	if ( enc_button_counter_1 > 1 ){    //number of options for function menu -1 
  		enc_button_counter_1 = 0;
  	}
  	if ( enc_button_counter_2 > 1 ){    //track select
  		enc_button_counter_2 = 0;
  	}
  	if ( enc_button_counter_3 > 2 ){     //volumes
  		enc_button_counter_3 = 0;
  	}
  	if ( enc_button_counter_4 > 0 ){     //effects
  		enc_button_counter_4 = 0;
  	}
  	if ( enc_button_counter_5 > 4 ){     //effect parameters
  		enc_button_counter_5 = 0;
  	}
	Serial.print( "enc_button_counter_5 ");
	Serial.println( enc_button_counter_5 );
  return *this;
}
Atm_enc_button& Atm_enc_button::countDown( void ) {
  	if ( encBtn == 1 ) {				
  		enc_button_counter_1--;
  	}
  	else if ( encBtn == 2){
  		enc_button_counter_2--;
  	}
  	else if ( encBtn == 3){
  		enc_button_counter_3--;
  	}
  	else if ( encBtn == 4){
  		enc_button_counter_4--;
  	}
  	else if ( encBtn == 5){
  		enc_button_counter_5--;
  	}										
	
  	if ( enc_button_counter_1 < 0 ){    //number of options for function menu -1 
  		enc_button_counter_1 = 1;
  	}
  	if ( enc_button_counter_2 < 0 ){    //track select
  		enc_button_counter_2 = 1;
  	}
  	if ( enc_button_counter_3 < 0 ){     //volumes
  		enc_button_counter_3 = 2;
  	}
  	if ( enc_button_counter_4 < 0 ){     //effects
  		enc_button_counter_4 = 0;
  	}
  	if ( enc_button_counter_5 < 0 ){     //effect parameters
  		enc_button_counter_5 = 4;
  	}
   return *this;
}
/* Nothing customizable below this line                          
 ************************************************************************************************
*/

/* Public event methods
 *
 */

Atm_enc_button& Atm_enc_button::btn_1() {
  trigger( EVT_BTN_1 );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_enc_button& Atm_enc_button::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "ENCBUTTON\0EVT_BTN_1\0EVT_ENC_UP\0EVT_ENC_DOWN\0ELSE\0IDLE\0COUNT_UP\0COUNT_DOWN" );
  return *this;
}



