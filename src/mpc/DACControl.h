/* 
 * File:   DACControl.h
 * Author: Tim
 *
 * Created on 30 March 2013, 3:03 PM
 */

#ifndef DACCONTROL_H
#define	DACCONTROL_H

void dac_setup();
void dac_put();
void queue_sample(float value);

#endif	/* DACCONTROL_H */

