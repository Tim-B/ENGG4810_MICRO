#include "../system/global.h"

unsigned char mpc_row_keys[] = {GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};
unsigned char mpc_col_keys[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};

bool bounce_hold = 0;
int debounce_target = 0;

int xAllocated = 0;
int yAllocated = 0;

void keycontrol_setup() {

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, HIGH_PINS);
    GPIOPinWrite(GPIO_PORTC_BASE, HIGH_PINS, HIGH_PINS);
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, LOW_PINS);

    GPIOIntTypeSet(GPIO_PORTD_BASE, LOW_PINS, GPIO_BOTH_EDGES);
    GPIOPinIntEnable(GPIO_PORTD_BASE, LOW_PINS);
    GPIOPortIntRegister(GPIO_PORTD_BASE, keypressHanlder);
    DEBUG_PRINT("Keypad control initialized\n", NULL);
}

void add_key_sample(mpc_sample *sample) {
    keys[xAllocated][yAllocated].sample = sample;
    DEBUG_PRINT("Assigning %i %i %i\n", xAllocated, yAllocated, sample->header.SamplesPerSec);
    yAllocated++;
    if(yAllocated >= NUM_KEY_COLS) {
        xAllocated++;
        yAllocated = 0;
    }
    if(xAllocated >= NUM_KEY_ROWS) {
        yAllocated = 0;
        xAllocated = 0;
    }
}

void keypressHanlder(void) {
    GPIOPinIntClear(GPIO_PORTD_BASE, LOW_PINS);
    if (!bounce_hold) {
        // scan_keys();
        bounce_hold = true;
        debounce_target = get_tick() + DEBOUNCE_DELAY;
    }
}

void checkDebounce() {
    if (bounce_hold && (get_tick() > debounce_target)) {
        bounce_hold = false;
    }
}

void scan_keys() {
    int readVal = 0;
    mpc_sample *sample;
    for (int r = 0; r < NUM_KEY_ROWS; r++) {
        GPIOPinWrite(GPIO_PORTC_BASE, HIGH_PINS, 0 | mpc_row_keys[r]);
        for (int c = 0; c < NUM_KEY_COLS; c++) {
            //DEBUG_PRINT("Checking %i %i\n", r, c);
            sample = keys[r][c].sample;
            if (sample->in_use == true) {
                // DEBUG_PRINT("Sample active: %i %i\n", r, c);
                // SysCtlDelay(25);
                readVal = GPIOPinRead(GPIO_PORTD_BASE, mpc_col_keys[c]);
                if (readVal) {
                    trigger_sample_event(KEY_ON, sample);
                    // DEBUG_PRINT("Sample active: %i %i\n", r, c);
                } else {
                    trigger_sample_event(KEY_OFF, sample);
                }
            }
        }
    }
    GPIOPinWrite(GPIO_PORTC_BASE, HIGH_PINS, HIGH_PINS);
}