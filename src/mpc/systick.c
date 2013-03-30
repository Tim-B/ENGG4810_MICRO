#include "global.h"

int timestamp = 0;

void tick_setup() {
    
    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);

    TimerLoadSet(TIMER2_BASE, TIMER_A, SysCtlClockGet() / 1000);


    //
    // Setup the interrupts for the timer timeouts.
    //
    IntEnable(INT_TIMER2A);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER2_BASE, TIMER_A);

    DEBUG_PRINT("System tick initialized\n", NULL);
}

void sys_tick() {
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    timestamp++;
}

int get_tick() {
    return timestamp;
}
