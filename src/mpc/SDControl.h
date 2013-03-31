/* 
 * File:   SDControl.h
 * Author: Tim
 *
 * Created on 31 March 2013, 1:33 PM
 */

#ifndef SDCONTROL_H
#define	SDCONTROL_H

#include "../third_party/fatfs/ff.h"
#include "../third_party/fatfs/diskio.h"

void sd_init();

void sd_read();

FRESULT sd_list(char* path);

#define PATH "/mods"

#endif	/* SDCONTROL_H */

