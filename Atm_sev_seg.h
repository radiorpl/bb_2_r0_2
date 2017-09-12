#pragma once

#include <Automaton.h>

class Atm_sev_seg: public Machine {

 public:
  enum { HOME, OFF, MASTER_VOL, VOL_WAV_1, VOL_WAV_2, TRACK_WAV_1, TRACK_WAV_2, PLAY_WAV_1, PLAY_WAV_2, DELAY, DELAY_SEND_1, DELAY_SEND_2, DELAY_TIME_1, DELAY_TIME_2, DELAY_TIME_3, DELAY_TIME_4, DELAY_FB_1, DELAY_FB_2, DELAY_FB_3, DELAY_FB_4, DELAY_GAIN_1, DELAY_GAIN_2, DELAY_GAIN_3, DELAY_GAIN_4, DELAY_MIX }; // STATES
  
  enum { EVT_HOME, EVT_OFF, EVT_MASTER_VOL, EVT_VOL_WAV_1, EVT_VOL_WAV_2, EVT_TRACK_WAV_1, EVT_TRACK_WAV_2, EVT_PLAY_WAV_1, EVT_PLAY_WAV_2, EVT_DELAY, EVT_DELAY_SEND_1, EVT_DELAY_SEND_2, EVT_DELAY_TIME_1, EVT_DELAY_TIME_2, EVT_DELAY_TIME_3, EVT_DELAY_TIME_4, EVT_DELAY_FB_1, EVT_DELAY_FB_2, EVT_DELAY_FB_3, EVT_DELAY_FB_4, EVT_DELAY_GAIN_1, EVT_DELAY_GAIN_2, EVT_DELAY_GAIN_3, EVT_DELAY_GAIN_4, EVT_DELAY_MIX, ELSE }; // EVENTS
  Atm_sev_seg( void ) : Machine() {};
  Atm_sev_seg& begin( void );
  Atm_sev_seg& trace( Stream & stream );
  Atm_sev_seg& trigger( int event );
  int state( void );
  Atm_sev_seg& write( int digit, int character );
  Atm_sev_seg& writeBlink( int digit, int character );
  Atm_sev_seg& writeLevel( int level );
  Atm_sev_seg& writeLevelBlink( int level );
  

 private:
  enum { ENT_OFF, ENT_HOME, ENT_MASTER_VOL, ENT_VOL_WAV_1, ENT_VOL_WAV_2, ENT_TRACK_WAV_1, ENT_TRACK_WAV_2, ENT_PLAY_WAV_1, ENT_PLAY_WAV_2, ENT_DELAY, ENT_DELAY_SEND_1, ENT_DELAY_SEND_2, ENT_DELAY_TIME_1, ENT_DELAY_TIME_2, ENT_DELAY_TIME_3, ENT_DELAY_TIME_4, ENT_DELAY_FB_1, ENT_DELAY_FB_2, ENT_DELAY_FB_3, ENT_DELAY_FB_4, ENT_DELAY_GAIN_1, ENT_DELAY_GAIN_2, ENT_DELAY_GAIN_3, ENT_DELAY_GAIN_4, ENT_DELAY_MIX }; // ACTIONS
  
  int event( int id ); 
  void action( int id );
  //real pins
  //int digPins[4] = { 9, 10, 11, 12};
  //int segPins[8] = { 2, 14, 7, 8, 6, 20, 21, 5 };
  //serial test pins
  byte digPins[4] = { 0, 1, 2, 3 };   //digit pins
  byte pinCountDig = 4;         //number of digits
  byte command [3] = { 21, 19, 20 }; //21 is first led register with auto increment, so send 21, then 2 btyes for led0-3 and then led4-7 19 is psc1, 20 is pwm1
  int last_level;
  int dig_delay;
  //non-blinking characters
  //               0    1   2  3   4   5   6    7  8    9   10 11   12 13  14  15  16  17  18  19  20  21   22 23  24  25  26  27  28  29  30  31  32  33  34  35  36
  //               0    1   2  3   4   5   6    7  8    9   A  b    c  d    E   F  g   h   i   j   L   m    n  o   p   q   r   s   t   u   y   Z   -    _   ^   .  " "
  byte seg0 [37] { 0,  65, 16, 0,  65, 4,  4,  64, 0,  64, 64, 5,  21, 1,  20, 84, 0,  69, 85, 1,  21, 68, 69, 5,  80, 64, 85, 4,  21, 5,  65, 16, 85, 21, 84, 85, 85 };
  byte seg1 [37] { 80, 85, 68, 69, 65, 65, 64, 85, 64, 65, 64, 64, 68, 68, 64, 64, 65, 64, 84, 84, 80, 84, 68, 68, 64, 65, 68, 65, 64, 84, 65, 68, 69, 85, 85, 21, 85};
  
  //blink
  //                  0    1    2    3    4    5    6    7    8    9    A    b    c    d    E    F    g    h    i   j    L    m    n    o    p    q   r     s   t
  //    																																						-   _  ^  . " "
  byte segBlink0 [37] {255, 125, 223, 255, 125, 247, 247, 127, 255, 127, 127, 245, 213, 253, 215, 87,  255, 117, 85, 253, 213, 119, 117, 245, 95,  127, 85,  247, 213, 245, 125, 223, 85,  213, 87, 85,  85 };
  byte segBlink1 [37] {95,  85,  119, 117, 125, 125, 127, 85,  127, 125, 127, 127, 119, 119, 127, 127, 125, 127, 87, 87,  95,  87,  119, 119, 127, 125, 119, 125, 127, 87,  125, 119, 117, 85,  85, 213, 85 };


};
