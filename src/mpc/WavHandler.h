/* 
 * File:   WavHandler.h
 * Author: Tim
 *
 * Created on 31 March 2013, 2:44 PM
 */

#ifndef WAVHANDLER_H
#define	WAVHANDLER_H

#include "../system/global.h"
#include <ctype.h>

#define WAV_HEADER_SIZE 40
#define WAV_SAMPLE_SIZE 32

typedef struct WAVE_HEADER {
    char RIFF[4];
    unsigned long ChunkSize;
    char WAVE[4];
    char fmt[4];
    unsigned long Subchunk1Size;
    unsigned short AudioFormat;
    unsigned short NumOfChan;
    unsigned long SamplesPerSec;
    unsigned long bytesPerSec;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    char Subchunk2ID[4];
    unsigned long Subchunk2Size;
    float other[9];
} wave_header;

wave_header parse_header(BYTE* buffer);

#endif	/* WAVHANDLER_H */

