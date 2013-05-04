#include "LowPass.h"
#include <arm_math.h>

#define BLOCK_SIZE 32 
#define NUM_TAPS 27 

uint32_t i;
arm_biquad_casd_df1_inst_f32 S;
arm_status status;
float32_t state[4];
uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = NUM_BLOCK_SAMPLED / BLOCK_SIZE;
float32_t coeffs[5];

void lowPassInit() {
    DEBUG_PRINT("Init start\n", NULL);
    biquad_gen(LPF, coeffs, 2000, 0.707);

    arm_biquad_cascade_df1_init_f32(&S, 1, (float32_t *) coeffs, &state);
    DEBUG_PRINT("Init end\n", NULL);
}

void lowPassApply(sample_block *block) {
    arm_biquad_cascade_df1_f32 (&S, (float32_t *) &block->data, (float32_t *) &block->data, NUM_BLOCK_SAMPLED);
}
