/*
 * LCD_cfg.h
 *
 * Created: 8/31/2023 11:31:05 AM
 *  Author: N A E E M
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_
#include "generic_macros_header.h"

#define LCD_CFG_PINS DDRA |= 0b11111100;

#define RS(x) if(x==0) CLRBIT(PORTA,PA2);else SETBIT(PORTA,PA2);
#define EN(x) if(x==0) CLRBIT(PORTA,PA3);else SETBIT(PORTA,PA3);
#define D4(x) if(x==0) CLRBIT(PORTA,PA4);else SETBIT(PORTA,PA4);
#define D5(x) if(x==0) CLRBIT(PORTA,PA5);else SETBIT(PORTA,PA5);
#define D6(x) if(x==0) CLRBIT(PORTA,PA6);else SETBIT(PORTA,PA6);
#define D7(x) if(x==0) CLRBIT(PORTA,PA7);else SETBIT(PORTA,PA7);

#endif /* LCD_CFG_H_ */