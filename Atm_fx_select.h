#pragma once

#include <Automaton.h>

class Atm_fx_select : public Machine {

 public:
  enum { CONTROL, ENC_UP, ENC_DOWN, BTN_1 }; // STATES
  enum { EVT_CONTROL, EVT_ENC_UP, EVT_ENC_DOWN, EVT_BTN_1, ELSE }; // EVENTS
  Atm_fx_select( void ) : Machine(){};
  Atm_fx_select& begin( int fx_con );
  Atm_fx_select& trace( Stream & stream );
  Atm_fx_select& trigger( int event );
  Atm_fx_select& onPress( Machine& machine, int event = 0 );
  Atm_fx_select& onPress( atm_cb_push_t callback, int idx = 0 );
  Atm_fx_select& control( void );
  Atm_fx_select& btn1( void );
  Atm_fx_select& encoderUp( void );
  Atm_fx_select& encoderDown( void );  
  int state( void ); 
 
 private:
  enum { ENT_CONTROL, ENT_ENC_UP, ENT_ENC_DOWN, ENT_BTN_1 }; // ACTIONS
  enum { ON_PRESS, CONN_MAX }; // CONNECTORS
  atm_connector connectors[CONN_MAX];
  int event( int id ); 
  void action( int id );
  int fx_control;
  int fx_position;
  int display_delay;
};