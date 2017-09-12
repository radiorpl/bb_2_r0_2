#pragma once
/*
header file for function to play wav in loop
button stops or starts
7/15/17
loop function works by putting playCheck in ON_LOOP event 
added button skips tracks
added play function has input filename
7/19/17
added instances, this version with 2 instances
looping works
8/1/17
total rewrite, branch
8/29/17
*/


#include <Automaton.h>
class Atm_wav_1 : public Machine {
	public:
		enum { WAV_OFF, WAV_ON, ENC_UP, ENC_DOWN, BTN_1, BTN_2 }; //STATES
		enum { EVT_WAV_OFF, EVT_WAV_ON, EVT_ENC_UP, EVT_ENC_DOWN, EVT_BTN_1, EVT_BTN_2, ELSE }; //EVENTS
		
		Atm_wav_1( void ) : Machine(){};
		Atm_wav_1& begin( int instance );
		Atm_wav_1& play( void );   
		Atm_wav_1& stop( void );
		Atm_wav_1& encoderUp( void );
		Atm_wav_1& encoderDown( void );
		Atm_wav_1& btn1( void );
		Atm_wav_1& btn2( void );
		Atm_wav_1& trace( Stream& stream );
		Atm_wav_1& onPress( Machine& machine, int event = 0 );
		Atm_wav_1& onPress( atm_cb_push_t callback, int idx = 0 ); 
		Atm_wav_1& trigger( int event );
		int state( void );
		
		
	private:
     	enum { ENT_WAV_OFF, ENT_WAV_ON, ENT_ENC_UP, ENT_ENC_DOWN, ENT_BTN_1, ENT_BTN_2 }; // ACTIONS
     	enum { ON_PRESS, CONN_MAX }; // CONNECTORS
     	atm_connector connectors[CONN_MAX];
		int player_instance;
		int display_delay;
     	int event( int id ); 
     	void action( int id );
		int last_track_1_level;
		int last_track_2_level;
	
};