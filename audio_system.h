#pragma once
#include <Audio.h>
/*
//r0-2audio library
AudioControlSGTL5000     sgtl5000_1;     //xy=744,575
AudioPlaySdWav           playSdWav1;     //xy=394,289
AudioPlaySdWav           playSdWav2;     //xy=398,385
AudioMixer4              mixer1;         //xy=594,297
AudioMixer4              mixer2;         //xy=591,395
AudioOutputI2S           i2s1;           //xy=824,334
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord3(playSdWav2, 0, mixer2, 2);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 3);
AudioConnection          patchCord5(mixer2, 0, i2s1, 1);
AudioConnection          patchCord6(mixer1, 0, i2s1, 0);
//AudioControlSGTL5000     sgtl5000_1;     //xy=744,575


//r3 audio library
// GUItool: begin automatically generated code
extern AudioPlaySdWav           playSdWav2;     //xy=88,160
extern AudioPlaySdWav           playSdWav1;     //xy=89,66
extern AudioMixer4              mixer1;         //xy=238,84
extern AudioMixer4              mixer2;         //xy=232,163
extern AudioMixer4              mixer3;         //xy=495,35
extern AudioMixer4              mixer4;         //xy=505,131
extern AudioMixer4              mixer7;         //xy=525,381
extern AudioMixer4              mixer5;         //xy=678,70
extern AudioMixer4              mixer6;         //xy=680,261
extern AudioMixer4              mixer8;         //xy=682,375
extern AudioMixer4              mixer9;         //xy=855,328
extern AudioEffectDelay         delay1;         //xy=309,331
extern AudioOutputI2S           i2s1;           //xy=1023,334
extern AudioControlSGTL5000     sgtl5000_1;     //xy=478,626

// GUItool: end automatically generated code
*/
extern AudioPlaySdWav           playSdWav2;     //xy=88,160
extern AudioPlaySdWav           playSdWav1;     //xy=89,66
extern AudioMixer4              mixer1;         //xy=238,84
extern AudioMixer4              mixer2;         //xy=238,169
extern AudioMixer4              mixer10;        //xy=304,531
extern AudioEffectDelay         delay1;         //xy=309,331
extern AudioMixer4              mixer3;         //xy=495,35
extern AudioMixer4              mixer4;         //xy=505,131
extern AudioEffectChorus        chorus1;        //xy=508,585
extern AudioEffectFlange        flange1;        //xy=514,510
extern AudioMixer4              mixer7;         //xy=525,381
extern AudioMixer4              mixer5;         //xy=678,70
extern AudioMixer4              mixer8;         //xy=750,354
extern AudioMixer4              mixer6;         //xy=753,208
extern AudioMixer4              mixer9;         //xy=888,302
extern AudioMixer4              mixer11;        //xy=1046,240
extern AudioOutputI2S           i2s1;           //xy=1066,296
extern AudioControlSGTL5000     sgtl5000_1;     //xy=1075,409