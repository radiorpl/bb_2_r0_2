#pragma once
#include "Atm_sev_seg.h"
#include "Atm_delay_effect.h"
#include "Atm_modulation_effect.h"
//display and timers
extern Atm_sev_seg displayMain;
extern Atm_timer paramTimer;
extern Atm_timer delayTimer;
extern Atm_delay_effect delaySend1;
extern Atm_delay_effect delaySend2;	 
extern Atm_delay_effect delayTime1; 
extern Atm_delay_effect delayFb1;
extern Atm_delay_effect delayMix;
extern Atm_modulation_effect modSend1; 
extern Atm_modulation_effect modSend2; 
extern Atm_modulation_effect flangeGain; 
extern Atm_modulation_effect chorusGain;