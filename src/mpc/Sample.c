#include "global.h"

void check_waiting(mpc_sample *sample) {
    if(sample->waiting) {
        load_next_sample(sample);
    }
}

void setup_sample(mpc_sample *sample) {
    mpc_sample_open(sample);
    sample->waiting = true;
    load_next_sample(sample);
    sample->needs_reset = false;
}

float read_sample(mpc_sample *sample) {
    sample->waiting = true;
    return sample->next_sample.left;
}


void load_next_sample(mpc_sample *sample) {
    mpc_sample_load_next(sample);
    sample->waiting = false;
}

void check_reset_sample(mpc_sample *sample) {
    if(sample->needs_reset == true) {
        mpc_sample_reset(sample);
        sample->needs_reset = false;
    }
}