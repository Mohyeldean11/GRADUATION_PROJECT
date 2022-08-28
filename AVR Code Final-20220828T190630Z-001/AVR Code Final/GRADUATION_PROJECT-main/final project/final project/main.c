#include <avr/io.h>
#include "DATA_TYPES.h"
#include "LBIT_Math.h"
#include "MDIO_INTERFACE.h"
#include "TIMER_INTERFACE.h"
#include "PROJECT_INTERFACING.h"

/*
D4 Cytron DIR Output
B3	Cytron PWM
Base input = A5 &A6

BASE_RIGHT=MDIO_GETPIN_VALUE(PORTA,PIN2);
BASE_LEFT=MDIO_GETPIN_VALUE(PORTA,PIN3);

Z_AXIS_UP=MDIO_GETPIN_VALUE(PORTA,PIN0);
Z_AXIS_DOWN=MDIO_GETPIN_VALUE(PORTA,PIN1);



*/
						/************************************************************************/
						/*						global variables								*/
						/************************************************************************/
						
u8_t Z_AXIS_UP , Z_AXIS_DOWN ,BASE_RIGHT , BASE_LEFT ,FEED_UP ,FEED_DOWN,Y_AXIS_LEFT,Y_AXIS_RIGHT,stop_button=0;



void PWM_Init();


int main(void)
{
	
	MDIO_SETPIN_STATUS(PORTB,PIN1|PIN3,OUTPUT);      //SETTING THE OC0 AND DIRECTION FOR CYTRON
	
	TIMER0_INITIALIZE(PWM_PHASE,NO_PRESCALE);		//OC0 PWM
	
	PWM_Init();								// OC2 PWM
	
	

	motor_init(idle_state,BASE_M);
	TIMER0_INITIALIZE(PWM_PHASE,NO_PRESCALE);
	
	//TIMER0_PWM_SETUP(PWM_NON_INVERT,255*.);
	while (1)
	{
		TIMER0_PWM_SETUP(PWM_NON_INVERT,255*.7);		//.7	
		/*INITIALIZING THE PWM SIGNALS*/					
		
	
		/*GETTING THE VALUES OF THE SWITCHES*/
		keys_init();
		
		
		
		/*if (((FEED_UP==1) && (FEED_DOWN ==1)))
		{
			TIMER0_PWM_SETUP(PWM_NON_INVERT,255*0);
			motor_init(stop_state,FEED_M);
		}
		else if ((FEED_UP==0 && FEED_DOWN ==0)){
			TIMER0_PWM_SETUP(PWM_NON_INVERT,255*0);
			motor_init(stop_state,FEED_M);
		}
		
		else if ((FEED_UP==1 && FEED_DOWN ==0)){
			TIMER0_PWM_SETUP(PWM_NON_INVERT,255*.7);
			motor_init(start_state,FEED_M);
		}
		
		else if ((FEED_UP==0 && FEED_DOWN ==1)){
			TIMER0_PWM_SETUP(PWM_NON_INVERT,255*.7);
			motor_init(stop_state,FEED_M);
		}*/
		
		
		/*if (Z_AXIS_UP==1)
		{
			OCR2=255;
			motor_init(start_state,Z_AXIS_M);
		TIMER0_PWM_SETUP(PWM_NON_INVERT,255);
			
		}
		if (Z_AXIS_DOWN==1)
		{
			motor_init(start_state,Z_AXIS_M);
			MDIO_SETPIN_VALUE(PORTB,PIN0,LOW);
		TIMER0_PWM_SETUP(PWM_NON_INVERT,255*.7);
		}
		if (stop_button==1)
		{
			MDIO_SETPIN_VALUE(PORTB,PIN3,LOW);
		}*/
		/*if(BASE_RIGHT==1)
		{
			motor_init(start_state,BASE_M);
		}
		if (BASE_LEFT==1)
		{
			motor_init(start_state,BASE_M);
			relay_ACTIVATE(relay_1);
			relay_ACTIVATE(relay_2);
		}
		if (FEED_UP==1)
		{
			motor_init(start_state,FEED_M);
		}
		if(FEED_DOWN==1)
		{
			motor_init(start_state,FEED_M);
			relay_ACTIVATE(relay_3);
			relay_ACTIVATE(relay_4);
		}
		if(Y_AXIS_RIGHT==1)
		{
			motor_init(start_state,Y_AXIS_M);
		}
		if(Y_AXIS_LEFT==1)
		{
			motor_init(start_state,Y_AXIS_M);
			relay_ACTIVATE(relay_5);
			relay_ACTIVATE(relay_6);
		}*/
	}
}


void PWM_Init(){
	DDRD |= (1<<7);                              //set PD7 as PWM output
	

	TCCR2 |= (1<<WGM20)|(1<<WGM21);                //select Fast PWM mode by setting bits


	TCCR2 |=(1<<COM21)|(1<<CS20)|(0<<CS21)|(0<<CS22);   //clear OC2 on compare match


	
}
void keys_init()
{
	/*KEYS INITIALIZING ON PORT A*/
	MDIO_SETPIN_STATUS(PORTA,PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7,INPUT_FLOAT);
	MDIO_SETPIN_STATUS(PORTD,PIN6,INPUT_FLOAT);
	/*KEYS VALUES*/
	Z_AXIS_UP=MDIO_GETPIN_VALUE(PORTA,PIN0);
	Z_AXIS_DOWN=MDIO_GETPIN_VALUE(PORTA,PIN1);
	
	BASE_RIGHT=MDIO_GETPIN_VALUE(PORTA,PIN2);
	BASE_LEFT=MDIO_GETPIN_VALUE(PORTA,PIN3);
	
	FEED_UP=MDIO_GETPIN_VALUE(PORTA,PIN4);
	FEED_DOWN=MDIO_GETPIN_VALUE(PORTA,PIN5);
	
	Y_AXIS_RIGHT=MDIO_GETPIN_VALUE(PORTA,PIN6);
	Y_AXIS_LEFT=MDIO_GETPIN_VALUE(PORTA,PIN7);
	stop_button=MDIO_GETPIN_VALUE(PORTD,PIN6);
	
	
}


void motor_init(u8_t status,u8_t Motor)
{
	MDIO_SETPIN_STATUS(PORTD,PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7,OUTPUT);
	
	
	if (status==idle_state)
	{
		MDIO_SETPIN_VALUE(PORTD,PIN0|PIN1|PIN2|PIN3|PIN4|PIN5|PIN6|PIN7,LOW);
	}
	else if (status==start_state)
	{
		switch(Motor)
		{
			case Z_AXIS_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN0,HIGH);
				MDIO_SETPIN_VALUE(PORTD,PIN1,LOW);
				break;
			}
			case BASE_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN2,HIGH);
				MDIO_SETPIN_VALUE(PORTD,PIN3,LOW);
				break;
			}
			case FEED_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN4,HIGH);
				break;
			}
			case Y_AXIS_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN5,HIGH);
				MDIO_SETPIN_VALUE(PORTD,PIN6,LOW);
				break;
			}
		}
	}
	else if (status==stop_state)
	{
		switch(Motor)
		{
			case Z_AXIS_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN0,LOW);
				MDIO_SETPIN_VALUE(PORTD,PIN1,LOW);
				break;
			}
			case BASE_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN2,LOW);
				MDIO_SETPIN_VALUE(PORTD,PIN3,LOW);
				break;
			}
			case FEED_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN4,LOW);
				break;
			}
			case Y_AXIS_M:
			{
				MDIO_SETPIN_VALUE(PORTD,PIN5,LOW);
				MDIO_SETPIN_VALUE(PORTD,PIN6,LOW);
				break;
			}
		}
	}
}
