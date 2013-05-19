
#include "../system/global.h"

int applyKO(int input, effect_data* e) {
    float temp = 0;
    int effectVal = 0;
    temp = e->paramX * 4096.0f;
    effectVal = (int) temp;
    input = input & effectVal;
    temp = e->paramY * 4096.0f;
    effectVal = (int) temp;
    input = input ^ effectVal;
    return input;
}
