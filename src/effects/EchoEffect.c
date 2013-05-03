#include "../mpc/global.h"
#include "EchoEffect.h"

#define NUM_BACK 8

int past[NUM_BACK] = {0};

int applyEcho(int sample, float feed, int time) {
    int x = 0;
    
    for(int i = NUM_BACK - 1; i > 0; i--) {
        if(i == time) {
            x = past[i];
        }
        past[i] = past[i - 1];
    }
    past[0] = sample;
    float val = feed * x;
    return sample + val;
    // return sample;
}
