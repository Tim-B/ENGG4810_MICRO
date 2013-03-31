#include "global.h"
#include "SoundOutControl.h"

int cnt = 0;

void soundoutcontrol_setup() {
    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
            SYSCTL_XTAL_16MHZ);

    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
    // Configure the two 32-bit periodic timers.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    //TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / ((1024 * 42)));
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

    // TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / (1024 * 20));

    //
    // Setup the interrupts for the timer timeouts.
    //
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);

    DEBUG_PRINT("Sound out control initialized\n", NULL);
}

void soundoutTimerHanlder(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    
    // UARTprintf("Tick: %i\n", cnt);
    // scan_keys();
    
    if(cnt) {
        dac_put(3000);
        cnt = 0;
    } else {
        dac_put(0);
        cnt = 1;
    }
     
}