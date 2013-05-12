/* 
 * File:   Sample.h
 * Author: Tim
 *
 * Created on 31 March 2013, 3:48 PM
 */

#ifndef SAMPLE_H
#define	SAMPLE_H
#include "../system/global.h"

typedef struct MPC_SAMPLE {
    wave_header header;
    bool playing;
    bool latch;
    bool loop;
    FIL file;
    UINT read_bytes;
    bool in_use;
    char* fileName;
    bool needs_reset;
} mpc_sample;

typedef enum {
    KEY_ON,
    KEY_OFF,
    RESET,
} sample_event;

void setup_sample(mpc_sample *sample);
void check_reset_sample(mpc_sample *sample);
void trigger_sample_event(sample_event event, mpc_sample *sample);

#endif	/* SAMPLE_H */

