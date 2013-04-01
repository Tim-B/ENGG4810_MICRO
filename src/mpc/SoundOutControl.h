/* 
 * File:   SoundOutControl.h
 * Author: Tim
 *
 * Created on 30 March 2013, 2:47 PM
 */

#ifndef SOUNDOUTCONTROL_H
#define	SOUNDOUTCONTROL_H

#define NUM_SAMPLES 12

void soundoutcontrol_setup();
void soundoutTimerHanlder(void);
void checkSampleState(void);

mpc_sample samples[NUM_SAMPLES];

#endif	/* SOUNDOUTCONTROL_H */

