#define NUM_SSI_DATA 3

#include "../system/global.h"
#include "DACControl.h"
#include "driverlib/ssi.h"
#include "inc/hw_ssi.h"

void dac_setup() {
    unsigned long ulDataRx[NUM_SSI_DATA];
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);
    GPIOPinConfigure(GPIO_PF2_SSI1CLK);
    GPIOPinConfigure(GPIO_PF3_SSI1FSS);
    GPIOPinConfigure(GPIO_PF0_SSI1RX);
    GPIOPinConfigure(GPIO_PF1_SSI1TX);
    GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0 | GPIO_PIN_1);
    SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 20000000, 16);
    SSIEnable(SSI1_BASE);
    while (SSIDataGetNonBlocking(SSI1_BASE, &ulDataRx[0])) {}
    DEBUG_PRINT("DAC control initialized\n", NULL);
}

void dac_put(int value) {
    int16_t write = 0;
    write = 0x0FFF & value;
    write = 0x3000 | write;
    // DEBUG_PRINT("Writing: %i\n", value);

    SSIDataPut(SSI1_BASE, write);
    while (SSIBusy(SSI1_BASE)) {}
}
