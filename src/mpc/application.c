#include "global.h"
#include "application.h"

void setup() {
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    FPULazyStackingEnable();
    FPUEnable();

    uart_setup();
    
    sd_init();
    dac_setup();
    keycontrol_setup();
    tick_setup();
    soundoutcontrol_setup();
    
    IntMasterEnable();
            
    DEBUG_PRINT("Setup complete\n", NULL);
}

void loop() {
    checkDebounce();
    checkSampleState();
}
