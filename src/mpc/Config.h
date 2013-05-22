/* 
 * File:   Config.h
 * Author: Tim
 *
 * Created on 19 May 2013, 2:32 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include "../system/global.h"

typedef struct CONFIG {
    unsigned char sampleData[NUM_SAMPLES];
    unsigned char tempo;
    unsigned char effects[2];
    unsigned char lfo;
} config;

config configData;

void initConfig();
void setSampleProperties(int index, mpc_sample *sample);
effect getEffect(int index);
bool lfoOn();

#endif	/* CONFIG_H */

