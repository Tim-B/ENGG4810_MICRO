#include "global.h"
#include "application.h"

void setup() {
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    FPULazyStackingEnable();
    FPUEnable();

    uart_setup();
    soundoutcontrol_setup();
    dac_setup();
    keycontrol_setup();
    tick_setup();
    IntMasterEnable();
    sd_init();
            
    DEBUG_PRINT("Setup complete\n", NULL);
}

void loop() {
    checkDebounce();
}
