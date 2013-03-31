/* 
 * File:   WavHandler.h
 * Author: Tim
 *
 * Created on 31 March 2013, 2:44 PM
 */

#ifndef WAVHANDLER_H
#define	WAVHANDLER_H

#define WAV_HEADER_SIZE 40
#define WAV_SAMPLE_SIZE 16

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
} wave_header;

typedef struct WAVE_SAMPLE {
    unsigned char left;
    unsigned char right;
} wave_sample;

wave_header parse_header(BYTE* buffer);

#endif	/* WAVHANDLER_H */

