#pragma once

#include <Automaton.h>

class Atm_enc_button: public Machine {

 public:
  enum { IDLE, COUNT_UP, COUNT_DOWN }; // STATES
  enum { EVT_BTN_1, EVT_ENC_UP, EVT_ENC_DOWN, ELSE }; // EVENTS
  Atm_enc_button( void ) : Machine() {};
  Atm_enc_button& begin( int encButton );
  Atm_enc_button& trace( Stream & stream );
  Atm_enc_button& trigger( int event );
  Atm_enc_button& countUp( void );
  Atm_enc_button& countDown( void );
  int state( void );
  Atm_enc_button& btn_1( void );

  
 private:
  enum { ENT_COUNT_UP, ENT_COUNT_DOWN }; // ACTIONS
  int event( int id ); 
  void action( int id ); 
  int encBtn;
};


