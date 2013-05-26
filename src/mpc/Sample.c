#include "../system/global.h"

bool lfoRelease = true;
bool loopRelease = true;

void setup_sample(mpc_sample *sample) {
    mpc_sample_open(sample);
    sample->needs_reset = false;
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
    
    if(event == LOOP_PRESS) {
        if(loopRelease == false) {
            return;
        }
        if(sample->loop) {
            sample->loop = false;
        } else {
            sample->loop = true;
        }
        loopRelease = false;
    }
    
    if(event == KEY_ON) {
        sample->playing = true;
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
        if(!sample->loop) {
            sample->playing = false;
        }
    }
    
    if(event == LFO_PRESS) {
        if(lfoRelease == false) {
            return;
        }
        if(lfoOn()) {
            setLFO(false);
        } else {
            setLFO(true); 
        }
        lfoRelease = false;
    }
    
    if(event == LFO_RELEASE) {
        lfoRelease = true;
    }
    
    if(event == LOOP_RELEASE) {
        loopRelease = true;
    }
    
}