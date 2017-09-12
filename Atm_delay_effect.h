#pragma once

#include <Automaton.h>

class Atm_delay_effect: public Machine {

 public:
  enum { OFF, CONTROL, ENC_UP, ENC_DOWN, BTN_1 }; // STATES
  enum { EVT_OFF, EVT_CONTROL, EVT_ENC_UP, EVT_ENC_DOWN, EVT_BTN_1, ELSE }; // EVENTS
  Atm_delay_effect( void ) : Machine(){};
  Atm_delay_effect& begin( int param_con );
  Atm_delay_effect& trace( Stream & stream );
  Atm_delay_effect& trigger( int event );
  Atm_delay_effect& setLevel( void );
  Atm_delay_effect& off( void );
  Atm_delay_effect& btn1( void );
  Atm_delay_effect& encoderUp( void );
  Atm_delay_effect& encoderDown( void );  
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
  int speed_array [13]{
  	 0, 27, 35, 54, 71, 80, 107, 143, 160, 214, 286, 321, 425
  };
  
};
