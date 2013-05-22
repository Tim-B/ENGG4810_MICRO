#include "../system/global.h"

int sampleCount = 0;
int sampleValue = 0;

int applyDecimate(int input, effect_data* e) {
    float temp = 0;
    int effectVal = 0;
    temp = e->paramX * 2048.0f;
    effectVal = (int) temp;
    
    if(effectVal != 0) {
       int round = input % effectVal;
       input = input - round;       
    }


    temp = e->paramY * 32.0f;
    effectVal = (int) temp;

    if(effectVal != 0) {
        if(sampleCount % effectVal == 0) {
            sampleValue = input;
        } else {
            input = sampleValue;
        }
    }
    
    sampleCount++;
    return input;
}


