#include "../mpc/global.h"
#include "SampleBlock.h"

#define NUM_BLOCKS 2

sample_block blocks[NUM_BLOCKS];
sample_block *playing_block;
short currentBlock = 0;

void initBlock(sample_block *block) {
    block->current = false;
    block->cursor = 0;
    block->waiting = true;
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
    float val = 0;
    for (int i = 0; i < NUM_BLOCK_SAMPLED; i++) {
        val = 0;
        numSamps = 0;
        for (int j = 0; j < NUM_SAMPLES; j++) {
            sample = getSampleByIndex(j);
            if (sample->playing == true) {
                val += sample->next_block[i];
                numSamps++;
            }
        }
        block->raw[i] = val / numSamps;
    }
}

void loadBlock(sample_block *block) {
    mpc_sample *sample;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sample = getSampleByIndex(i);
        if (sample->playing == true) {
            mpc_sample_load_next(sample);
        }
    }
    mixBlock(block);
    lowPassApply(block);
    block->waiting = false;
    block->cursor = 0;
}

void swapBlocks() {
    playing_block->current = false;
    playing_block->waiting = true;
    if(currentBlock == 0) {
        playing_block = &blocks[1];
        currentBlock = 1;
    } else {
        playing_block = &blocks[0];
        currentBlock = 0;
    }
}

float readSample() {
    int index = ++playing_block->cursor;
    if(index >= NUM_BLOCK_SAMPLED) {
        swapBlocks();
        index = 0;
    }
    return playing_block->data[index];
}

void checkSampleBlocks() {
    for(int i = 0; i < NUM_BLOCKS; i++) {
        if(blocks[i].waiting) {
            loadBlock(&blocks[i]);
        }
    }
}