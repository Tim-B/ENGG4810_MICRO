#include "global.h"

unsigned char mpc_row_keys[] = {GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
unsigned char mpc_col_keys[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2};

int bounce_hold = 0;
int debounce_target = 0;

void keycontrol_setup() {

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, HIGH_PINS);
    GPIOPinWrite(GPIO_PORTC_BASE, HIGH_PINS, HIGH_PINS);
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, LOW_PINS);

    GPIOIntTypeSet(GPIO_PORTD_BASE, LOW_PINS, GPIO_RISING_EDGE);
    // GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinIntEnable(GPIO_PORTD_BASE, LOW_PINS);
    GPIOPortIntRegister(GPIO_PORTD_BASE, keypressHanlder);
    DEBUG_PRINT("Keypad control initialized\n", NULL);
}

void keypressHanlder(void) {
    GPIOPinIntClear(GPIO_PORTD_BASE, LOW_PINS);
    if(!bounce_hold) {
        scan_keys();
        bounce_hold = 1;
        debounce_target = get_tick() + DEBOUNCE_DELAY;
    }
}

void checkDebounce() {
    if(bounce_hold && (get_tick() > debounce_target)) {
        bounce_hold = 0;
    }
}

void scan_keys() {
    int readVal = 0;
    for (int r = 0; r < NUM_KEY_ROWS; r++) {
        GPIOPinWrite(GPIO_PORTC_BASE, HIGH_PINS, 0 | mpc_row_keys[r]);
        for (int c = 0; c < NUM_KEY_COLS; c++) {
            readVal = GPIOPinRead(GPIO_PORTD_BASE, mpc_col_keys[c]);
            if (readVal) {
                DEBUG_PRINT("Key pressed %i %i \n", r, c);
            }
        }
    }
    GPIOPinWrite(GPIO_PORTC_BASE, HIGH_PINS, HIGH_PINS);
}