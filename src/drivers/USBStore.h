/* 
 * File:   USBStore.h
 * Author: Tim
 *
 * Created on 21 April 2013, 12:38 PM
 */

#ifndef USBSTORE_H
#define	USBSTORE_H

#define USBMSC_ACTIVITY_TIMEOUT 300
#define FLAG_UPDATE_STATUS 1

volatile enum {
    MSC_DEV_DISCONNECTED,
    MSC_DEV_CONNECTED,
    MSC_DEV_IDLE,
    MSC_DEV_READ,
    MSC_DEV_WRITE,
} g_eMSCState;

void setupUSBStore();

unsigned long usbRXHandler(void *pvCBData, unsigned long ulEvent,
        unsigned long ulMsgValue, void *pvMsgData);

unsigned long usbTXHandler(void *pvCBData, unsigned long ulEvent,
        unsigned long ulMsgValue, void *pvMsgData);

unsigned long USBDMSCEventCallback(void *pvCBData, unsigned long ulEvent,
        unsigned long ulMsgParam, void *pvMsgData);

void usbTask();

#endif	/* USBSTORE_H */

