#include "../system/global.h"


void setup_sample(mpc_sample *sample) {
    mpc_sample_open(sample);
    sample->needs_reset = false;
    sample->latch = false;
    sample->loop = false;
    sample->playing = false;
}

void check_reset_sample(mpc_sample *sample) {
    if(sample->needs_reset == true) {
        mpc_sample_reset(sample);
        sample->needs_reset = false;
    }
}

void trigger_sample_event(sample_event event, mpc_sample *sample) {
    mpc_sample *sample2 = getSampleByIndex(2);
    if(event == KEY_ON) {
        sample->playing = true;
        //sample2->playing = true;
        //DEBUG_PRINT("Playing %s\n", sample->fileName);
    }
    
    if(event == KEY_OFF) {
        if(!sample->latch && !sample->loop) {
            if(sample->playing == true) {
                mpc_sample_reset(sample);
            }
            sample->playing = false;
        }
    }
    
    if(event == RESET) {
        if(!sample->latch && !sample->loop) {
            sample->playing = false;
        }
    }
}