/* 
 * File:   ADCDriver.h
 * Author: Tim
 *
 * Created on 6 April 2013, 4:26 PM
 */

#ifndef ADCDRIVER_H
#define	ADCDRIVER_H

void setupADC();
void readADC(sample_block *block);
void ADCIntHandler(void);

#endif	/* ADCDRIVER_H */

