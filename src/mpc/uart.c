#include "uart.h"
#include "utils/uartstdio.h"

void uart_setup() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioInit(0);
    DEBUG_PRINT("\n====================\n\n", NULL);
    DEBUG_PRINT("UART initialized\n", NULL);
    DEBUG_PRINT("Application info: %s %s\n", __DATE__, __TIME__);
}
