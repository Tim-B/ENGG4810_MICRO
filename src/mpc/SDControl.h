/* 
 * File:   SDControl.h
 * Author: Tim
 *
 * Created on 31 March 2013, 1:33 PM
 */

#ifndef SDCONTROL_H
#define	SDCONTROL_H

void sd_init();

void sd_read();

FRESULT sd_list(char* path);

void mpc_sample_open(mpc_sample *sample, char* wavname);
void mpc_sample_load_next(mpc_sample *sample);

#define PATH "/mpc"

#endif	/* SDCONTROL_H */

