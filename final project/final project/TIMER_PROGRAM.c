/************************************************************************/
/* Name: TIMER_PROGRAM.c                                                */
/* Author: MOHIEE ELDEAN                                                */
/* Version: V1.0                                                        */
/* Usage: This file contains logical implementations of TIMER Module    */
/************************************************************************/

									/************************************************************************/
									/*								INSTRUCTIONS                            */
									/************************************************************************/
								/*	TO USE THE TIMER0 DRIVER
								INCASE FOR PWM MODE OR COMPARE MATCH MODE:
								1-USE THE TIMER0 COMPMATCH_SETUP FUNCTION OR THE PWM_SETUP TO INITIALIZE THE VALUES WHETHER THE DUTY CYCLES OR THE COMPARE VALUE
								2-USE THE CALLBACK_FUNC TO ASSIGN THE FUNCTION THAT YOU WANTED TO BE CALLED WHEN THE INTERRUPT IS GENERATED IN CASE OF THE COMPARE MATCH MODE OR NORMAL MODE
								3-FINALLY USE THE TIMER0 INITIALIZING TO CHOOSE THE MODE AND THE PRESCALER AND TO ACTIVATE THE INTERRUPT FLAG ATLAST
								
								
								OTHER FUNCTIONS:
								-YOU CAN SHUT DOWN THE TIMER BY USING THE TIMER0_SHUTDOWN FUNCTION "THE NAME SPEAKS ABOUT ITSELF XD"
								-IF YOU WANT TO READ THE VALUE THAT THE TIMER REACHED YOU CAN USE THE TIMER0_READVALUE.*/



									/************************************************************************/
									/*                              INCLUDES                                */
									/************************************************************************/
									
#include "DATA_TYPES.h"
#include "LBIT_Math.h"
#include "TIMER_INTERFACE.h"
#include "TIMER_PRIVATE.h"
#include "MDIO_INTERFACE.h"
									/************************************************************************/
									/*								GLOBAL POINTERS      AND VARIABLES      */
									/************************************************************************/
									
static void (*NORM_PTR)(void);											//A POINTER TO FUNCTION FOR NORMAL MODE																		
static void (*COMP_PTR)(void);											//A POINTER TO FUNCTION FOR COMPARE MATCH MODE

static u8_t prescaler_value;											//A GLOBAL VARIABLE USED TO CARRY THE PRESCALE VALUE
									/************************************************************************/
									/*							TIMER0 PROGRAM                              */
									/************************************************************************/
									
void TIMER0_INITIALIZE(u8_t timer_mode,u8_t prescale_value)
{
	/*SETTING THE PRESCALE VALUE PASSED TO THE FUNCTION TO A STATIC GLOBAL VARIABLE*/
	prescaler_value=prescale_value;
	
	/*CHOOSING THE MODE FOR THE TIMER*/
	switch(timer_mode)
	{
		case NORMAL_TIMER :
		{
			/*SETTING THE TIMER MODE TO NORMAL*/
			CLEAR_BIT(TIMER_TCCR0,WGM00);
			CLEAR_BIT(TIMER_TCCR0,WGM01);
			
			/*DISCONNECTING THE OC0 PIN IN NORMAL MODE*/
			CLEAR_BIT(TIMER_TCCR0,COM00);
			CLEAR_BIT(TIMER_TCCR0,COM01);
			break;
		}
	

		case PWM_PHASE :
		{
			/*SETTING THE TIMER MODE  TO PWM PHASE CORRECT {OPTIONAL TO BE USED IN THIS DRIVER}*/
			SET_BIT(TIMER_TCCR0,WGM00);
			CLEAR_BIT(TIMER_TCCR0,WGM01);

			break;
		}
		case COMP_MATCH :
		{
			/*SETTING THE TIMER MODE TO COMPARE MATCH MODE*/
			CLEAR_BIT(TIMER_TCCR0,WGM00);
			SET_BIT(TIMER_TCCR0,WGM01);
			
			break;
		}
		case PWM_FAST:
		{
			/*SETTING THE TIMER MODE  TO PWM FAST {OPTIONAL TO BE USED IN THIS DRIVER}*/
			SET_BIT(TIMER_TCCR0,WGM00);
			SET_BIT(TIMER_TCCR0,WGM01);
		}
		default:
		{
			/*do nothing*/
			break;
		}
	}
		
	/*ENABLING THE GLOBAL INTERRUPT FLAG FOR ANY INTERRUPT IN TIMER0*/
	SET_BIT(SREG,I);
	
	/*SETTING THE OC0 PIN TO OUTPUT VALUE*/
	MDIO_SETPIN_STATUS(PORTB,PIN3,OUTPUT);
	
	/*SETTING THE PRESCALER VALUE*/
	TIMER_TCCR0|=(prescaler_value);					


}

void TIMER0_TURNOFF(u8_t reset_mode)
{ 
	/*THIS MODE IS TO RESET THE COUNTER VALUE TO ZERO*/
	if (reset_mode==TIMER_RESET)
	{
		TIMER_TCNT0=0;
	}
	/*CLEARING THE TCCR0 REGISTER ESPECIALLY CS00-->CS02 BITS TO STOP THE TIMER*/
	else if (reset_mode==TIMER_STOP)
	{
		TIMER_TCCR0=0;
	}

}

void TIMER0_READVALUE(u8_t* READVALUE)
{
	*READVALUE=TIMER_TCNT0;
}

void TIMER0_PWM_SETUP(u8_t pwm_mode,u8_t duty_value)	
{
		if (pwm_mode ==PWM_NON_INVERT)							
		{
			/*SETTING THE PWM TO NON INVERTING MODE*/
			CLEAR_BIT(TIMER_TCCR0,COM00);
			SET_BIT(TIMER_TCCR0,COM01);
				
			/*SETTING THE DUTY CYCLE FOR THE OUTPUT SIGNAL*/
			TIMER_OCR0=duty_value;
		}
			
		/*SETTING THE PWM TO  INVERTING MODE*/
		else if (pwm_mode ==PWM_INVERT)
		{		
			/*SETTING THE PWM TO  INVERTING MODE*/
			SET_BIT(TIMER_TCCR0,COM00);
			SET_BIT(TIMER_TCCR0,COM01);
			/*SETTING THE DUTY CYCLE FOR THE OUTPUT SIGNAL {AS THE MAX VALUE IS 256*/
			TIMER_OCR0=255-duty_value;
		}
		else
		{
			/*do nothing*/
		}		
}					

void TIMER0_COMPMATCH_SETUP(u8_t compare_mode, u8_t compare_value)
{
			/*ENABLING THE TIMER0 COMPARE MATCH INTERRUPT*/
			SET_BIT(TIMER_TIMSK,OCIE0);
			
			/*SETTING OC0 TO BE TOGGLED ON COMPARE MODE*/
			if (compare_mode==OC0_TOGGLE)
			{
				SET_BIT(TIMER_TCCR0,COM00);
				CLEAR_BIT(TIMER_TCCR0,COM01);
			}
			
			/*SETTING OC0 TO BE CLEARE ON COMPARE MODE*/
			else if (compare_mode==OC0_CLEAR)							
			{
				CLEAR_BIT(TIMER_TCCR0,COM00);
				SET_BIT(TIMER_TCCR0,COM01);
			}
			
			/*SETTING OC0 TO BE SET ON COMPARE MODE*/
			else if (COMP_MATCH==OC0_SET)
			{
				SET_BIT(TIMER_TCCR0,COM00);
				SET_BIT(TIMER_TCCR0,COM01);
			}
			
			/*SETTING THE COMPARE VALUE TO TIMER0 TCNT REGISTER*/
			TIMER_OCR0=compare_value;
}

void TIMER0_CALLBACK_FUNC( u8_t timer_mode,void (*funcptr)(void))
{
	if (timer_mode==NORMAL_TIMER)
	{
		/*ENABLING THE TIMER0 INTERRUPT INITIALIZING*/
		SET_BIT(TIMER_TIMSK,TOIE0);
		
		NORM_PTR=funcptr;
	}
	else if (timer_mode==COMP_MATCH)
	{
		COMP_PTR=funcptr;
	}
	else
	{
		/*do nothing*/
	}
}

void TIMER0_delay(u16_t time_value)
{
	 u16_t delay_counter=0;
	/*SETTING THE TIMER MODE TO NORMAL MODE*/
	CLEAR_BIT(TIMER_TCCR0,WGM00);
	CLEAR_BIT(TIMER_TCCR0,WGM01);
		
	/*DISCONNECTING THE OC0 PIN IN NORMAL MODE*/
	CLEAR_BIT(TIMER_TCCR0,COM00);
	CLEAR_BIT(TIMER_TCCR0,COM01);
	
	/*SETTING THE PRESCALER OF THE TIMER AND INITIALIZING IT*/
	TIMER_TCCR0|=(_64_PRESCALE);	
	
	while(time_value>=(0.5*delay_counter))
	{
		/*CHECKING THE VALUE OF THE TIMER*/
		if(TIMER_TCNT0>=250)
		{
			/*INCREMENTING THE DELAY COUNTER EVERY 2 MILLI SECONDS*/
			delay_counter++;
		}
	}
	/*RESETING THE DELAY COUNTER*/
	delay_counter=0;
	
	/*TURNING OFF THE TIMER*/
	TIMER_TCCR0=0;
}



									/************************************************************************/
									/*							ISR IMPLEMENTATION                          */
									/************************************************************************/

void __vector_10 (void) __attribute__ ((signal));
void __vector_10 (void)
{
	COMP_PTR();					//CALLING THE INTERRUPT FUNCTION FOR THE COMPARE MATCH MODE
}
void __vector_11 (void)	__attribute__((signal));
void __vector_11 (void)
{
	NORM_PTR();					//CALLING THE INTERRUPT FUNCTION FOR THE NORMAL MODE

}
