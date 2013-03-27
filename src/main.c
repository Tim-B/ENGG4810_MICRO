#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "utils/uartstdio.h"
#include <inttypes.h>
#include <stdio.h>

void dacWrite(uint16_t val) {
    long unsigned int *nothing;
    long unsigned int something = 0;
    nothing = &something;
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
   // UARTprintf("BEF\n");
    SSIDataPut(SSI0_BASE, 0x31);
    //SSIDataGet(SSI0_BASE, nothing);
    //while(SSIBusy(SSI0_BASE)) { }
    SSIDataPut(SSI0_BASE, val);
    //SSIDataGet(SSI0_BASE, nothing);
    //while(SSIBusy(SSI0_BASE)) { }
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
    SysCtlDelay(200000);
    UARTprintf("Test swiaft\n");
    
}

int main() {

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
            SYSCTL_XTAL_16MHZ);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioInit(0);
    UARTprintf("Test\n");

    //
    // Configure the SSI.
    //
    UARTprintf("Test1\n");
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    UARTprintf("Test2\n");
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    //GPIOPinConfigure(GPIO_PA3_SSI0FSS);

    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);
    UARTprintf("Test6\n");
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
    UARTprintf("Test7\n");
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_2);
    UARTprintf("Test8\n");
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
            SSI_MODE_MASTER, 1000000, 0);
    UARTprintf("Test9\n");
    SSIEnable(SSI0_BASE);

    UARTprintf("Test10\n");
    //
    // Send some data.
    //
    int val = 2047;
    while (1) {
        dacWrite(val);
        SysCtlDelay(200000);
        val++;
        if (val > 4095) {
            val = 0;
        }
    }

}