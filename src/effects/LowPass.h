/* 
 * File:   LowPass.h
 * Author: Tim
 *
 * Created on 4 May 2013, 10:29 AM
 */

#ifndef LOWPASS_H
#define	LOWPASS_H

#include "../mpc/../system/global.h"

void lowPassInit();
void lowPassApply(sample_block *block);

#endif	/* LOWPASS_H */

