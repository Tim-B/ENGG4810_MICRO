#include "IIRFilter.h"
#include <arm_math.h>

#define SAM_BLOCK_SIZE 32 
#define NUM_TAPS 27 

uint32_t i;
arm_biquad_casd_df1_inst_f32 S;
arm_status status;
static float32_t state[4];
uint32_t blockSize = SAM_BLOCK_SIZE;
uint32_t numSamples = NUM_BLOCK_SAMPLED;
uint32_t numBlocks = NUM_BLOCK_SAMPLED / SAM_BLOCK_SIZE;
float32_t coeffs[5];

static float32_t LPFstate[4];
static float32_t HPFstate[4];

void iirInit() {
    DEBUG_PRINT("Init start\n", NULL);
    biquad_gen(LPF, coeffs, 10000, 0.3);

    arm_biquad_cascade_df1_init_f32(&S, 1, &coeffs[0], &state);
    DEBUG_PRINT("Init end: %i %i\n", blockSize, numSamples);
}

void limitState() {
    for (int i = 0; i < 4; i++) {
        if (isnan(LPFstate[i])) {
            LPFstate[i] = 0;
        }
        if (isnan(HPFstate[i])) {
            HPFstate[i] = 0;
        }
    }
}

void iirApply(BIQUAD_TYPE type, sample_block *block, effect_data *effect) {
    float freq = 0;
    float q = 0;
    limitState();

    switch (type) {
        case LPF:
            freq = effect->paramX;
            freq = 10000 * freq;
            S.pState = &LPFstate;
            break;
        case HPF:
            freq = effect->paramX;
            freq = 1000 * freq + 20;
            S.pState = &HPFstate;
            break;
        case BPF:
            freq = effect->paramX;
            freq = 10000 * freq;
            break;
        case NOTCH:
            freq = effect->paramX;
            freq = 10000 * freq;
            break;
    }

    q = effect->paramY;
    q = (q * 3) + 0.5;

    biquad_gen(type, S.pCoeffs, freq, q);
    
    for (int i = 0; i < 5; i++) {
        if (isnan(coeffs[i])) {
            coeffs[i] = 0;
        }
    }
    
    arm_biquad_cascade_df1_f32(&S, &block->raw[0], &block->data[0], NUM_BLOCK_SAMPLED);
}
