#include "../mpc/../system/global.h"
#include "driverlib/adc.h"
#define ADC_SEQUENCER_LENGTH 1

int nextCheck = 0;

void setupADC() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
    DEBUG_PRINT("ADC initialized\n", NULL);
}

char readADC() {
    unsigned long ulADC0_Value[1];
    int outval = 0;
    ADCProcessorTrigger(ADC0_BASE, 3);
    while (!ADCIntStatus(ADC0_BASE, 3, false)) {
    }
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, ulADC0_Value);
    outval = ulADC0_Value[0] / 32;
    if(outval > 128) {
        return 128;
    }
    if(outval < 0) {
        return 0;
    }
    // DEBUG_PRINT("ADC val: %i\n", outval);
    return outval;
}
