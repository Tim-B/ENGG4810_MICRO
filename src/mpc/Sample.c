#include "global.h"

void check_waiting(mpc_sample *sample) {
    if(sample->waiting) {
        load_next_sample(sample);
    }
}

void setup_sample(mpc_sample *sample, char* wavname) {
    mpc_sample_open(sample, wavname);
    sample->waiting = true;
    load_next_sample(sample);
}

short read_sample(mpc_sample *sample) {
    short temp = 0;
    temp = sample->next_sample.left;
    // temp = temp >> 4;
    sample->waiting = true;
    return temp;
}

void load_next_sample(mpc_sample *sample) {
    mpc_sample_load_next(sample);
    sample->waiting = false;
}