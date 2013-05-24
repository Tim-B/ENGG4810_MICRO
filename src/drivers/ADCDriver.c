#include "../mpc/../system/global.h"
#include "driverlib/adc.h"
#define ADC_SEQUENCER_LENGTH 1

int nextCheck = 0;
int stepCnt = 0;
float stepInt = (2 * M_PI) / (44100 / 512);

void setupADC() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    DEBUG_PRINT("ADC initialized\n", NULL);
    ADCSequenceDisable(ADC0_BASE, 3);
    ADCSequenceDisable(ADC0_BASE, 1);
    DEBUG_PRINT("ADC initialized\n", NULL);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1);
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_CH9 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);
    ADCIntClear(ADC0_BASE, 1);
    DEBUG_PRINT("ADC initialized\n", NULL);
}

float scale(int val) {
    float fVal = (float) val;
    float outval = val / 4096.0f;
    if(outval > 1) {
        return 1;
    }
    if(outval < 0) {
        return 0;
    }
    return outval;
}

void readADC(sample_block *block) {
    unsigned long ulADC0_Value[4];
    ADCProcessorTrigger(ADC0_BASE, 1);
    while (!ADCIntStatus(ADC0_BASE, 1, false)) {
    }
    ADCIntClear(ADC0_BASE, 1);
    ADCSequenceDataGet(ADC0_BASE, 1, ulADC0_Value);
    
    float lfoVal = scale(ulADC0_Value[0]);
    // block->effects[0].paramX = lfoVal;  
    if(lfoOn()) {
        int lfoFreq = (2 * lfoVal) + 0.5;
        float sinIn = stepInt * stepCnt * lfoFreq ;
       block->effects[0].paramX = (0.45 * arm_sin_f32(sinIn)) + 0.45; 
    } else {
       block->effects[0].paramX = lfoVal;  
    }
    
    if(block->effects[0].paramX > 1 || block->effects[0].paramX < 0) {
        DEBUG_PRINT("Huuuu\n", NULL);
    }

    block->effects[0].paramY = scale(ulADC0_Value[1]);
    block->effects[1].paramX = scale(ulADC0_Value[2]);
    block->effects[1].paramY = scale(ulADC0_Value[3]);
    stepCnt++;
    // DEBUG_PRINT("ADC %i %i %i %i\n", ulADC0_Value[0], ulADC0_Value[1], ulADC0_Value[2], ulADC0_Value[3]);
}
