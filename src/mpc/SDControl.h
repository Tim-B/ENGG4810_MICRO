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

void mpc_sample_open(mpc_sample *sample);
void mpc_sample_load_next(mpc_sample *sample, float* buffer);
void mpc_sample_reset(mpc_sample *sample);
void read_config(config *config);

#define PATH "/mpc"

#endif	/* SDCONTROL_H */

