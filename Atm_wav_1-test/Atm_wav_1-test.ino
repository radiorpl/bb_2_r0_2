#include <Atm_wav_1.h>
#include <Atm_master_vol.h>
#include <Atm_enc_button.h> 
#include <button_counters.h> 
#include <Atm_sev_seg.h>
#include <Atm_delay_effect.h>
#include <Automaton.h>
#include "display_def.h"
#include "button_counters.h"
#include "audio_system.h"


#define SDCARD_CS_PIN    10      // Use these with the Teensy Audio Shield
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

Atm_wav_1 wav1, wav2;                               //declare atm machines
Atm_master_vol volMaster, volWav1, volWav2;
Atm_encoder enc1, enc2, enc3;
Atm_button btn1, btn2, btn3;
Atm_enc_button encBtn1, encBtn2, encBtn3;
Atm_sev_seg displayMain;
Atm_timer delayTimer, paramTimer;

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
   volMaster.begin(0);
   volWav1.begin(1);
   volWav2.begin(2);
   enc1.begin(33, 24);
   enc1.debounce(300);
   enc2.begin(26, 25);
   enc3.begin(27, 28);
   enc3.debounce(30);    //if debounce too fast, trouble reading encoder
   btn1.begin(4);
   btn2.begin(5);
   btn3.begin(8);
   encBtn1.begin(1);
   encBtn2.begin(2);
   encBtn3.begin(3);
   displayMain.begin();
   delayTimer.begin(100);
   paramTimer.begin(3000);
   paramTimer.onFinish( displayMain, displayMain.EVT_HOME );	 
   sgtl5000_1.enable();
   sgtl5000_1.volume(0.3);	   
   wav1.trace(Serial);
   wav2.trace(Serial); 
   encBtn2.trace(Serial); 
   volMaster.trace(Serial);  
}

//===================================================
void loop() {
	if ( paramTimer.state() == 0) {
		if ( enc_button_counter_1 == 0 ) {
			btn1.onPress ( paramTimer, paramTimer.EVT_START );
			btn1.onPress ( 1, displayMain, displayMain.EVT_PLAY_WAV_1 );
			//enc1.onChange ( displayMain, displayMain.EVT_PLAY_WAV_1 );
		}
		else if ( enc_button_counter_1 == 1 ) {
			btn1.onPress ( paramTimer, paramTimer.EVT_START );
			btn1.onPress ( 1, displayMain, displayMain.EVT_PLAY_WAV_2 );
			//enc1.onChange ( displayMain, displayMain.EVT_PLAY_WAV_1 );
		}
	}
	else {
		enc1.onChange( ATM_UP, encBtn1, encBtn1.EVT_ENC_UP );     //=========encoder and btn 1 control start stop different wavs
		enc1.onChange( ATM_DOWN, encBtn1, encBtn1.EVT_ENC_DOWN ); //on this one encoders change count and btn does action
		if ( enc_button_counter_1 == 0 ) {
		  btn1.onPress( wav1, wav1.EVT_BTN_1 );
		  if ( enc_button_counter_1 != last_enc_button_counter_1 ){
		  	displayMain.trigger( displayMain.EVT_PLAY_WAV_1 );
			paramTimer.trigger( paramTimer.EVT_START );
		  }
		last_enc_button_counter_1 = enc_button_counter_1;  
		}
		else if ( enc_button_counter_1	 == 1 ) {
		  btn1.onPress( wav2, wav2.EVT_BTN_1 );
		  if ( enc_button_counter_1 != last_enc_button_counter_1 ){
		  	displayMain.trigger( displayMain.EVT_PLAY_WAV_2 );
			paramTimer.trigger( paramTimer.EVT_START );
		  }
		last_enc_button_counter_1 = enc_button_counter_1;  
		}
	}
	
//====================================================	
	if ( paramTimer.state() == 0) {		//====================trigger display for wav players if display is home
		if ( enc_button_counter_2 == 0 ) {
			btn2.onPress ( paramTimer, paramTimer.EVT_START );
			btn2.onPress ( 1, displayMain, displayMain.EVT_TRACK_WAV_1 );
		}
		else if ( enc_button_counter_2 == 1 ) {
			btn2.onPress ( paramTimer, paramTimer.EVT_START );
			btn2.onPress ( 1, displayMain, displayMain.EVT_TRACK_WAV_2 );
		}
	}
	else{
		btn2.onPress( encBtn2, encBtn2.EVT_BTN_1 );   //=============encoder and btn 2 control track selection
		if ( enc_button_counter_2 == 0 ) {             //button does count, encoders do action
			enc2.onChange( ATM_UP, wav1, wav1.EVT_ENC_UP );
			enc2.onChange( ATM_DOWN, wav1, wav1.EVT_ENC_DOWN );
		}
		else if ( enc_button_counter_2	== 1 ) {
			enc2.onChange( ATM_UP, wav2, wav2.EVT_ENC_UP );
			enc2.onChange( ATM_DOWN, wav2, wav2.EVT_ENC_DOWN );
		}
}
//=================================================================	
	if ( paramTimer.state() == 0 ) {
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
	else {
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
	automaton.run();
}