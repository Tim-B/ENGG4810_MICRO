/* 
 * File:   LowPass.h
 * Author: Tim
 *
 * Created on 4 May 2013, 10:29 AM
 */

#ifndef LOWPASS_H
#define	LOWPASS_H

#include "../system/global.h"
#include "FilterHelp.h"

void iirInit();
void iirApply(BIQUAD_TYPE type, sample_block *block, effect_data *effect);

#endif	/* LOWPASS_H */

