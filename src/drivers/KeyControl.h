/* 
 * File:   KeyControl.h
 * Author: Tim
 *
 * Created on 30 March 2013, 2:47 PM
 */

#ifndef KEYCONTROL_H
#define	KEYCONTROL_H

void keycontrol_setup();
void keypressHanlder(void);
void checkDebounce();

void scan_keys();


#define HIGH_PINS GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
#define LOW_PINS GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3

#define NUM_KEY_ROWS 4
#define NUM_KEY_COLS 4

#define DEBOUNCE_DELAY 50

extern unsigned char mpc_row_keys[NUM_KEY_ROWS];

extern unsigned char mpc_col_keys[NUM_KEY_COLS];

void add_key_sample(mpc_sample *sample);

typedef struct MPC_KEY {
    mpc_sample* sample;
} mpc_key;

mpc_key keys[NUM_KEY_COLS][NUM_KEY_ROWS];

#endif	/* KEYCONTROL_H */

