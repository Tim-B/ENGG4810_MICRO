#include "../system/global.h"

int timestamp = 0;
int tempoVal = 0;
bool ledState = false;

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
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
    
    tempoVal = tempo();
    tempoVal = (1000 * 60) / tempoVal;

    DEBUG_PRINT("System tick initialized\n", NULL);
}

void sys_tick() {
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    timestamp++;
    if(timestamp % tempoVal == 0) {
        if (ledState) {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0); 
            ledState = false;
        } else {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
            ledState = true;
        }
    }
}

int get_tick() {
    return timestamp;
}
