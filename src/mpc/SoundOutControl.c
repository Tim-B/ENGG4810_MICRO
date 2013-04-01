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
    
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / ((1000 * 44)));
    // TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

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
    
    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i].in_use = false;
    }
    
    samples[0].in_use = true;
    samples[0].fileName = "/mpc/1.wav";
    
    samples[1].in_use = true;
    samples[1].fileName = "/mpc/2.wav";
    
    samples[2].in_use = true;
    samples[2].fileName = "/mpc/3.wav";
    
    samples[3].in_use = true;
    samples[3].fileName = "/mpc/4.wav";

    samples[4].in_use = true;
    samples[4].fileName = "/mpc/5.wav";

    samples[5].in_use = true;
    samples[5].fileName = "/mpc/6.wav";

    samples[6].in_use = true;
    samples[6].fileName = "/mpc/7.wav";

    samples[7].in_use = true;
    samples[7].fileName = "/mpc/8.wav";

    samples[8].in_use = true;
    samples[8].fileName = "/mpc/9.wav";    

    
    // samples[2].playing = true;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        if (samples[i].in_use == true) {
            setup_sample(&samples[i]);
            UARTprintf("Sample rate: %i\n", samples[i].header.bitsPerSample);
            UARTprintf("Chanels: %i\n", samples[i].header.NumOfChan);
        }
        add_key_sample(&samples[i]);
    }
    
    UARTprintf("Short: %i\n", sizeof(short));

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
                check_reset_sample(&samples[i]);
            }
        }
        checkSamples = false;
    }
}

void soundoutTimerHanlder(void) {
    cnt++;
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    
    short val = 0;
    
    for (int i = 0; i < NUM_SAMPLES; i++) {
        if (samples[i].playing == true) {
            val += read_sample(&samples[i]);
        }
    }
    
    dac_put(val);
    
/*
    if(cnt) {
        dac_put(3000);
        cnt = 0;
    } else {
        dac_put(0);
        cnt = 1;
    }
*/
    checkSamples = true;
}