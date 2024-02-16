/*
 * _7_segment.c
 *
 * Created: 9/2/2023 9:04:01 AM
 *  Author: C O N N E C T
 */ 

#include "generic_macros_header.h"
#include "7-segment.h"
#include "7-segment_cfg.h"

void sevenS_init(void){
	ss_init();
}

//First 7-segment
void SS11_read(uint8_t num,uint8_t EN){
	SS1_1(num,EN);
}
void SS12_read(uint8_t num,uint8_t EN){
	SS1_2(num,EN);
}

//Second 7-segment
void SS21_read(uint8_t num,uint8_t EN){
	SS2_1(num,EN);
}
void SS22_read(uint8_t num,uint8_t EN){
	SS2_2(num,EN);
}

//Third 7-segment
void SS31_read(uint8_t num,uint8_t EN){
	SS3_1(num,EN);
}
void SS32_read(uint8_t num,uint8_t EN){
	SS3_2(num,EN);
}