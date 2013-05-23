/* 
 * File:   OutputHistory.h
 * Author: Tim
 *
 * Created on 23 May 2013, 6:30 PM
 */

#ifndef OUTPUTHISTORY_H
#define	OUTPUTHISTORY_H

#define OUT_BUF_LEN 800

typedef struct OUTPUT_BUFFER {
    short data[OUT_BUF_LEN];
    int start;
} output_buffer;

output_buffer delay_output;

short pull(output_buffer *output, int index);

void push(output_buffer *output, short val);

#endif	/* OUTPUTHISTORY_H */

