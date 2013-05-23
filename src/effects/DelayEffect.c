#include "../system/global.h"

int applyDelay(int input, effect_data* e) {
    float temp = 0;
    int effectVal = 0;
    temp = e->paramX * OUT_BUF_LEN;
    effectVal = (int) temp;
    int out = pull(&delay_output, effectVal);
    push(&delay_output, input);
    temp = e->paramY * (float) out;
    input = input + (int) temp;
    input = input >> 1;
    return input;
}
