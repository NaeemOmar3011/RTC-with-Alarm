/*
 * KEYPAD_cfg.h
 *
 * Created: 8/31/2023 1:41:03 PM
 *  Author: N A E E M
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_
#include "generic_macros_header.h"

#define KEYPAD_port_init() DDRB =0b11110000; \
						 PORTB =0b11111111; 	

#define KEYPAD_1(x) if(x==0) CLRBIT(PORTB,PB4); else SETBIT(PORTB,PB4);
#define KEYPAD_2(x) if(x==0) CLRBIT(PORTB,PB5); else SETBIT(PORTB,PB5);
#define KEYPAD_3(x) if(x==0) CLRBIT(PORTB,PB6); else SETBIT(PORTB,PB6);
#define KEYPAD_4(x) if(x==0) CLRBIT(PORTB,PB7); else SETBIT(PORTB,PB7);

#define KEYPAD_A READBIT(PINB,PB0)
#define KEYPAD_B READBIT(PINB,PB1)
#define KEYPAD_C READBIT(PINB,PB2)
#define KEYPAD_D READBIT(PINB,PB3)



#endif /* KEYPAD_CFG_H_ */