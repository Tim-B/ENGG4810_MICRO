#include "../system/global.h"

short pull(output_buffer *output, int index) {
    int target = output->start - index;
    if(target < 0) {
        target = target + OUT_BUF_LEN;
    }
    int returnVal = output->data[target];
    
    target = output->start + 1;
    if(target >= OUT_BUF_LEN) {
        target = 0;
    }

    output->start = target;
    return returnVal;
}

void push(output_buffer *output, short val) {
    output->data[output->start] = val;
}