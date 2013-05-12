#include "../mpc/../system/global.h"

static unsigned long g_ulFlags;
static unsigned long g_ulIdleTimeout;
tDMAControlTable uDMAControlTable[64] __attribute__ ((aligned(1024)));

void setupUSBStore() {
    DEBUG_PRINT("USB1\n", NULL);
    g_eMSCState = MSC_DEV_DISCONNECTED;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);
    DEBUG_PRINT("USB2\n", NULL);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    uDMAControlBaseSet(&uDMAControlTable[0]);
    uDMAEnable();
    GPIOPinTypeUSBAnalog(GPIO_PORTD_BASE, GPIO_PIN_5 | GPIO_PIN_4);
    USBStackModeSet(0, USB_MODE_DEVICE, 0);
    DEBUG_PRINT("USB %s\n", g_sMSCDevice.pucVendor);
    USBDMSCInit(0, (tUSBDMSCDevice *) & g_sMSCDevice);
    DEBUG_PRINT("USBStore initialized\n", NULL);
}

unsigned long USBDMSCEventCallback(void *pvCBData, unsigned long ulEvent,
        unsigned long ulMsgParam, void *pvMsgData) {
    //
    // Reset the time out every time an event occurs.
    //
    g_ulIdleTimeout = USBMSC_ACTIVITY_TIMEOUT;

    switch (ulEvent) {
            //
            // Writing to the device.
            //
        case USBD_MSC_EVENT_WRITING:
        {
            //
            // Only update if this is a change.
            //
            if (g_eMSCState != MSC_DEV_WRITE) {
                //
                // Go to the write state.
                //
                g_eMSCState = MSC_DEV_WRITE;

                //
                // Cause the main loop to update the screen.
                //
                g_ulFlags |= FLAG_UPDATE_STATUS;
            }

            break;
        }

            //
            // Reading from the device.
            //
        case USBD_MSC_EVENT_READING:
        {
            //
            // Only update if this is a change.
            //
            if (g_eMSCState != MSC_DEV_READ) {
                //
                // Go to the read state.
                //
                g_eMSCState = MSC_DEV_READ;

                //
                // Cause the main loop to update the screen.
                //
                g_ulFlags |= FLAG_UPDATE_STATUS;
            }

            break;
        }
            //
            // The USB host has disconnected from the device.
            //
        case USB_EVENT_DISCONNECTED:
        {
            //
            // Go to the disconnected state.
            //
            g_eMSCState = MSC_DEV_DISCONNECTED;

            //
            // Cause the main loop to update the screen.
            //
            g_ulFlags |= FLAG_UPDATE_STATUS;

            break;
        }
            //
            // The USB host has connected to the device.
            //
        case USB_EVENT_CONNECTED:
        {
            //
            // Go to the idle state to wait for read/writes.
            //
            g_eMSCState = MSC_DEV_IDLE;

            break;
        }
        case USBD_MSC_EVENT_IDLE:
        default:
        {
            break;
        }
    }

    return (0);
}

void usbTask() {
    switch (g_eMSCState) {
        case MSC_DEV_READ:
            break;
        case MSC_DEV_WRITE:
            break;
        case MSC_DEV_DISCONNECTED:
            break;
        case MSC_DEV_CONNECTED:
            break;
        case MSC_DEV_IDLE:
            break;
    }
}