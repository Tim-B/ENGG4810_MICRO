/* 
 * File:   FilterHelp.h
 * Author: Tim
 *
 * Created on 4 May 2013, 8:46 PM
 */

#ifndef FILTERHELP_H
#define	FILTERHELP_H

#include "../system/global.h"

typedef enum {
    LPF,
    HPF,
    BPF,
    NOTCH,
} BIQUAD_TYPE;

typedef struct BIQUAD_COEF {
    float forward[3];
    float back[3];
} biquad_coef;

#define SAMPLE_RATE 44100

void biquad_gen(BIQUAD_TYPE type, float* returnVar, int Fc, float Q);

#endif	/* FILTERHELP_H */

