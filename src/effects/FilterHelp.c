#include "FilterHelp.h"
#include <arm_math.h>

/**
 * I have no idea what this does.
 * See: http://musicweb.ucsd.edu/~tre/biquad.pdf
 * See: biquad_gen.m
 * 
 * @param type The filter type, either LPF, HPF, BPF or NOTCH
 * @param Fc The cutoff frequency in Hz
 * @param Q something which is a float
 * @return a biquad_coef struct
 */

void biquad_gen(BIQUAD_TYPE type, float* returnVar, int Fc, float Q) {

    biquad_coef data;

    float w0 = 2 * M_PI * Fc / SAMPLE_RATE;

    float c1 = cosf(w0);
    float alpha = sinf(w0) / (2 * Q);

    float b0, b1, b2, a0, a1, a2;

    switch (type) {
        case LPF:
            b0 = (1 - c1) / 2;
            b1 = 1 - c1;
            b2 = (1 - c1) / 2;
            a0 = 1 + alpha;
            a1 = -2 * c1;
            a2 = 1 - alpha;
            break;
        case HPF:
            b0 = (1 + c1) / 2;
            b1 = -1 - c1;
            b2 = (1 + c1) / 2;
            a0 = 1 + alpha;
            a1 = -2 * c1;
            a2 = 1 - alpha;
            break;
        case BPF:
            b0 = alpha;
            b1 = 0;
            b2 = -alpha;
            a0 = 1 + alpha;
            a1 = -2 * c1;
            a2 = 1 - alpha;
            break;
        case NOTCH:
            b0 = 1;
            b1 = -2 * c1;
            b2 = 1;
            a0 = 1 + alpha;
            a1 = -2 * c1;
            a2 = 1 - alpha;
            break;
    }

    returnVar[0] = b0 / a0;
    returnVar[1] = b1 / a0;
    returnVar[2] = b2 / a0;

    returnVar[3] = -1 * (a1 / a0);
    returnVar[4] = -1 * (a2 / a0);

}
