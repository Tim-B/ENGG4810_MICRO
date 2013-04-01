#include "global.h"
#include "SoundOutControl.h"

int cnt = 0;

mpc_sample sample;

bool checkSamples = false;

void soundoutcontrol_setup() {
    
    //
    // Set the clocking to run directly from the crystal.
    //
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
    // Configure the two 32-bit periodic timers.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    
    //TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / ((1024 * 5)));
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
    samples[0].in_use = true;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        if (samples[i].in_use == true) {
            setup_sample(&samples[i], "something.wav");
            UARTprintf("Sample rate: %i\n", samples[i].header.bitsPerSample);
            UARTprintf("Sample setup %p\n", &samples[i]);
        }
    }

    DEBUG_PRINT("Sound out control initialized\n", NULL);
}

void checkSampleState() {
    if (checkSamples) {
        mpc_sample sample;
        for (int i = 0; i < NUM_SAMPLES; i++) {
            sample = samples[i];
            if (samples[i].in_use == true) {
                // UARTprintf("Sample check %i %p\n", i, &samples[i]);
                check_waiting(&samples[i]);
            }
        }
        checkSamples = false;
    }
}

void soundoutTimerHanlder(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
   // sample = samples[0];
    
    short val = read_sample(&samples[0]);
    // UARTprintf("Tick: %i\n", val);
    // scan_keys();
    //dac_put(val);
    
    if(cnt) {
        dac_put(3000);
        cnt = 0;
    } else {
        dac_put(0);
        cnt = 1;
    }
    checkSamples = true;
}