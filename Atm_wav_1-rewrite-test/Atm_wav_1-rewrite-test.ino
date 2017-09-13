#include <Atm_wav_1.h>
#include <Atm_master_vol.h>
#include <Atm_enc_button.h> 
#include <button_counters.h> 
#include <Atm_sev_seg.h>
#include <Atm_delay_effect.h>
#include <Atm_fx_select.h>
#include <Automaton.h>
#include "display_def.h"
#include "button_counters.h"
#include "audio_system.h"



#define SDCARD_CS_PIN    10      // Use these with the Teensy Audio Shield
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

Atm_wav_1 wav1, wav2;                               //declare atm machines
Atm_master_vol volMaster, volWav1, volWav2;
Atm_encoder enc1, enc2, enc3, enc4, enc5;
Atm_button btn1, btn2, btn3, btn4, btn5;
Atm_enc_button encBtn1, encBtn2, encBtn3, encBtn4, encBtn5;
Atm_sev_seg displayMain;
Atm_timer delayTimer, paramTimer;
Atm_delay_effect delaySend1, delaySend2, delayTime1, delayFb1, delayMix;
Atm_fx_select delaySelect;

void setup() {
   Serial.begin( 9600 );
   SPI.setMOSI(SDCARD_MOSI_PIN);
   SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {              //To do: change to start in different mode when sd missing
     while (1) {
		    btn1.onPress( encBtn1, encBtn1.EVT_BTN_1 );
       Serial.println("Unable to access the SD card");   
     }   
   }   
   wav1.begin(1);    //start wav instances
   wav2.begin(2);
   volMaster.begin(0);   //volumes
   volWav1.begin(1);
   volWav2.begin(2);
   delaySend1.begin(0);    //delays
   delaySend2.begin(1);
   delayTime1.begin(2);
   delayFb1.begin(6);
   delayMix.begin(14);
   delaySelect.begin(0);
   enc1.begin(33, 24);      //encoders
   enc1.debounce(100);
   enc2.begin(25, 26);
   enc2.debounce(125);
   enc3.begin(27, 28);
   enc3.debounce(225);    //if debounce too fast, trouble reading encoder
   enc4.begin(29, 30);
   enc5.begin(31, 32);
   enc5.debounce(225);
   btn1.begin(4);
   btn2.begin(5);
   //btn2.debounce(10);
   btn3.begin(8);
   btn4.begin(16);
   btn5.begin(17);
   encBtn1.begin(1);
   encBtn2.begin(2);
   encBtn3.begin(3);
   encBtn4.begin(4);
   encBtn5.begin(5);
   displayMain.begin();
   delayTimer.begin(100);
   paramTimer.begin(3000);
   paramTimer.onFinish( displayMain, displayMain.EVT_HOME );	 
   sgtl5000_1.enable();
   sgtl5000_1.volume(0.5);	   
   delayMix.trace(Serial);
   enc5.trace(Serial);
   //displayMain.trace(Serial); 
   //encBtn2.trace(Serial); 
   //volMaster.trace(Serial);  
}

//===================================================
void loop() {
  	enc1.onChange2( ATM_UP, paramTimer, paramTimer.EVT_START );    
  	enc1.onChange2( ATM_DOWN, paramTimer, paramTimer.EVT_START );
	
	if ( displayMain.state() == displayMain.PLAY_WAV_1 || displayMain.state() == displayMain.PLAY_WAV_2 ) {
	  	enc1.onChange( ATM_UP, encBtn1, encBtn1.EVT_ENC_UP );    
	  	enc1.onChange( ATM_DOWN, encBtn1, encBtn1.EVT_ENC_DOWN );
		if ( enc_button_counter_1 == 0 ) {
		   	btn1.onPress( wav1, wav1.EVT_BTN_2 );
		  	enc1.onChange3( ATM_UP, displayMain, displayMain.EVT_PLAY_WAV_2 );    
		  	enc1.onChange3( ATM_DOWN, displayMain, displayMain.EVT_PLAY_WAV_2 );		
	    }
		else if ( enc_button_counter_1 == 1 ) {
		  	btn1.onPress( wav2, wav2.EVT_BTN_2 );
		  	enc1.onChange3( ATM_UP, displayMain, displayMain.EVT_PLAY_WAV_1 );    
		  	enc1.onChange3( ATM_DOWN, displayMain, displayMain.EVT_PLAY_WAV_1 );	
	    }
	}
	else {
		if ( enc_button_counter_1 == 0 ) {				//on this one encoders change count and btn does action
			btn1.onPress( wav1, wav1.EVT_BTN_2 );
		  	enc1.onChange( ATM_UP, wav1, wav1.EVT_BTN_2 );    
		  	enc1.onChange( ATM_DOWN, wav1, wav1.EVT_BTN_2 ); 
		  	enc1.onChange3( ATM_UP, displayMain, displayMain.EVT_PLAY_WAV_1 );    
		  	enc1.onChange3( ATM_DOWN, displayMain, displayMain.EVT_PLAY_WAV_1 );
		}
		else if ( enc_button_counter_2 == 1 ) {
			btn1.onPress( wav2, wav2.EVT_BTN_2 );
		  	enc1.onChange( ATM_UP, wav2, wav2.EVT_BTN_2 );    
		  	enc1.onChange( ATM_DOWN, wav2, wav2.EVT_BTN_2 );
		  	enc1.onChange3( ATM_UP, displayMain, displayMain.EVT_PLAY_WAV_2 );    
		  	enc1.onChange3( ATM_DOWN, displayMain, displayMain.EVT_PLAY_WAV_2 );
		}
	}
//====================================================	
	
	if ( displayMain.state() == displayMain.TRACK_WAV_1 || displayMain.state() == displayMain.TRACK_WAV_2 ) {  			//track control
		if ( enc_button_counter_2 == 0 ) {
			btn2.onPress( 1, wav1, wav1.EVT_BTN_1 );
			btn2.onPress( encBtn2, encBtn2.EVT_BTN_1 );
		}
		else if ( enc_button_counter_2 == 1 ) {
			btn2.onPress( 1, wav2, wav2.EVT_BTN_1 );
			btn2.onPress( encBtn2, encBtn2.EVT_BTN_1 );
		}	
	}
	else {
		if ( enc_button_counter_2 == 0 ) {
			btn2.onPress( 1, 0, 0 );
			btn2.onPress( wav1, wav1.EVT_BTN_1 );
		}
		else if ( enc_button_counter_2 == 1 ) {
			btn2.onPress( 1, 0, 0 );
			btn2.onPress( wav2, wav2.EVT_BTN_1 );
		}
	}
	if ( enc_button_counter_2 == 0 ) {
		enc2.onChange( ATM_UP, wav1, wav1.EVT_ENC_UP );
		enc2.onChange( ATM_DOWN, wav1, wav1.EVT_ENC_DOWN );
	}
	else if ( enc_button_counter_2 == 1 ) {
		enc2.onChange( ATM_UP, wav2, wav2.EVT_ENC_UP );
		enc2.onChange( ATM_DOWN, wav2, wav2.EVT_ENC_DOWN );
	}
	
//=================================================================	
	if ( (displayMain.state() == displayMain.MASTER_VOL) || (displayMain.state() == displayMain.VOL_WAV_1) || (displayMain.state() == displayMain.VOL_WAV_2) ){
		if ( enc_button_counter_3 == 0 ) {
			btn3.onPress( encBtn3, encBtn3.EVT_BTN_1 );
			btn3.onPress( 1, volMaster, volMaster.EVT_BTN_1 );		
		}
		else if ( enc_button_counter_3 == 1 ) {
			btn3.onPress( encBtn3, encBtn3.EVT_BTN_1 );
			btn3.onPress( 1, volWav1, volWav1.EVT_BTN_1 );		//===============encoder and btn 3 control volumes
		}
		else if ( enc_button_counter_3 == 2 ) {
			btn3.onPress( encBtn3, encBtn3.EVT_BTN_1 );
			btn3.onPress( 1, volWav2, volWav2.EVT_BTN_1 );
		}
	}
	else {
		if ( enc_button_counter_3 == 0 ) {
		btn3.onPress( volMaster, volMaster.EVT_BTN_1 );		//===============encoder and btn 3 control volumes
		}
		else if ( enc_button_counter_3 == 1 ) {
		btn3.onPress( volWav1, volWav1.EVT_BTN_1 );		//===============encoder and btn 3 control volumes
		}
		else if ( enc_button_counter_3 == 2 ) {
		btn3.onPress( volWav2, volWav2.EVT_BTN_1 );		//===============encoder and btn 3 control volumes
		}
	}
	if ( enc_button_counter_3 == 0 ) {
	  	enc3.onChange( ATM_UP, volMaster, volMaster.EVT_ENC_UP );
	  	enc3.onChange( ATM_DOWN, volMaster, volMaster.EVT_ENC_DOWN );
	}
	else if ( enc_button_counter_3 == 1 ) {
	  	enc3.onChange( ATM_UP, volWav1, volWav1.EVT_ENC_UP );
	  	enc3.onChange( ATM_DOWN, volWav1, volWav1.EVT_ENC_DOWN );
	}
	else if ( enc_button_counter_3 == 2 ) {
	  	enc3.onChange( ATM_UP, volWav2, volWav2.EVT_ENC_UP );
	  	enc3.onChange( ATM_DOWN, volWav2, volWav2.EVT_ENC_DOWN );
	}
//====================================================================
	//button 4 - effect selection
	 if ( (displayMain.state() == displayMain.DELAY) ) {
		 if ( enc_button_counter_5 == 0 ) {
			 btn4.onPress( delaySelect, delaySelect.EVT_BTN_1 );
		 } 
	 }
	 else {
		 if ( enc_button_counter_5 == 0 ) {
			 btn4.onPress( delaySelect, delaySelect.EVT_BTN_1 );
		 } 
	 }
//====================================================================	
	//encoder/button 5 - delay
	if ( (displayMain.state() == displayMain.DELAY_SEND_1) || (displayMain.state() == displayMain.DELAY_SEND_2) || (displayMain.state() == displayMain.DELAY_TIME_1) || (displayMain.state() == displayMain.DELAY_FB_1) || (displayMain.state() == displayMain.DELAY_MIX) ) {
		if ( enc_button_counter_5 == 0 ) {
			btn5.onPress( encBtn5, encBtn5.EVT_BTN_1 );
			btn5.onPress( 1, delaySend1, delaySend1.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 1 ) {
			btn5.onPress( encBtn5, encBtn5.EVT_BTN_1 );
			btn5.onPress( 1, delaySend2, delaySend2.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 2 ) {
			btn5.onPress( encBtn5, encBtn5.EVT_BTN_1 );
			btn5.onPress( 1, delayTime1, delayTime1.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 3 ) {
			btn5.onPress( encBtn5, encBtn5.EVT_BTN_1 );
			btn5.onPress( 1, delayFb1, delayFb1.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 4 ) {
			btn5.onPress( encBtn5, encBtn5.EVT_BTN_1 );
			btn5.onPress( 1, delayMix, delayMix.EVT_BTN_1 );
		}
	}
	else {
		if ( enc_button_counter_5 == 0 ) {
			btn5.onPress( delaySend1, delaySend1.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 1 ) {
			btn5.onPress( delaySend2, delaySend2.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 2 ) {
			btn5.onPress( delayTime1, delayTime1.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 3 ) {
			btn5.onPress( delayFb1, delayFb1.EVT_BTN_1 );
		}
		else if ( enc_button_counter_5 == 4 ) {
			btn5.onPress( delayMix, delayMix.EVT_BTN_1 );
		}
	}
	
	if ( enc_button_counter_5 == 0) {
		enc5.onChange( ATM_UP, delaySend1, delaySend1.EVT_ENC_UP );
		enc5.onChange( ATM_DOWN, delaySend1, delaySend1.EVT_ENC_DOWN );
	}
	else if ( enc_button_counter_5 == 1) {
		enc5.onChange( ATM_UP, delaySend2, delaySend2.EVT_ENC_UP );
		enc5.onChange( ATM_DOWN, delaySend2, delaySend2.EVT_ENC_DOWN );
	}
	else if ( enc_button_counter_5 == 2) {
		enc5.onChange( ATM_UP, delayTime1, delayTime1.EVT_ENC_UP );
		enc5.onChange( ATM_DOWN, delayTime1, delayTime1.EVT_ENC_DOWN );
	}
	else if ( enc_button_counter_5 == 3) {
		enc5.onChange( ATM_UP, delayFb1, delayFb1.EVT_ENC_UP );
		enc5.onChange( ATM_DOWN, delayFb1, delayFb1.EVT_ENC_DOWN );
	}
	else if ( enc_button_counter_5 == 4) {
		enc5.onChange( ATM_UP, delayMix, delayMix.EVT_ENC_UP );
		enc5.onChange( ATM_DOWN, delayMix, delayMix.EVT_ENC_DOWN );
	}
	
//==============================================================
	automaton.run();
}