/*
 * Alarm with RTC.c
 *
 * Created: 9/26/2023 4:25:07 PM
 *  Author: N A E E M
 */ 


#include "7-segment.h"
#include "LCD.h"
#include "KEYPAD.h"

/*************************Macros for Key_Pad********************************/
#define Close_Alarm ('-')
#define Set ('C')
#define No_Press ('x')
#define Alarm_Set ('+')

/*********************Macros for some peripherals*************************/
/////Buzzer/////
#define Set_Buzzer SETBIT(DDRA,PA0) 
#define Open_Buzzer SETBIT(PORTA,PA0)
#define Close_Buzzer CLRBIT(PORTA,PA0)

/****************************Global variables*****************************/
volatile uint8_t sec=0,min=0,hr=0,check=0,tk=0;

/****************************Functions Prototype*****************************/
void LCD(uint8_t hr,uint8_t min,uint8_t sec);
uint8_t Setting_Minutes_Hours(uint8_t *hr,uint8_t *min,uint8_t *sec);

/****************************Main Function*****************************/
int main(void)
{
	uint8_t HR=0,MIN=0,SEC=0;
	uint8_t AS=0,Error=0;
	//***Functions_Initialization***//
	sevenS_init();
	LCD_init();
	KEYPAD_init();
	Timer0_Compare_Pre_init(50);  //Time= 50 * (1024/(16M))  -->Prescaler=1024
	
	//***Set_Peripherals***//
	Set_Buzzer;
	
	while(1)
    {
		LCD_write_command(First_Line(6));
		LCD_write_string("TIME");
		
		while(Key_pressed() == No_Press)
		{
			LCD(hr,min,sec);
			
			//Turn on alarm
			if((hr==HR) && (min==MIN) && (AS==1))
			{
				Open_Buzzer;
			}
		}

		//Turn off alarm
		if(Key_pressed() == Close_Alarm)
		{
			Close_Buzzer;
			AS=0;
		}
		
		//Time_set
		else if(Key_pressed() == Set)
		{
			uint8_t hr1,min1,sec1;
			
			check=1; //==> stop incrementing counter for interrupt
			
			while(Key_pressed() != No_Press);
			while(Key_pressed() == No_Press);
			
			hr1=hr;
			min1=min;
			sec1=sec;
			
			Error=Setting_Minutes_Hours(&hr1 , &min1 , &sec1);
			
			if(Error)
			{
				//Do nothing
			}
			else
			{
				hr=hr1;
				min=min1;
				sec=sec1;	
			}
			check=0; //==> continue incrementing counter for interrupt 
			
			while(Key_pressed() != No_Press);
		}
		
		//Alarm_set
		else if(Key_pressed() == Alarm_Set)
		{
			while(Key_pressed() != No_Press);
			LCD_write_command(1);
			LCD_write_command(First_Line(4));
			LCD_write_string("Set Alarm");
			LCD_write_command(Second_Line(0));	
			LCD(HR,MIN,SEC);
			while(Key_pressed() == No_Press);
			
			if(Key_pressed() != Alarm_Set)
			{
				Error=Setting_Minutes_Hours( &HR , &MIN , &SEC);
					
				if(Error){
					HR=0;
					MIN=0;
					SEC=0;
				}
				else
				{
					LCD_write_command(1);
					LCD_write_command(First_Line(3));
					LCD_write_string("Alarm Set");
					AS=1;
					_delay_ms(500);
					LCD_write_command(1);
				}
				
			}
			else 
			{
				LCD_write_command(1);	
			}
		}
    }
}

/*****************************************************************************
* Function Name: LCD
* Purpose      : Type on LCD
* Parameters   : uint8_t
* Return value : void
*****************************************************************************/
void LCD(uint8_t hr,uint8_t min,uint8_t sec)
{
	static uint8_t hr_shift=1,min_shift=3;
	if(hr>=10)  hr_shift=2;
	else if(hr<10) hr_shift=1;
	if(min>=10) min_shift=hr_shift+3;
	else if(min<10) min_shift=hr_shift+2;
	
	
	LCD_write_command(Second_Line(0));
	LCD_write_num(hr);
	LCD_write_command(Second_Line(hr_shift));
	LCD_write_string(":");
	LCD_write_num(min);
	LCD_write_command(Second_Line(min_shift));
	LCD_write_string(":");
	LCD_write_num(sec);
	LCD_write_string("      ");
}

/*****************************************************************************
* Function Name: Setting_Minutes_Hours
* Purpose      : Setting minutes and hours for clock and alarm and return error state
* Parameters   : uint8_t*
* Return value : uint8_t
*****************************************************************************/
uint8_t Setting_Minutes_Hours(uint8_t *hr,uint8_t *min,uint8_t *sec){
	
	uint8_t error_check=0;
	
	//Hours set
	while(Key_pressed() != Set)
	{
		static uint8_t flag=0;
		if(flag==0)
		{
			*hr=Key_pressed()-48;
			while(Key_pressed() != No_Press);
			flag=1;
		}
		else
		{
			*hr=*hr*10+(Key_pressed()-48);
			flag=0;
			LCD(*hr,*min,*sec);
			while(Key_pressed() != No_Press);
			break;
		}
		LCD(*hr,*min,*sec);
		while(Key_pressed() == No_Press);
	}
	while(Key_pressed() != No_Press);
	
	//Minutes set
	while(Key_pressed() != Set)
	{
		while(Key_pressed() == No_Press);
		static uint8_t flag=0;
		if(flag==0)
		{
			*min=Key_pressed()-48;
			while(Key_pressed() != No_Press);
			flag=1;
		}
		else
		{
			*min=*min*10+(Key_pressed()-48);
			flag=0;
			LCD(*hr,*min,*sec);
			while(Key_pressed() != No_Press);
			break;
		}
		LCD(*hr,*min,*sec);
		while(Key_pressed() == No_Press);
	}
	while(Key_pressed() != Set);
	while(Key_pressed() != No_Press);
	
	//check inputs
	if((*hr==24 && *min>0) || (*hr>24) || (*min>59))
	{
		LCD_write_command(1);
		LCD_write_command(First_Line(2));
		LCD_write_string("Wrong Entry");
		_delay_ms(500);
		LCD_write_command(1);
		error_check=1;
	}
	return error_check;	
}

/*****************************************************************************
* Function Name: ISR for timer0 CTC
* Purpose      : Setting interrupt routine
* Parameters   : void
* Return value : void
*****************************************************************************/
ISR(TIMER0_COMP_vect){
	static uint8_t flag=1;
	static uint16_t count=0;
	if(check==0) count++;
	if(count==310){count=0; tk=1;} //==> 310 == 1sec
		
	//switching 7-segment in sequence
	switch(flag){
		case 1: SS12_read(sec/10,1); flag=2; break;
		case 2: SS11_read(sec%10,1); flag=3; break;
		case 3: SS22_read(min%10,1); flag=4; break;
		case 4: SS21_read(min/10,1); flag=5; break;
		case 5: SS32_read(hr %10,1); flag=6; break;
		case 6: SS31_read(hr /10,1); flag=1; break;
	}
	
	if(tk == 1) {sec++; tk=0; } //sec increment
	if(sec==60){sec=0; min++; } //min increment
	if(min==60){min=0; hr++; } //Hr increment
	if(hr==24){hr=0; min=0; sec=0;} //Hr reset
	
}