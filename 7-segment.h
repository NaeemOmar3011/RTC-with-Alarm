/*
 * _7_segment.h
 *
 * Created: 9/2/2023 9:04:18 AM
 *  Author: C O N N E C T
 */ 


#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "generic_macros_header.h"
#define BUTTON READBIT(PIND,PD6)

void sevenS_init(void);

//First 7-segment
void SS11_read(uint8_t num,uint8_t EN);
void SS12_read(uint8_t num,uint8_t EN);
//Second 7-segment
void SS21_read(uint8_t num,uint8_t EN);
void SS22_read(uint8_t num,uint8_t EN);
//Third 7-segment
void SS31_read(uint8_t num,uint8_t EN);
void SS32_read(uint8_t num,uint8_t EN);

#endif /* 7-SEGMENT_H_ */