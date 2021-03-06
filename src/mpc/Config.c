
#include "../system/global.h"

bool lfoVal = false;

void initConfig() {
    read_config(&configData);
    DEBUG_PRINT("Conf value: %i\n", configData.tempo);
}

void setSampleProperties(int index, mpc_sample *sample) {
    char val = configData.sampleData[index];
    if(val & 0x01) {
        sample->in_use = true;
    } else {
        sample->in_use = false;
    }
    if(val & 0x02) {
        sample->latch = true;
        DEBUG_PRINT("Latch: %s\n", sample->fileName);
    } else {
        sample->latch = false;
    }
}

effect getEffect(int index) {
    int val = configData.effects[index];
    switch(val) {
        case 1:
            return LOW_PASS;
        case 2:
            return HIGH_PASS;
        case 3:
            return BAND_PASS;
        case 4:
            return NOTCH_PASS;
        case 5:
            return ECHO;
        case 6:
            return DELAY;
        case 7:
            return BITCRUSH_DECIMATE;
        case 8:
            return KO;
        default:
            return NONE;
    }
    return NONE;
}

bool lfoOn() {
    return lfoVal;
}

void setLFO(bool val) {
    lfoVal = val;
}

int tempo() {
    return configData.tempo;
}