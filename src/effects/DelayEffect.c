#include "../system/global.h"

int cnt = 0;
short val;
float interp = 0;

int applyDelay(int input, effect_data* e) {
    float temp = 0;
    int effectVal = 0;
    temp = e->paramX * OUT_BUF_LEN;
    effectVal = (int) temp;
    int out = 0;
    float addVal;
    int dif = cnt % 3;
    if (dif) {
        addVal =  interp * (float) dif;
        // out = val + (int) addVal;
        out = val;
    } else {
        out = pull(&delay_output, effectVal);
        push(&delay_output, input);
        interp = (out - val) / 3.0f;
        val = out;
    }
    temp = e->paramY * (float) out;
    input = input + (int) temp;
    input = input >> 1;
    cnt++;
    return input;
}
