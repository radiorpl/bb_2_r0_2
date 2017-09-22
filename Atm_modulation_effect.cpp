#include "Atm_modulation_effect.h"
#include "audio_system.h"
#include "display_def.h"
#include "button_counters.h"

int mod_send_level_1;
int mod_send_level_2;
int flange_offset_level;
int flange_depth_level;
int flange_rate_level;
int chorus_voice_level;
int flange_mix_level;
int chorus_mix_level;	
	
Atm_modulation_effect& Atm_modulation_effect::begin( int param_con ) {
  // clang-format off
  const static state_t state_table[] PROGMEM = {
    /*               	ON_ENTER    ON_LOOP  ON_EXIT  EVT_OFF  EVT_CONTROL  EVT_ENC_UP   EVT_ENC_DOWN  EVT_BTN_1   ELSE */  
   /*    OFF      */   ENT_OFF,       -1,      -1,      -1,     CONTROL,	  -1,            -1,         -1,        -1,
   /*    CONTROL  */   ENT_CONTROL,   -1,      -1,      OFF,    CONTROL,	  ENC_UP,      ENC_DOWN,    BTN_1,      -1,
   /*    ENC_UP   */   ENT_ENC_UP,    -1,      -1,   	-1,     CONTROL,		-1,          -1,     	 -1,        -1,   
   /*    ENC_DOWN */   ENT_ENC_DOWN,  -1,      -1,   	-1,     CONTROL,		-1,          -1,     	 -1,        -1, 
   /*    BTN_1    */   ENT_BTN_1,     -1,      -1,   	-1,     CONTROL,		-1,          -1,     	 -1,        -1, 	  
	    
  };
  
  Machine::begin( state_table, ELSE );
  param_control = param_con;
  display_delay = 100;
  param_level = 0.5;
  mixer9.gain(1, 0.5);  //flange mix
  mixer9.gain(2, 0.5);   //chorus mix
  mixer10.gain(0, 0.5);  //wav 1 send
  mixer10.gain(1, 0.5);  //wav 2 send
  s_idx = FLANGE_DELAY_LENGTH/4;
  s_depth = FLANGE_DELAY_LENGTH/4;
  s_freq = .5;
  n_chorus = 2;
  flange1.begin( fl_delayline, FLANGE_DELAY_LENGTH, s_idx, s_depth, s_freq );
  chorus1.begin( ch_delayline, CHORUS_DELAY_LENGTH, n_chorus );
  return *this; 
}

int Atm_modulation_effect::event( int id ) {
  switch ( id ) {
  	case EVT_OFF:
  	  return 0;	
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

void Atm_modulation_effect::action( int id ) {
  switch ( id ) {
  	case ENT_OFF:
  	  off();
  	  return;
	case ENT_CONTROL:
	  setLevel();
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
	}
}

Atm_modulation_effect& Atm_modulation_effect::trigger( int event ) {
  	Machine::trigger( event );
 	 return *this;
}

int Atm_modulation_effect::state( void ) {
  	return Machine::state();
}

Atm_modulation_effect& Atm_modulation_effect::setLevel( void ) {
	if ( param_control == 0 ) {		                       //send wav 1
		if ( param_position > last_param_position ) {
			if ( param_level < 0.99 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level += 0.001;
					mixer10.gain(0, param_level);
					delay(1);
			    }
			}
		}
		if ( param_position < last_param_position ) {
			if ( param_level > 0.02 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level -= 0.001;
					mixer10.gain(0, param_level);
					delay(1);
		        }
			}
		}
		Serial.println("modulation send 1");
		Serial.println(param_level);
	}	
	if ( param_control == 1 ) {		                       //send wav 2
		if ( param_position > last_param_position ) {
			if ( param_level < 0.99 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level += 0.001;
					mixer10.gain(1, param_level);
					delay(1);
			    }
			}
		}
		if ( param_position < last_param_position ) {
			if ( param_level > 0.02 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level -= 0.001;
					mixer10.gain(1, param_level);
					delay(1);
		        }
			}
		}
		Serial.println("modulation send 2");
		Serial.println(param_level);
	}
	if ( param_control == 2 ) {		                       //gain flange
		if ( param_position > last_param_position ) {
			if ( param_level < 0.99 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level += 0.001;
					mixer9.gain(2, param_level);
					delay(1);
			    }
			}
		}
		if ( param_position < last_param_position ) {
			if ( param_level > 0.02 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level -= 0.001;
					mixer9.gain(2, param_level);
					delay(1);
		        }
			}
		}
		Serial.println("flange gain");
		Serial.println(param_level);
	}
	if ( param_control == 3 ) {		                       //gain chorus 
		if ( param_position > last_param_position ) {
			if ( param_level < 0.99 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level += 0.001;
					mixer9.gain(3, param_level);
					delay(1);
			    }
			}
		}
		if ( param_position < last_param_position ) {
			if ( param_level > 0.02 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level -= 0.001;
					mixer9.gain(3, param_level);
					delay(1);
		        }
			}
		}
		Serial.println("chorus gain");
		Serial.println(param_level);
	}
	/*
	if ( param_control == 4 ) {		                       //flange offset
		if ( param_position > last_param_position ) {
			if ( param_level < 0.99 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level += 0.001;
					flange1.voices(s_idx, s_depth, s_freq);
					delay(1);
			    }
			}
		}
		if ( param_position < last_param_position ) {
			if ( param_level > 0.02 ) {
				for ( int x = 0; x < 100; x++ ) {
					param_level -= 0.001;
					mixer9.gain(3, param_level);
					delay(1);
		        }
			}
		}
		Serial.println("chorus gain");
		Serial.println(param_level);
	}
	*/
	return *this;
}

Atm_modulation_effect& Atm_modulation_effect::btn1( void ) {
  	return *this;
}

Atm_modulation_effect& Atm_modulation_effect::encoderUp( void ) {
  	return *this;
}

Atm_modulation_effect& Atm_modulation_effect::encoderDown( void ) {
  	return *this;
}

Atm_modulation_effect& Atm_modulation_effect::off( void ) {
  	return *this;
}

Atm_modulation_effect& Atm_modulation_effect::trace( Stream & stream ) {
  	Machine::setTrace( &stream, atm_serial_debug::trace,
      "MODULATION_EFFECT\0EVT_OFF\0EVT_CONTROL\0EVT_ENC_UP\0EVT_ENC_DOWN\0EVT_BTN_1\0ELSE\0OFF\0CONTROL\0ENC_UP\0ENC_DOWN\0BTN_1" );
  	return *this;
}