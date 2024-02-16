/*
 * KEYPAD.c
 *
 * Created: 8/31/2023 1:40:42 PM
 *  Author: N A E E M
 */ 
#include "generic_macros_header.h"
#include "KEYPAD.h"
#include "KEYPAD_cfg.h"

uint8_t KEYPAD_keys[]={
	'1', '2', '3', '/',
	'4', '5', '6', '*',
	'7', '8', '9', '-',
	'C', '0', '=', '+',	
};

void KEYPAD_init(void){
	KEYPAD_port_init();
}

uint8_t Key_pressed(void){
	uint8_t i;
	for(i=0;i<4;i++){
		switch(i){
			case 0: KEYPAD_1(0); KEYPAD_2(1); KEYPAD_3(1); KEYPAD_4(1); break;
			case 1: KEYPAD_1(1); KEYPAD_2(0); KEYPAD_3(1); KEYPAD_4(1);	break;
			case 2: KEYPAD_1(1); KEYPAD_2(1); KEYPAD_3(0); KEYPAD_4(1);	break;
			case 3: KEYPAD_1(1); KEYPAD_2(1); KEYPAD_3(1); KEYPAD_4(0);	break;
		}
		 if(KEYPAD_A==0) { return KEYPAD_keys[i+0];	}
		 if(KEYPAD_B==0) { return KEYPAD_keys[i+4];	}
		 if(KEYPAD_C==0) { return KEYPAD_keys[i+8];	}
		 if(KEYPAD_D==0) { return KEYPAD_keys[i+12];}
		 _delay_ms(10);	 
	}
	return 'x';
}