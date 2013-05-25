#include "../system/global.h"
#include "application.h"
#include "driverlib/rom.h"

void setup() {
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    ROM_FPULazyStackingEnable();
    ROM_FPUEnable();

    uart_setup();

    sd_init();
    dac_setup();
    keycontrol_setup();
    initConfig();
    tick_setup();    
    soundoutcontrol_setup();
    setupADC();
    setupUSBStore();
    initSampleBlocks();
    
    
    ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    ROM_IntMasterEnable();

    DEBUG_PRINT("Setup complete\n", NULL);
}

void loop() {
    //checkDebounce();
    checkSampleBlocks();
    //usbTask();
}

#ifdef DEBUG

void __error__(char *pcFilename, unsigned long ulLine) {
    DEBUG_PRINT("Error %s %i\n", pcFilename, ulLine);
}
#endif
