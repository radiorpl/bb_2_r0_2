/*
8/3/17
Volume control for audio system Atm_wav_1 working in preset steps
8/6/17 
add separate controls for each instance
8/9/17
split vol into 33 steps
added variables for sev seg display level
8/13/17
added display and home parts
8/14/17
added events for all state for trigger()
8/17/17
triggering display still not working. Adding checkMillis function for on_loop
8/18/17
r2 TOTAL REWRITE 
works controlling volumes
haven't worked out displays yet
8/19/17 
attempt to add display
8/20/17
successfully connected sev seg
*/	
#include "Atm_master_vol.h"
#include "audio_system.h"
#include "display_def.h"
#include "button_counters.h"

int mas_vol_level; //variables for display
int vol_wav_1_level; 
int vol_wav_2_level; 

	
Atm_master_vol& Atm_master_vol::begin( int vol_con ) {
  	// clang-format off
	static const state_t state_table[] PROGMEM = {
		/*               	ON_ENTER    			ON_LOOP   		ON_EXIT		EVT_ENC_UP		EVT_ENC_DOWN		EVT_BTN_1	 	EVT_VOL_CONTROL 	ELSE */	 				
		/*VOL_CONTROL */	ENT_VOL_CONTROL, 		-1,					-1,		  VOL_UP,	  	 VOL_DOWN,			  BTN_1,		    VOL_CONTROL,		-1,	
		/*VOL_UP 	  */	ENT_VOL_UP, 			-1,					-1,			-1,	  	 		-1,					-1,				VOL_CONTROL,		-1,
		/*VOL_DOWN 	  */	ENT_VOL_DOWN, 			-1,					-1,			-1,	  	 		-1,					-1,				VOL_CONTROL,		-1,
		/*BTN_1 	  */	ENT_BTN_1, 				-1,					-1,			-1,	  	 		-1,					-1,				VOL_CONTROL,		-1,
	};
    // clang-format on
    Machine::begin( state_table, ELSE );
	vol_control = vol_con;
	//volume_position = 5;
	volume_level = 0.5;
	AudioMemory(160);	    
	//sets mixers for 2 wav playback, no effects
	mixer1.gain(0, 0.5); 	//wav1 stereo to mono
    mixer1.gain(1, 0.5);
    mixer2.gain(0, 0.5);	//wav2
    mixer2.gain(1, 0.5);
	mixer6.gain(0, 0.5);	//mix 1 and 2
	mixer6.gain(0, 0.5);
	mixer9.gain(0, 0.5);	//mix with effects
	display_delay = 100;  //wait after entering screen state
    return *this;	
}

int Atm_master_vol::event( int id ) {
  switch ( id ) {
    case EVT_ENC_UP:
		return 0;	  
    case EVT_ENC_DOWN:
		return 0;	
    case EVT_BTN_1:
		return 0;
	case EVT_VOL_CONTROL:
		return 0;
  	}  
  	return 0;
}
/* Add C++ code for each action
 * This generates the 'output' for the state machine
 *
 * Available connectors:
 *   push( connectors, ON_PRESS, 0, <v>, <up> );
 */
void Atm_master_vol::action( int id ) {
	switch ( id ) {
		case ENT_BTN_1:    //reset counter frome evt_btn_1
			btn1();
			return;		
		case ENT_VOL_CONTROL:
			setVolume();
			return;		
		case ENT_VOL_UP:
			encoderUp();
			return;	
		case ENT_VOL_DOWN:
			encoderDown();
			return;	
	}
}
/* Optionally override the default trigger() method
 * Control how your machine processes trigger
 */

Atm_master_vol& Atm_master_vol::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_master_vol::state( void ) {
  return Machine::state();
  }


Atm_master_vol& Atm_master_vol::setVolume( void ) {
	if ( vol_control == 0 ) {  		      //master 	
		if ( volume_position > last_volume_position ) {
			if ( volume_level < 0.99 ) {
				for ( int x = 0; x < 100; x++ ) {
					volume_level += 0.001;
					sgtl5000_1.volume(volume_level);
					delay(1);
			    }
			}
		}	
		if ( volume_position < last_volume_position ) {
			if ( volume_level > 0.02 ) {
				for ( int x = 0; x < 100; x++ ) {
					volume_level -= 0.001;
					sgtl5000_1.volume(volume_level);
					delay(1);
		        }
			}
		}
		Serial.println("master volume");
		Serial.println(volume_level);
		
		if ( volume_level < 0.02 ) {   //range
			volume_level = 0.0;
		}	
		if ( volume_level > 0.97 ) {
			volume_level = 0.99;
		}
			
		if ( volume_level < 0.09 ) {
			mas_vol_level = 0;
		}
		else if ( volume_level < 0.19 ) {
			mas_vol_level = 1;
		}
		else if ( volume_level < 0.29 ) {
			mas_vol_level = 2;
		}
		else if ( volume_level < 0.39 ) {
			mas_vol_level = 3;
		}
		else if ( volume_level < 0.49 ) {
			mas_vol_level = 4;
		}
		else if ( volume_level < 0.59 ) {
			mas_vol_level = 5;
		}
		else if ( volume_level < 0.69 ) {
			mas_vol_level = 6;
		}
		else if ( volume_level < 0.79 ) {
			mas_vol_level = 7;
		}
		else if ( volume_level < 0.89 ) {
			mas_vol_level = 8;
		}
		else if ( volume_level >= 0.9 ) {
			mas_vol_level = 9;
		}
		last_volume_position = volume_position;
	}
	//===================================//wav1
	else if ( vol_control == 1 ){  	
		if ( volume_position > last_volume_position ) {
			if ( volume_level < 0.99 ) {
				for ( int x = 0; x < 100; x++ ) {
					volume_level += 0.001;
					mixer6.gain(0, volume_level);
					delay(1);
			    }
			}
		}	
		if ( volume_position < last_volume_position ) {
			if ( volume_level > 0.02 ) {
				for ( int x = 0; x < 100; x++ ) {
					volume_level -= 0.001;
					mixer6.gain(0, volume_level);
					delay(1);
		        }
				Serial.println("bira 1 volume");
				Serial.println(volume_level);
			}
		}
		
		if ( volume_level < 0.02 ) {
			volume_level = 0.0;
		}	
		if ( volume_level > 0.97 ) {
			volume_level = 0.99;
		}
			
		if ( volume_level < 0.09 ) {
			vol_wav_1_level = 0;
		}
		else if ( volume_level < 0.19 ) {
			vol_wav_1_level = 1;
		}
		else if ( volume_level < 0.29 ) {
			vol_wav_1_level = 2;
		}
		else if ( volume_level < 0.39 ) {
			vol_wav_1_level = 3;
		}
		else if ( volume_level < 0.49 ) {
			vol_wav_1_level = 4;
		}
		else if ( volume_level < 0.59 ) {
			vol_wav_1_level = 5;
		}
		else if ( volume_level < 0.69 ) {
			vol_wav_1_level = 6;
		}
		else if ( volume_level < 0.79 ) {
			vol_wav_1_level = 7;
		}
		else if ( volume_level < 0.89 ) {
			vol_wav_1_level = 8;
		}
		else if ( volume_level >= 0.9 ) {
			vol_wav_1_level = 9;
		}
		last_volume_position = volume_position;
	}
//===================================//wav2
	
	else if ( vol_control == 2 ){  	
		if ( volume_level < 0.02 ) {
			volume_level = 0.0;
		}	
		if ( volume_level > 0.97 ) {
			volume_level = 0.99;
		}
		if ( volume_position > last_volume_position ) {
			for ( int x = 0; x < 100; x++ ) {
				volume_level += 0.001;
				mixer6.gain(1, volume_level);
				delay(1);
		    }
		}
		if ( volume_position < last_volume_position ) {
			for ( int x = 0; x < 100; x++ ) {
				volume_level -= 0.001;
				mixer6.gain(1, volume_level);
				delay(1);
	        }
			Serial.println("bira 2 volume");
			Serial.println(volume_level);
		}
		if ( volume_level < 0.09 ) {
			vol_wav_2_level = 0;
		}
		else if ( volume_level < 0.2 ) {
			vol_wav_2_level = 1;
		}
		else if ( volume_level < 0.3 ) {
			vol_wav_2_level = 2;
		}
		else if ( volume_level < 0.4 ) {
			vol_wav_2_level = 3;
		}
		else if ( volume_level < 0.5 ) {
			vol_wav_2_level = 4;
		}
		else if ( volume_level < 0.6 ) {
			vol_wav_2_level = 5;
		}
		else if ( volume_level < 0.7 ) {
			vol_wav_2_level = 6;
		}
		else if ( volume_level < 0.8 ) {
			vol_wav_2_level = 7;
		}
		else if ( volume_level < 0.9 ) {
			vol_wav_2_level = 8;
		}
		else if ( volume_level >= 0.9 ) {
			vol_wav_2_level = 9;
		}
		last_volume_position = volume_position;
	}
	return *this;
}

Atm_master_vol& Atm_master_vol::btn1( void ) {
    if ( (displayMain.state() == displayMain.MASTER_VOL) || (displayMain.state() == displayMain.VOL_WAV_1) || (displayMain.state() == displayMain.VOL_WAV_2) ) {
		if ( enc_button_counter_3 == 0 ) {
			displayMain.trigger( displayMain.EVT_MASTER_VOL );
		}
		else if ( enc_button_counter_3 == 1 ) {
			displayMain.trigger( displayMain.EVT_VOL_WAV_1 );
		}
		else if ( enc_button_counter_3 == 2 ) {
			displayMain.trigger( displayMain.EVT_VOL_WAV_2 );
		}
		paramTimer.trigger( paramTimer.EVT_START );
    }
	else {
   		paramTimer.trigger( paramTimer.EVT_START );   //trigger timer
   		Serial.println("wait display triggered");
		if ( vol_control == 0 ) {
			displayMain.trigger( displayMain.EVT_MASTER_VOL );  
		}
		else if ( vol_control == 1 ) {
			displayMain.trigger( displayMain.EVT_VOL_WAV_1 );
		}
		else if ( vol_control == 2 ) {
			displayMain.trigger( displayMain.EVT_VOL_WAV_2 );
		}								
		delay(display_delay);       					//display wait	
	}
	trigger( EVT_VOL_CONTROL );			//back to vol control
	return *this;
}

Atm_master_vol& Atm_master_vol::encoderUp( void ) {	
	
	if ( (displayMain.state() == displayMain.MASTER_VOL) || (displayMain.state() == displayMain.VOL_WAV_1) || (displayMain.state() == displayMain.VOL_WAV_2) ) {
		volume_position += 1;
		if ( vol_control == 0 ){
			displayMain.trigger( displayMain.EVT_MASTER_VOL );
		}
		else if ( vol_control == 1 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_1 );	
		}
		else if ( vol_control == 2 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_2 );	
		}		
		Serial.println("enc up");
		Serial.println(volume_position);
		paramTimer.trigger( paramTimer.EVT_START );
	}
	else {
		paramTimer.trigger( paramTimer.EVT_START );
		Serial.println("wait display triggered");
		if ( vol_control == 0 ){
			displayMain.trigger( displayMain.EVT_MASTER_VOL );
		}
		else if ( vol_control == 1 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_1 );	
		}
		else if ( vol_control == 2 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_2 );	
		}		
		delay(display_delay);	
	}
	trigger( EVT_VOL_CONTROL );	
	return *this;
}

Atm_master_vol& Atm_master_vol::encoderDown( void ) {
	if ( (displayMain.state() == displayMain.MASTER_VOL) || (displayMain.state() == displayMain.VOL_WAV_1) || (displayMain.state() == displayMain.VOL_WAV_2) ) {
		volume_position -= 1;
		if ( vol_control == 0 ){
			displayMain.trigger( displayMain.EVT_MASTER_VOL );
		}
		else if ( vol_control == 1 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_1 );	
		}
		else if ( vol_control == 2 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_2 );	
		}		
		Serial.println("enc down");
		Serial.println(volume_position);
		Serial.println(volume_position);
		paramTimer.trigger( paramTimer.EVT_START );
	}
	else {
		paramTimer.trigger( paramTimer.EVT_START );
		Serial.println("wait display triggered");
		if ( vol_control == 0 ){
			displayMain.trigger( displayMain.EVT_MASTER_VOL );
		}
		else if ( vol_control == 1 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_1 );	
		}
		else if ( vol_control == 2 ){
			displayMain.trigger( displayMain.EVT_VOL_WAV_2 );	
		}		
		delay(display_delay);
	}
	trigger( EVT_VOL_CONTROL );
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

Atm_master_vol& Atm_master_vol::onPress( Machine& machine, int event ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, machine, event );
  return *this;
}

Atm_master_vol& Atm_master_vol::onPress( atm_cb_push_t callback, int idx ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, callback, idx );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_master_vol& Atm_master_vol::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "MASTER_VOL\0\EVT_ENC_UP\0EVT_ENC_DOWN\0EVT_BTN_1\0EVT_TIMER\0EVT_VOL_CONTROL\0ELSE\0VOL_CONTROL\0VOL_UP\0VOL_DOWN\0BTN_1" );
  return *this;
}
