#include "Atm_fx_select.h"
#include "audio_system.h"
#include "display_def.h"
#include "button_counters.h"

int delay_on_off;

Atm_fx_select& Atm_fx_select::begin( int fx_con ) {
		static const state_t state_table[] PROGMEM = {
		
		 /*               	ON_ENTER    			ON_LOOP   		ON_EXIT	   EVT_CONTROL      EVT_ENC_UP		EVT_ENC_DOWN		EVT_BTN_1	 	ELSE */	 
		/*CONTROL     */	ENT_CONTROL, 		    -1,					-1,		CONTROL,           ENC_UP,	  	 ENC_DOWN,			  BTN_1,    	-1,	
		/*ENC_UP 	  */	ENT_ENC_UP, 			-1,					-1,		CONTROL,             -1,	  	 	-1,					-1,			-1,
		/*ENC_DOWN 	  */	ENT_ENC_DOWN, 			-1,					-1,	    CONTROL,             -1,	  	 	-1,					-1,			-1,
		/*BTN_1 	  */	ENT_BTN_1, 				-1,					-1,		CONTROL,	  	 	 -1,				-1,				    -1,		    -1,
		
		};
	Machine::begin( state_table, ELSE );
	fx_control = fx_con;
	display_delay = 100;
	fx_position = 0;
	return *this;	
}
//events
int Atm_fx_select::event( int id ) {
  switch ( id ) {
  	case EVT_CONTROL:
  		return 0;
    case EVT_ENC_UP:
		return 0;	  
    case EVT_ENC_DOWN:
		return 0;	
    case EVT_BTN_1:
		return 0;
  	}  
  	return 0;
}
//actions
void Atm_fx_select::action( int id ) {
	switch ( id ) {	
		case ENT_CONTROL:
			control();
			return;		
		case ENT_ENC_UP:
			encoderUp();
			return;	
		case ENT_ENC_DOWN:
			encoderDown();
			return;	
		case ENT_BTN_1:    //reset counter frome evt_btn_1
			btn1();
			return;	
	}
}

  Atm_fx_select& Atm_fx_select::trigger( int event ) {
    Machine::trigger( event );
    return *this;
  }

  int Atm_fx_select::state( void ) {
    return Machine::state();
  }
  //===================================================control============================
  
  Atm_fx_select& Atm_fx_select::control( void ) {
	  if ( fx_control == 0) {
		  if ( fx_position < 0) {
			  fx_position = 0;
		  }
		  if ( fx_position > 1) {
			  fx_position = 0;
		  }
		  delay_on_off = fx_position;
		  if ( delay_on_off == 0) {
	  	    delaySend1.trigger( delaySend1.EVT_OFF );    
	  	    delaySend2.trigger( delaySend2.EVT_OFF );
	  	    delayTime1.trigger( delayTime1.EVT_OFF );
	  	    delayFb1.trigger( delayFb1.EVT_OFF );
	  	    delayMix.trigger( delayMix.EVT_OFF );
		  }
		  else if ( delay_on_off == 1) {
	  	    delaySend1.trigger( delaySend1.EVT_CONTROL );    
	  	    delaySend2.trigger( delaySend2.EVT_CONTROL );
	  	    delayTime1.trigger( delayTime1.EVT_CONTROL );
	  	    delayFb1.trigger( delayFb1.EVT_CONTROL );
	  	    delayMix.trigger( delayMix.EVT_CONTROL );
		  }
	  }
	  return *this;
  }

  
  //======================================================btns/encoders=====================
  
  Atm_fx_select& Atm_fx_select::btn1( void ) {
    if ( (displayMain.state() == displayMain.DELAY) ) {
  		
		if ( enc_button_counter_4 == 0 ) {
			fx_position += 1;
			displayMain.trigger( displayMain.EVT_DELAY );
		}
		paramTimer.trigger( paramTimer.EVT_START );   //trigger timer
	}
	else {
     		paramTimer.trigger( paramTimer.EVT_START );   //trigger timer
     		Serial.println("wait display triggered");
  		if ( fx_control == 0 ) {
  			displayMain.trigger( displayMain.EVT_DELAY );  
  		}							
  		delay(display_delay);       					//display wait	
	}
	trigger( EVT_CONTROL );			//back to vol control
  	return *this;
  }

  Atm_fx_select& Atm_fx_select::encoderUp( void ) {	
    if ( (displayMain.state() == displayMain.DELAY) ) {
		if ( enc_button_counter_4 == 0 ) {
			displayMain.trigger( displayMain.EVT_DELAY );
  		}
		paramTimer.trigger( paramTimer.EVT_START );   //trigger timer
	}
  	else {
     		paramTimer.trigger( paramTimer.EVT_START );   //trigger timer
     		Serial.println("wait display triggered");
  		if ( fx_control == 0 ) {
  			displayMain.trigger( displayMain.EVT_DELAY );  
  		}							
  		delay(display_delay);       					//display wait	
  	}
	trigger( EVT_CONTROL );			//back to vol control
  	return *this;
  }

  Atm_fx_select& Atm_fx_select::encoderDown( void ) {
   if ( (displayMain.state() == displayMain.DELAY) ) {
		if ( enc_button_counter_4 == 0 ) {
			displayMain.trigger( displayMain.EVT_DELAY );
  		}
		paramTimer.trigger( paramTimer.EVT_START );   //trigger timer
	}
  	else {
     		paramTimer.trigger( paramTimer.EVT_START );   //trigger timer
     		Serial.println("wait display triggered");
  		if ( fx_control == 0 ) {
  			displayMain.trigger( displayMain.EVT_DELAY );  
  		}							
  		delay(display_delay);       					//display wait
  		trigger( EVT_CONTROL );			//back to vol control	
  	}
  	return *this;
  }
						
  /* Nothing customizable below this line                          
   ************************************************************************************************
  */

  /* Public event methods
   *
   */
  /*
   * onPress() push connector variants ( slots 1, autostore 0, broadcast 0 )
   */

  Atm_fx_select& Atm_fx_select::onPress( Machine& machine, int event ) {
    onPush( connectors, ON_PRESS, 0, 1, 1, machine, event );
    return *this;
  }

  Atm_fx_select& Atm_fx_select::onPress( atm_cb_push_t callback, int idx ) {
    onPush( connectors, ON_PRESS, 0, 1, 1, callback, idx );
    return *this;
  }

  /* State trace method
   * Sets the symbol table and the default logging method for serial monitoring
   */

  Atm_fx_select& Atm_fx_select::trace( Stream & stream ) {
    Machine::setTrace( &stream, atm_serial_debug::trace,
      "FX_SELECT\0EVT_CONTROL\0EVT_ENC_UP\0EVT_ENC_DOWN\0EVT_BTN_1\0ELSE\0CONTROL\0ENC_UP\0ENC_DOWN\0BTN_1" );
    return *this;
  }
