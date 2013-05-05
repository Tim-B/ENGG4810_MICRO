#include "global.h"
#include "SoundOutControl.h"

mpc_sample sample;

bool checkSamples = false;

int vol = 128;

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

    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / 44100);
    //TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

    // TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() / (1024 * 20));

    //
    // Setup the interrupts for the timer timeouts.
    //
    IntEnable(INT_TIMER0A);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);

    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i].in_use = false;
    }

    samples[0].in_use = true;
    samples[0].fileName = "/mpc/sin_16.wav";

    samples[1].in_use = true;
    samples[1].fileName = "/mpc/sin_16.wav";

    samples[2].in_use = true;
    samples[2].fileName = "/mpc/sin_16.wav";
    //samples[2].playing = true;

    samples[3].in_use = true;
    samples[3].fileName = "/mpc/style_16.wav";
    // samples[3].playing = true;

    samples[4].in_use = true;
    samples[4].fileName = "/mpc/style_16.wav";

    samples[5].in_use = true;
    samples[5].fileName = "/mpc/style_16.wav";

    samples[6].in_use = true;
    samples[6].fileName = "/mpc/avb_16.wav";

    samples[7].in_use = true;
    samples[7].fileName = "/mpc/avb_16.wav";

    samples[8].in_use = true;
    samples[8].fileName = "/mpc/avb_16.wav";
    samples[8].playing = true;

    samples[9].in_use = true;
    samples[9].fileName = "/mpc/sin_16.wav";

    samples[10].in_use = true;
    samples[10].fileName = "/mpc/sin_16.wav";

    samples[11].in_use = true;
    samples[11].fileName = "/mpc/sin_16.wav";

    for (int i = 0; i < NUM_SAMPLES; i++) {
        if (samples[i].in_use == true) {
            setup_sample(&samples[i]);
            DEBUG_PRINT("Sample rate: %i\n", samples[i].header.bitsPerSample);
            DEBUG_PRINT("Chanels: %i\n", samples[i].header.NumOfChan);
        }
        add_key_sample(&samples[i]);
    }

    DEBUG_PRINT("Sound out control initialized\n", NULL);
}

void setVol(int newvol) {
    vol = newvol;
}

void soundoutTimerHanlder(void) {
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    dac_put(readSample());
}

mpc_sample* getSampleByIndex(int i) {
    return &samples[i];
}
