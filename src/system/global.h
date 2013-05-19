
#ifndef GLOBAL_H
#define	GLOBAL_H

// General includes
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
// End general includes

// Constants
#define M_PI 3.14159265358979323846
#define NUM_BLOCK_SAMPLED 512
// End Constants

// CMSIS includes
#include <ARMCM4.h>
#include <system_ARMCM4.h>
// End CMSIS includes

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
#include "driverlib/fpu.h"
#include "usblib/usblib.h"
#include "usblib/usb-ids.h"
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdmsc.h"
#include "driverlib/udma.h"
// End Stellaris includes

// Third Party Includes
#include "../third_party/fatfs/ff.h"
#include "../third_party/fatfs/diskio.h"
#include "../third_party/fatfs/integer.h"
#include "../third_party/usbmsc/usb_msc_structs.h"
#include "../third_party/usbmsc/usbdsdcard.h"
// End Third Party Includes

//Application Includes
#include "../mpc/uart.h"
#include "../mpc/WavHandler.h"
#include "../mpc/Sample.h"
#include "../mpc/SDControl.h"
#include "../mpc/application.h"
#include "../mpc/SoundOutControl.h"
#include "../mpc/DACControl.h"
#include "../drivers/KeyControl.h"
#include "../mpc/systick.h"
#include "../effects/EffectDefinitions.h"
#include "../effects/FilterHelp.h"
#include "../mpc/SampleBlock.h"
#include "../drivers/ADCDriver.h"
#include "../drivers/USBStore.h"
#include "../effects/EchoEffect.h"
#include "../effects/IIRFilter.h"
#include "../effects/DecimateEffect.h"
#include "../effects/KOEffect.h"

// End Application Includes

// Debug
#ifdef DEBUG
#define DEBUG_PRINT(a, ...) UARTprintf(a, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(a, ...) (void)0
#endif
// End Debug

#endif	/* GLOBAL_H */

