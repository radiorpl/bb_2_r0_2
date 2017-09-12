/*
src file for function to play wav in loop
button stops or starts
7/15/17
loop function works by putting playCheck in ON_LOOP event 
added button skips tracks
added play function has input filename
7/19/17
changed to encoders to toggle tracks up and down
works but needs debouncing or something b/c encoder is too sensitive
8/1/17
added instances, this version with 2 instances
looping works
8/14/17
add display stuff
8/29/17
total rewrite, new branch
*/
#include "Atm_wav_1.h"
#include "display_def.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "button_counters.h"


// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=88,160
AudioPlaySdWav           playSdWav1;     //xy=89,66
AudioMixer4              mixer2;         //xy=232,163
AudioMixer4              mixer1;         //xy=238,84
AudioEffectDelay         delay1;         //xy=309,331
AudioMixer4              mixer3;         //xy=495,35
AudioMixer4              mixer4;         //xy=505,131
AudioMixer4              mixer7;         //xy=525,381
AudioMixer4              mixer5;         //xy=678,70
AudioMixer4              mixer6;         //xy=680,261
AudioMixer4              mixer8;         //xy=682,375
AudioMixer4              mixer9;         //xy=855,328
AudioOutputI2S           i2s1;           //xy=1023,334
AudioConnection          patchCord1(playSdWav2, 0, mixer2, 0);
AudioConnection          patchCord2(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord3(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord4(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord5(mixer2, 0, mixer3, 1);
AudioConnection          patchCord6(mixer2, 0, mixer6, 1);
AudioConnection          patchCord7(mixer1, 0, mixer3, 0);
AudioConnection          patchCord8(mixer1, 0, mixer6, 0);
AudioConnection          patchCord9(delay1, 0, mixer3, 2);
AudioConnection          patchCord10(delay1, 0, mixer7, 0);
AudioConnection          patchCord11(delay1, 1, mixer3, 3);
AudioConnection          patchCord12(delay1, 1, mixer7, 1);
AudioConnection          patchCord13(delay1, 2, mixer7, 2);
AudioConnection          patchCord14(delay1, 2, mixer4, 0);
AudioConnection          patchCord15(delay1, 3, mixer7, 3);
AudioConnection          patchCord16(delay1, 3, mixer4, 1);
AudioConnection          patchCord17(mixer3, 0, mixer5, 0);
AudioConnection          patchCord18(mixer4, 0, mixer5, 1);
AudioConnection          patchCord19(mixer7, 0, mixer8, 0);
AudioConnection          patchCord20(mixer5, delay1);
AudioConnection          patchCord21(mixer6, 0, mixer9, 0);
AudioConnection          patchCord22(mixer8, 0, mixer9, 1);
AudioConnection          patchCord23(mixer9, 0, i2s1, 0);
AudioConnection          patchCord24(mixer9, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=478,626
// GUItool: end automatically generated code

//display levels
int track_1_level;
int track_2_level;
int last_state_1;
int last_state_2;

Atm_wav_1& Atm_wav_1::begin( int instance ) {
  	// clang-format off
	static const state_t state_table[] PROGMEM = {
		/*               	ON_ENTER    		ON_LOOP    	ON_EXIT		EVT_WAV_OFF     EVT_WAV_ON    EVT_ENC_UP	EVT_ENC_DOWN	EVT_BTN_1	EVT_BTN_2	  ELSE */
		/*	WAV_OFF */		ENT_WAV_OFF,		-1,				-1,	     WAV_OFF,		  WAV_ON,		ENC_UP,	 	 ENC_DOWN,		  BTN_1,	 BTN_2,			-1,
		/*	WAV_ON */		ENT_WAV_ON, 	    -1,				-1,		 WAV_OFF,		  WAV_ON,		ENC_UP,	 	 ENC_DOWN,		  BTN_1,	 BTN_2,	   	WAV_ON,
		/*	ENC_UP */		ENT_ENC_UP,		    -1,				-1,		 WAV_OFF,		  WAV_ON,		  -1,		    -1,			   -1,		   -1,			-1,
	    /* ENC_DOWN */		ENT_ENC_DOWN,		-1,				-1,		 WAV_OFF, 		  WAV_ON,		  -1,			-1,			   -1,		   -1,			-1,
		/*	BTN_1 */		ENT_BTN_1,		    -1,				-1,		 WAV_OFF, 		  WAV_ON,		  -1,			-1,			   -1,		   -1,			-1,
		/*	BTN_2 */		ENT_BTN_2,		    -1,				-1,		 WAV_OFF, 		  WAV_ON,		  -1,			-1,			   -1,		   -1,			-1,
		
	};
    // clang-format on
    Machine::begin( state_table, ELSE );	//r2 moved audio setup to master vol
	player_instance = instance;
	track_1_level = 1;
	track_2_level = 1;
	display_delay = 100;
    return *this;	
}

int Atm_wav_1::event( int id ) {
  switch ( id ) {
		case EVT_WAV_OFF:
			return 0;
		case EVT_WAV_ON:
			return 0;
		case EVT_ENC_UP:
			return 0;  
		case EVT_ENC_DOWN:
			return 0;  
		case EVT_BTN_1:
			return 0;
		case EVT_BTN_2:
			return 0;   
	}  
	return 0;
}
/*Actions
 * Available connectors:
 *   push( connectors, ON_PRESS, 0, <v>, <up> );
 */
void Atm_wav_1::action( int id ) {
	switch ( id ) {
		case ENT_WAV_OFF:
			stop();
			return;
		case ENT_WAV_ON:
			play();
			return;
		case ENT_ENC_UP:
			encoderUp();
			return;
		case ENT_ENC_DOWN:
			encoderDown();
			return;
		case ENT_BTN_1:
			btn1();
			return;	
		case ENT_BTN_2:
			btn2();
			return;	
	}	
}
/* Optionally override the default trigger() method
 * Control how your machine processes trigger
 */

Atm_wav_1& Atm_wav_1::trigger( int event ) {
  Machine::trigger( event );
  return *this;
}

/* Optionally override the default state() method
 * Control what the machine returns when another process requests its state
 */

int Atm_wav_1::state( void ) {
  return Machine::state();
}
//												=============PLAY==============
Atm_wav_1& Atm_wav_1::play( void ) {
	//last_state_1 = 1;	
	//Serial.println( last_state );
	if ( player_instance == 1 ) {		//player 1 	
		if ( (playSdWav1.isPlaying() == false) || (track_1_level != last_track_1_level) ) {
			if (track_1_level == 1) {
				playSdWav1.play("DRONE1.WAV"); //play wav file
			}
			else if (track_1_level == 2) {
				playSdWav1.play("DRONE2.WAV"); 
			}
			else if (track_1_level == 3) {
				playSdWav1.play("DRONE3.WAV"); 
			}
			else if (track_1_level == 4) {
				playSdWav1.play("DRONE4.WAV"); 
			}
			else if (track_1_level == 5) {
				playSdWav1.play("DRONE5.WAV"); 
			}
			last_state_1 = 1;
		}	
		last_track_1_level = track_1_level;
		delay(10);
		//Serial.print( "player no 1 - track " );
		//Serial.println( track_1_level );
	    }
		
	else if ( player_instance == 2 ) {
		if ( (playSdWav2.isPlaying() == false) || (track_2_level != last_track_2_level) ) {
			if (track_2_level == 1) {
				playSdWav2.play("DRONE1.WAV"); //play wav file
			}
			else if (track_2_level == 2) {
				playSdWav2.play("DRONE2.WAV"); 
			}
			else if (track_2_level == 3) {
				playSdWav2.play("DRONE3.WAV"); 
			}
			else if (track_2_level == 4) {
				playSdWav2.play("DRONE4.WAV"); 
			}
			else if (track_2_level == 5) {
				playSdWav2.play("DRONE5.WAV"); 
			}
			last_state_2 = 1;
		}
		last_track_2_level = track_2_level;
		delay(10);	
		//Serial.print( "player no 2 - track " );
		//Serial.println( track_1_level );	
		}
	return *this;
}

//                                 		===========STOP===========
Atm_wav_1& Atm_wav_1::stop( void ) {
	
	if ( player_instance == 1 ){
		playSdWav1.stop(); //stop wav file
		last_state_1 = 0;
		Serial.println("stop 1");
	}
	else if ( player_instance == 2 ){
		playSdWav2.stop(); //stop wav file
		last_state_2 = 0;
		Serial.println("stop 2");		
	}
	
	return *this;
}
//                                     ===========ENCODER UP==============
Atm_wav_1& Atm_wav_1::encoderUp( void ) {	
	  if ( displayMain.state() == displayMain.TRACK_WAV_1 || displayMain.state() == displayMain.TRACK_WAV_2 ) {
  		if ( player_instance == 1 ) {
  			track_1_level += 1;
  			if ( track_1_level > 4 ) {			//set range of track values
  				track_1_level = 5;
  			}
  			displayMain.trigger( displayMain.EVT_TRACK_WAV_1 );
  			if ( last_state_1 == 0 ) {
  				trigger( EVT_WAV_OFF );
  			}
  			else if ( last_state_1 == 1 ) {
  				trigger( EVT_WAV_ON );
  			}
  		}
  		else if ( player_instance == 2 ) {
  			track_2_level += 1;
  			if ( track_2_level > 4 ) {			
  				track_2_level = 5;
  			}
  			displayMain.trigger( displayMain.EVT_TRACK_WAV_2 );
  			//Serial.println( track_2_level);
  			if ( last_state_2 == 0 ) {
  				trigger( EVT_WAV_OFF );
  			}
  			else if ( last_state_2 == 1 ) {
  				trigger( EVT_WAV_ON );
  			}
  		}		
  		Serial.println("enc up");
  		paramTimer.trigger( paramTimer.EVT_START );
  	}
	else {
		paramTimer.trigger( paramTimer.EVT_START );
		Serial.println("wait display triggered");
		if ( player_instance == 1 ){
			displayMain.trigger( displayMain.EVT_TRACK_WAV_1 );
			delay( display_delay );
			if ( last_state_1 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_1 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
		else if ( player_instance == 2 ){
			displayMain.trigger( displayMain.EVT_TRACK_WAV_2 );
			delay( display_delay );
			if ( last_state_2 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_2 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}	
	}	
	return *this;
}
//                                     ===========ENCODER DOWN==============
Atm_wav_1& Atm_wav_1::encoderDown( void ) {	
	  if ( displayMain.state() == displayMain.TRACK_WAV_1 || displayMain.state() == displayMain.TRACK_WAV_2 ) {
  		if ( player_instance == 1 ) {
  			track_1_level -= 1;
  			if ( track_1_level < 2) {			//set range of track values
  				track_1_level = 1;
  			}
  			displayMain.trigger( displayMain.EVT_TRACK_WAV_1 );
  			if ( last_state_1 == 0 ) {
  				trigger( EVT_WAV_OFF );
  			}
  			else if ( last_state_1 == 1 ) {
  				trigger( EVT_WAV_ON );
  			}
  		}
  		else if ( player_instance == 2 ) {
  			track_2_level -= 1;
  			if ( track_2_level < 2 ) {			
  				track_2_level = 1;
  			}
  			displayMain.trigger( displayMain.EVT_TRACK_WAV_2 );
  			//Serial.println( track_2_level);
  			if ( last_state_2 == 0 ) {
  				trigger( EVT_WAV_OFF );
  			}
  			else if ( last_state_2 == 1 ) {
  				trigger( EVT_WAV_ON );
  			}
  		}		
  		Serial.println("enc down");
  		paramTimer.trigger( paramTimer.EVT_START );
  	}
	else {
		paramTimer.trigger( paramTimer.EVT_START );
		Serial.println("wait display triggered");
		if ( player_instance == 1 ){
			displayMain.trigger( displayMain.EVT_TRACK_WAV_1 );
			delay( display_delay );
			if ( last_state_1 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_1 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
		else if ( player_instance == 2 ){
			displayMain.trigger( displayMain.EVT_TRACK_WAV_2 );
			delay( display_delay );
			if ( last_state_2 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_2 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}	
	}	
	return *this;
}
//												===========Btn1
Atm_wav_1& Atm_wav_1::btn1( void ) {			//triggers display for tracks
	if ( displayMain.state() == displayMain.TRACK_WAV_1 || displayMain.state() == displayMain.TRACK_WAV_2 ) {
		if ( player_instance == 1 ) {
			displayMain.trigger( displayMain.EVT_TRACK_WAV_2 );
			if ( last_state_1 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_1 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
		else if ( player_instance == 2 ) {
			displayMain.trigger( displayMain.EVT_TRACK_WAV_1 );
			if ( last_state_2 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_2 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
		paramTimer.trigger( paramTimer.EVT_START );	
	}
	else {
		paramTimer.trigger( paramTimer.EVT_START );
		Serial.println("wait display triggered");
		if ( player_instance == 1 ){
			displayMain.trigger( displayMain.EVT_TRACK_WAV_1 );
			delay( display_delay );
			if ( last_state_1 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_1 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
		else if ( player_instance == 2 ){
			displayMain.trigger( displayMain.EVT_TRACK_WAV_2 );
			delay( display_delay );
			if ( last_state_2 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_2 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
	}	
	return *this;
}

Atm_wav_1& Atm_wav_1::btn2( void ) {			//triggers display for tracks
	if ( displayMain.state() == displayMain.PLAY_WAV_1 || displayMain.state() == displayMain.PLAY_WAV_2 ) {
		if ( player_instance == 1) {
			displayMain.trigger( displayMain.EVT_PLAY_WAV_1 );
			if ( last_state_1 == 0 ) {
				trigger( EVT_WAV_ON );
			}
			else if ( last_state_1 == 1 ) {
				trigger( EVT_WAV_OFF );
			}
		}
		else if ( player_instance == 2) {
			displayMain.trigger( displayMain.EVT_PLAY_WAV_2 );
			if ( last_state_2 == 0 ) {
				trigger( EVT_WAV_ON );
			}
			else if ( last_state_2 == 1 ) {
				trigger( EVT_WAV_OFF );
			}
		}
		paramTimer.trigger( paramTimer.EVT_START );
	}	
	else {
		paramTimer.trigger( paramTimer.EVT_START );
		Serial.println("wait display triggered");
		if ( player_instance == 1 ){
			displayMain.trigger( displayMain.EVT_PLAY_WAV_1 );
			delay( display_delay );
			if ( last_state_1 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_1 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
		else if ( player_instance == 2 ){
			displayMain.trigger( displayMain.EVT_PLAY_WAV_2 );
			delay( display_delay );
			if ( last_state_2 == 0 ) {
				trigger( EVT_WAV_OFF );
			}
			else if ( last_state_2 == 1 ) {
				trigger( EVT_WAV_ON );
			}
		}
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
Atm_wav_1& Atm_wav_1::btn_1() {( last_state == 0 ) {
			trigger( EVT_WAV_OFF );
  trigger( EVT_BTN_1 );
  return *this;
}
*/
/*
 * onPress() push connector variants ( slots 1, autostore 0, broadcast 0 )
 */

Atm_wav_1& Atm_wav_1::onPress( Machine& machine, int event ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, machine, event );
  return *this;
}

Atm_wav_1& Atm_wav_1::onPress( atm_cb_push_t callback, int idx ) {
  onPush( connectors, ON_PRESS, 0, 1, 1, callback, idx );
  return *this;
}

/* State trace method
 * Sets the symbol table and the default logging method for serial monitoring
 */

Atm_wav_1& Atm_wav_1::trace( Stream & stream ) {
  Machine::setTrace( &stream, atm_serial_debug::trace,
    "WAV_1\0EVT_WAV_OFF\0EVT_WAV_ON\0EVT_ENC_UP\0EVT_ENC_DOWN\0EVT_BTN_1\0EVT_BTN_2\0ELSE\0WAV_OFF\0WAV_ON\0ENC_UP\0ENC_DOWN\0BTN_1\0EVT_BTN_2" );
  return *this;
}
/*
Atm_led& Atm_led::trigger( int event ) {
  if ( event > ELSE ) {
    play();
  } else {
    Machine::trigger( event );
  }
  return *this;
}
*/