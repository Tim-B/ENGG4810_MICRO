#include "global.h"


void setup_sample(mpc_sample *sample) {
    mpc_sample_open(sample);
    sample->needs_reset = false;
}

void check_reset_sample(mpc_sample *sample) {
    if(sample->needs_reset == true) {
        mpc_sample_reset(sample);
        sample->needs_reset = false;
    }
}