#include "LowPass.h"
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
int blockRunCount = 0;

void lowPassInit() {
    DEBUG_PRINT("Init start\n", NULL);
    biquad_gen(LPF, coeffs, 500, 0.707);

    arm_biquad_cascade_df1_init_f32(&S, 1, &coeffs[0], &state);
    DEBUG_PRINT("Init end: %i %i\n", blockSize, numSamples);
}

void lowPassApply(sample_block *block) {
    blockRunCount++;
    arm_biquad_cascade_df1_f32 (&S, &block->raw[0], &block->data[0], NUM_BLOCK_SAMPLED);
    //block->data = block->raw;
}
