/* 
 * File:   Sample.h
 * Author: Tim
 *
 * Created on 31 March 2013, 3:48 PM
 */

#ifndef SAMPLE_H
#define	SAMPLE_H
#include "global.h"

typedef struct MPC_SAMPLE {
    wave_header header;
    float next_block[NUM_BLOCK_SAMPLED];
    bool playing;
    FIL file;
    UINT read_bytes;
    bool in_use;
    char* fileName;
    bool needs_reset;
} mpc_sample;

void setup_sample(mpc_sample *sample);
void check_reset_sample(mpc_sample *sample);

#endif	/* SAMPLE_H */

