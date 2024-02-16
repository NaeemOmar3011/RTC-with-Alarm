/*
 * _7_segment_cfg.h
 *
 * Created: 9/2/2023 9:04:34 AM
 *  Author: C O N N E C T
 */ 


#ifndef SEGMENT_CFG_H_
#define SEGMENT_CFG_H_
#include "generic_macros_header.h"
uint8_t ss[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f};
/*    EN A B C D E F G 
  0--> 0 1 1 1 1 1 1 0 -->0x7E
  1--> 0 0 1 1 0 0 0 0 -->0X30
  2--> 0 1 1 0 1 1 0 1 -->0x6D
  3--> 0 1 1 1 1 0 0 1 -->0x79
  4--> 0 0 1 1 0 0 1 1 -->0x33
  5--> 0 1 0 1 1 0 1 1 -->0x5B
  6--> 0 1 0 1 1 1 1 1 -->0x5F
  7--> 0 1 1 1 0 0 0 0 -->0xE0
  8--> 0 1 1 1 1 1 1 1 -->0x7F
  9--> 0 1 1 1 1 0 1 1 -->0x7B
  
*/


#define ss_init() DDRC =0xFF; DDRD =0xFF; //CLRBIT(DDRD,PD6); SETBIT(PORTD,PD7); SETBIT(PORTD,PD6);

//First 7-segment
#define SS1_1(num,EN) PORTC=0x80; PORTC|= ss[num]; \ 
		if(EN==1) {PORTD=~0b000010;} else {CLRBIT(PORTD,PD1);SETBIT(PORTD,PD0);}
#define SS1_2(num,EN) PORTC=0x80; PORTC|= ss[num]; \ 
		if(EN==1) {PORTD=~0b000001;} else {CLRBIT(PORTD,PD0);SETBIT(PORTD,PD1);}
//Second 7-segment
#define SS2_1(num,EN) PORTC=0x80; PORTC|= ss[num]; \
		if(EN==1) {PORTD=~0b001000;} else {CLRBIT(PORTD,PD3);SETBIT(PORTD,PD2);}
#define SS2_2(num,EN) PORTC=0x80; PORTC|= ss[num]; \ 
		if(EN==1) {PORTD=~0b000100;} else {CLRBIT(PORTD,PD2);SETBIT(PORTD,PD3);}
//Third 7-segment			
#define SS3_1(num,EN) PORTC=0x80; PORTC|= ss[num]; \
		if(EN==1) {PORTD=~0b100000;} else {CLRBIT(PORTD,PD5);SETBIT(PORTD,PD4);}
#define SS3_2(num,EN) PORTC=0x80; PORTC|= ss[num]; \ 
		if(EN==1) {PORTD=~0b010000;} else {CLRBIT(PORTD,PD4);SETBIT(PORTD,PD5);}			

#endif /* 7-SEGMENT_CFG_H_ */