
#ifndef GLOBAL_H
#define	GLOBAL_H

// General includes
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
// End general includes

// Stellaris includes
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "utils/uartstdio.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
// End Stellaris includes

// Third Party Includes

// End Third Party Includes

//Application Includes
#include "uart.h"
#include "application.h"
#include "SoundOutControl.h"
#include "DACControl.h"
#include "KeyControl.h"
#include "systick.h"
// End Application Includes


// Debug
#ifdef DEBUG
#define DEBUG_PRINT(a, ...) UARTprintf(a, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(a, ...) (void)0
#endif
// End Debug

#endif	/* GLOBAL_H */

