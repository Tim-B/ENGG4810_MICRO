/* 
 * File:   SampleBlock.h
 * Author: Tim
 *
 * Created on 3 May 2013, 9:17 PM
 */

#ifndef SAMPLEBLOCK_H
#define	SAMPLEBLOCK_H

#include "../mpc/../system/global.h"
#include "arm_math.h"

typedef struct EFFECT_DATA {
    effect effect;
    float paramX;
    float paramY;
} effect_data;

typedef struct SAMPLE_BLOCK {
    float32_t data[NUM_BLOCK_SAMPLED];
    float32_t raw[NUM_BLOCK_SAMPLED];
    int cursor;
    effect_data effects[2];
    bool current;
    bool waiting;
} sample_block;

void initSampleBlocks();
void loadBlock(sample_block *block);
float readSample();
void checkSampleBlocks();
int getOutput();

#endif	/* SAMPLEBLOCK_H */

