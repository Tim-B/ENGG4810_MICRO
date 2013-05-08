/* 
 * File:   SoundOutControl.h
 * Author: Tim
 *
 * Created on 30 March 2013, 2:47 PM
 */

#ifndef SOUNDOUTCONTROL_H
#define	SOUNDOUTCONTROL_H
#include "global.h"
#define NUM_SAMPLES 12

void soundoutcontrol_setup();
void soundoutTimerHanlder(void);
void checkSampleState(void);
void setVol(int newvol);
void mix();
mpc_sample* getSampleByIndex(int i);

mpc_sample samples[NUM_SAMPLES];

#endif	/* SOUNDOUTCONTROL_H */

