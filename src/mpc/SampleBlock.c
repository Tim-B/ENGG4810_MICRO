#include "../mpc/../system/global.h"
#include "SampleBlock.h"

#define NUM_BLOCKS 2

sample_block blocks[NUM_BLOCKS];
sample_block *playing_block;
short currentBlock = 0;
float buffer[2][NUM_BLOCK_SAMPLED];
float temp[NUM_BLOCK_SAMPLED];

void initBlock(sample_block *block) {
    block->current = false;
    block->cursor = 0;
    block->waiting = true;
    for (int i = 0; i < NUM_BLOCK_SAMPLED; i++) {
        block->data[i] = 0;
        block->raw[i] = 0;
    }
    loadBlock(block);
}

void initSampleBlocks() {
    lowPassInit();

    initBlock(&blocks[0]);
    initBlock(&blocks[1]);
    blocks[0].current = true;
    playing_block = &blocks[0];

    DEBUG_PRINT("Sample block initialized\n", NULL);
}

void mixBlock(sample_block *block) {
    mpc_sample *sample;
    int numSamps = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sample = &samples[i];
        if (sample->playing == true) {
            mpc_sample_load_next(sample, &buffer[numSamps]);
            numSamps++;
            if(numSamps > 1) {
                break;
            }
        }
    }
    if(numSamps >= 2) {
        arm_add_f32(&buffer[0], &buffer[1], &temp[0], NUM_BLOCK_SAMPLED);
        arm_scale_f32(&temp[0], 0.5f, &block->raw, NUM_BLOCK_SAMPLED);
    } else if(numSamps == 1) {
        arm_scale_f32(&buffer[0], 1.0f, &block->raw, NUM_BLOCK_SAMPLED);
    } else {
        arm_scale_f32(&buffer[0], 0.0f, &block->raw, NUM_BLOCK_SAMPLED);
    }
    
}

void loadBlock(sample_block *block) {
    mpc_sample *sample;
    scan_keys();
    mixBlock(block);
    lowPassApply(block);
    block->waiting = false;
    block->cursor = 0;
}

void swapBlocks() {
    playing_block->current = false;
    playing_block->waiting = true;
    if (currentBlock == 0) {
        playing_block = &blocks[1];
        currentBlock = 1;
    } else {
        playing_block = &blocks[0];
        currentBlock = 0;
    }
}

float readSample() {
    if (playing_block->waiting == true) {
        // DEBUG_PRINT("Oh Shiiii\n", NULL);
    }
    int index = ++playing_block->cursor;
    if (index >= NUM_BLOCK_SAMPLED) {
        swapBlocks();
        index = 0;
    }
    return playing_block->data[index];
}

void checkSampleBlocks() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (blocks[i].waiting) {
            loadBlock(&blocks[i]);
        }
    }
}