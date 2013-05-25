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
    block->effects[0].effect = getEffect(1);
    block->effects[1].effect = getEffect(0);
    // block->effects[0].effect = LOW_PASS;
    // block->effects[1].effect = NONE;
    for (int i = 0; i < NUM_BLOCK_SAMPLED; i++) {
        block->data[i] = 0;
        block->raw[i] = 0;
    }
    loadBlock(block);
}

void initSampleBlocks() {
    iirInit();

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
            if (numSamps > 1) {
                break;
            }
        }
    }
    if (numSamps >= 2) {
        arm_add_f32(&buffer[0], &buffer[1], &temp[0], NUM_BLOCK_SAMPLED);
        arm_scale_f32(&temp[0], 0.5f, &block->raw, NUM_BLOCK_SAMPLED);
    } else if (numSamps == 1) {
        arm_copy_f32(&buffer[0], &block->raw, NUM_BLOCK_SAMPLED);
        arm_scale_f32(&block->raw, 0.5f, &block->raw, NUM_BLOCK_SAMPLED);
    } else {
        arm_fill_f32(0.0f, &block->raw, NUM_BLOCK_SAMPLED);
    }
}

void applyEffects(sample_block *block, effect_data* e) {
    switch (e->effect) {
        case LOW_PASS:
            iirApply(LPF, block, e);
            break;
        case HIGH_PASS:
            iirApply(HPF, block, e);
            break;
        case NOTCH_PASS:
            iirApply(NOTCH, block, e);
            break;
        case BAND_PASS:
            iirApply(BPF, block, e);
            break;
        default:
            arm_copy_f32(&block->raw, &block->data, NUM_BLOCK_SAMPLED);
            break;
    }
}

void loadBlock(sample_block *block) {
    scan_keys();
    mixBlock(block);
    readADC(block);
    applyEffects(block, &block->effects[0]);
    arm_copy_f32(&block->data, &block->raw, NUM_BLOCK_SAMPLED);
    applyEffects(block, &block->effects[1]);
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

int getOutput() {
    effect_data *effect;
    float value = readSample();
    value = value * 0xFFF;
    value = value / 2;
    value += 0xFFF / 2;
    int out = (int) value;

    for (int i = 0; i < 2; i++) {
        effect = &playing_block->effects[i];
        if (effect->effect == KO) {
            out = applyKO(out, effect);
        }
        if (effect->effect == BITCRUSH_DECIMATE) {
            out = applyDecimate(out, effect);
        }
        if(effect->effect == DELAY) {
            out = applyDelay(out, effect);
        }
        if(effect->effect == ECHO) {
            out = applyEcho(out, effect);
        }        
    }
    return out;
}

void checkSampleBlocks() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (blocks[i].waiting) {
            loadBlock(&blocks[i]);
        }
    }
}