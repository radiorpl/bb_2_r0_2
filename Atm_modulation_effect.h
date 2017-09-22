#pragma once

#include <Automaton.h>
#include <Audio.h>
class Atm_modulation_effect: public Machine {

 public:
  enum { OFF, CONTROL, ENC_UP, ENC_DOWN, BTN_1 }; // STATES
  enum { EVT_OFF, EVT_CONTROL, EVT_ENC_UP, EVT_ENC_DOWN, EVT_BTN_1, ELSE }; // EVENTS
  Atm_modulation_effect( void ) : Machine(){};
  Atm_modulation_effect& begin( int param_con );
  Atm_modulation_effect& trace( Stream & stream );
  Atm_modulation_effect& trigger( int event );
  Atm_modulation_effect& setLevel( void );
  Atm_modulation_effect& off( void );
  Atm_modulation_effect& btn1( void );
  Atm_modulation_effect& encoderUp( void );
  Atm_modulation_effect& encoderDown( void );  
  int state( void );
 
 private:
  enum { ENT_OFF, ENT_CONTROL, ENT_ENC_UP, ENT_ENC_DOWN, ENT_BTN_1 }; // ACTIONS
  int event( int id ); 
  void action( int id );
  int param_control;
  int param_position;
  int last_param_position;
  int effect_state;
  int display_delay;
  float param_level;
  float last_param_level;
  
  //from flange and chorus examples
// Allocate the delay lines for left and right channels
// Number of samples in each delay line
#define FLANGE_DELAY_LENGTH (6*AUDIO_BLOCK_SAMPLES)
#define CHORUS_DELAY_LENGTH (16*AUDIO_BLOCK_SAMPLES)
short fl_delayline[FLANGE_DELAY_LENGTH];
short ch_delayline[CHORUS_DELAY_LENGTH];

int s_idx;
int s_depth;
float s_freq;
int n_chorus;
  
 
  int speed_array [13]{
  	 0, 27, 35, 54, 71, 80, 107, 143, 160, 214, 286, 321, 425
  };
  
};