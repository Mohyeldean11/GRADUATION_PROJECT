/************************************************************************/
/* Name: TIMER_PROGRAM.c                                                */
/* Author: MOHIEE ELDEAN                                                */
/* Version: V1.0                                                        */
/* Usage: This file contains logical implementations of TIMER1 Module   */
/************************************************************************/

#include "DATA_TYPES.h"
#include "LBIT_Math.h"
#include "MDIO_INTERFACE.h"
#include "TIMER1_PRIVATE.h"
#include "TIMER1_INTERFACE.h"

									/************************************************************************/
									/*						GLOBAL POINTERS                                 */
									/************************************************************************/
void(*ISR_PTRS[4])(void);
//{void(*ICU_PTR)(void),void(*ICU_PTR)(),void(*COMPA_PTR)(),void(*COMPB_PTR)(),void(*TOV1_PTR)()};



								/************************************************************************/
								/*					FUNCTIONS LOGICAL IMPLEMENTATIONS                   */
								/************************************************************************/

void TIMER1_NORMARL_MODE(u8_t prescaler_value)
{
	/*RESETING THE TIMER CONTROL REGISTERS*/
	TIMER1_TCCR1A=0;
	TIMER1_TCCR1B=0;		
	/*SETTING THE PRESCALE_VALUE*/
	TIMER1_TCCR1B|=prescaler_value;
}

void TIMER1_COMPMATCH_SETUP(u8_t compare_mode,u8_t pin_selection,u16_t compare_value,u8_t prescaler_value)
{
	/*RESETING THE TIMER CONTROL REGISTERS*/
	TIMER1_TCCR1A=0;
	TIMER1_TCCR1B=0;
	
	/*SETTING THE OC1A/OC1B TO OUTPUT VALUES*/
	MDIO_SETPIN_STATUS(PORTD,PIN4|PIN5,OUTPUT);
	switch (compare_mode)
	{
		case CTC_TOGGLE:
		{
			/*SETTING THE OC1A/OC1B TO BE TOGGLED ON COMPARE*/
			TIMER1_TCCR1A|=(0b01010000);
			break;
		}
		case CTC_CLEAR:
		{
			/*SETTING THE OC1A/OC1B TO BE CLEAR ON COMPARE (LOW OUTPUT)*/
			TIMER1_TCCR1A|=(0b10100000);
			break;
		}
		case CTC_SET:
		{
			/*SETTING THE OC1A/OC1B TO BE SET ON COMPARE (HIGH OUTPUT)*/
			TIMER1_TCCR1A|=(0b11110000);
			break;
		}
	}
		/*SETTING THE COMPARE VALUE FROM THE OCR1*/
		SET_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
		switch(pin_selection)
		{
			case OCR1A :
			{
				/*ASSIGINING THE COMPARE VALUE TO OCR1A*/
				TIMER1_OCR1A=compare_value;
				break;
			}
			case OCR1B :
			{
				/*ASSIGINING THE COMPARE VALUE TO OCR1B*/
				TIMER1_OCR1B=compare_value;
				break;
			}
			case OCR1:
			{
				/*ASSINGNING THE COMPARE VALUE TO BOTH REGISTERS TO GET OUTPUT ON BOTH PINS*/
				TIMER1_OCR1A=compare_value;
				TIMER1_OCR1B=compare_value;
				break;
			}
		}
	/*SETTING THE PRESCALER FOR THE CTC MODE*/	
	TIMER1_TCCR1B|=prescaler_value; 
}


void TIMER1_PWMFAST_SETUP(u8_t pwm_inverting_mode,u8_t fast_pwm_mode,u16_t duty_cycle,u8_t prescaler_value)
{
	/*RESETING THE TIMER CONTROL REGISTERS*/
	TIMER1_TCCR1A=0;
	TIMER1_TCCR1B=0;
	
	/*SETTING THE OCR1A PIN TO OUTPUT FOR THE PWM SIGNAL*/
	MDIO_SETPIN_STATUS(PORTD,PIN5,OUTPUT);
	
	/*SWITCHING OVER THE INVERTING MODES OF THE TIMERS*/
	switch (pwm_inverting_mode)
	{
		/*SETTING THE PWM MODE TO NON INVERTING*/
		case PWM_NON_INVERT:
		{
			TIMER1_TCCR1A|=(0b10100000);
			break;
		}
		/*SETTING THE PWM MODE TO NON INVERTING*/
		case PWM_INVERT:
		{
			TIMER1_TCCR1A|=(0b11110000);
			break;
		}
	}
	/*SWITCHING OVER THE FAST PWM MODES*/
	switch (fast_pwm_mode)
	{
		/*INCASE OF PWM 8 BITS*/
		case FAST_PWM8:
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			break;
		}
		case FAST_PWM9:
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			break;
		}
		case FAST_PWM10:
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			break;
		}
		case FAST_PWM16:
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM13);
			/*SETTING THE DUTY CYCLE TO THE OCRA REGISTER*/
			TIMER1_OCR1A=duty_cycle;
			break;
		}		
	}
	/*SETTING THE PRESCALER VALUE*/
	TIMER1_TCCR1B|=prescaler_value;
}


void TIMER1_PWMPHASE_SETUP(u8_t pwm_inverting_mode,u8_t phase_correct_mode,u16_t duty_cycle,u8_t prescaler_value)
{
	/*RESETING THE TIMER CONTROL REGISTERS*/
	TIMER1_TCCR1A=0;
	TIMER1_TCCR1B=0;
	
	/*SETTING THE OCR1A PIN TO OUTPUT FOR THE PWM SIGNAL*/
	MDIO_SETPIN_STATUS(PORTD,PIN5,OUTPUT);
	
	/*SWITCHING OVER THE INVERTING MODES OF THE TIMERS*/
	switch (pwm_inverting_mode)
	{
		/*SETTING THE PWM MODE TO NON INVERTING*/
		case PWM_NON_INVERT:
		{
			TIMER1_TCCR1A|=(0b10100000);
			break;
		}
		/*SETTING THE PWM MODE TO NON INVERTING*/
		case PWM_INVERT:
		{
			TIMER1_TCCR1A|=(0b11110000);
			break;
		}
	}
	/*SWITCHING OVER THE PHASE CORRECT MODE*/
	switch (phase_correct_mode)
	{
		case PHASE_PWM8:
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			break;
		}
		case PHASE_PWM9:
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
			break;
		}
		case PHASE_PWM10:
		{
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			break;
		}
		case PHASE_PWM16:
		{
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM13);
			/*SETTING THE VALUE OF THE DUTY CYCLE TO THE OCR1A REGISTER*/
			TIMER1_OCR1A=duty_cycle;
			break;
		}
	}
	/*SETTING THE PRESCALER VALUE*/
	TIMER1_TCCR1B|=prescaler_value;
}


void timer1_PWMPHASE_FREQUENCY(u8_t pwm_inverting_mode,u16_t duty_cycle,u8_t prescaler_value)
{
	/*RESETING THE TIMER CONTROL REGISTERS*/
	TIMER1_TCCR1A=0;
	TIMER1_TCCR1B=0;
	
	/*SETTING THE OCR1A PIN TO OUTPUT FOR THE PWM SIGNAL*/
	MDIO_SETPIN_STATUS(PORTD,PIN5,OUTPUT);
	
	/*SWITCHING OVER THE INVERTING MODES OF THE TIMERS*/
	switch (pwm_inverting_mode)
	{
		/*SETTING THE PWM MODE TO NON INVERTING*/
		case PWM_NON_INVERT:
		{
			TIMER1_TCCR1A|=(0b10100000);
			break;
		}
		/*SETTING THE PWM MODE TO NON INVERTING*/
		case PWM_INVERT:
		{
			TIMER1_TCCR1A|=(0b11110000);
			break;
		}
	}
	/*SETTING THE PHASE CORRECT AND FREQUENCY PWM (COUNT UP AND DOWN MODE)*/
	SET_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
	SET_BIT(TIMER1_TCCR1B,TIMER1_WGM13);
	
	/*SETTING THE DUTY CYCLE FOR PWM*/
	TIMER1_OCR1A=duty_cycle;
	
	/*SETTING THE PRESCALER VALUE*/
	TIMER1_TCCR1B|=prescaler_value;
}


int TIMER1_READVALUE(void)
{
	/*CREATING A VALUE TO CARRY THE TIMER COUNTS*/
	u16_t tick_value=0;
	
	/*GETTING THE TICK TIME FROM THE COUNTER REGISTER*/
	tick_value=TIMER1_TCNT1;
	
	/*RETURNING THE TIMER VALUE*/
	return tick_value;	
}


void TIMER1_TURNOFF(u8_t reset_mode)
{
	if(reset_mode==TIMER_RESET)
	{
	/*RESETING THE COUNTER REGISTER*/
		TIMER1_TCNT1=0;
	}
	else if(reset_mode==TIMER_STOP)
	{
		/*RESETING THE TIMER CONTROL REGISTERS*/
		TIMER1_TCCR1A=0;
		TIMER1_TCCR1B=0;
	
	/*RESETING THE COUNTER REGISTER*/
		TIMER1_TCNT1=0;
	}
}


void TIMER1_CALLBACK_FUNC(void(*funcptr)(void),u8_t timer_ISR)
{
	/*ACTIVATING THE GLOBAL INTERRUPT*/
	SET_BIT(SREG,I);
	/*SWITCHING BETWEEN THE GLOBAL POINTERS AND PASSING THE POINTER TO FUNCTION TO THE SPECIFIC POINTER FOR ISR*/
	/*ACTIVATING THE SPECIFIC INTERRUPT FOR THE ISR*/
	switch(timer_ISR)
	{
		case TIMER1_ICU_I :
		{
			SET_BIT(TIMER1_TIMSK,TIMER1_TICIE1);
			ISR_PTRS[TIMER1_ICU_I]=funcptr;
			break;
		}
		case TIMER1_COMPA_I :
		{
			
			SET_BIT(TIMER1_TIMSK,TIMER1_OCIE1A);
			ISR_PTRS[TIMER1_COMPA_I]=funcptr;
			break;
		}
		case TIMER1_COMPB_I :
		{
			SET_BIT(TIMER1_TIMSK,TIMER1_OCIE1B);
			ISR_PTRS[TIMER1_COMPB_I]=funcptr;
			break;
		}
		case TIMER1_TOV_I :
		{
			SET_BIT(TIMER1_TIMSK,TIMER1_TOIE1);
			ISR_PTRS[TIMER1_TOV_I]=funcptr;
			break;
		}
	}	
}



void TIMER1_ICU(u8_t ICU_EDGE,u8_t ICU_TYPE,u8_t prescaler_value)																				
{
	/*RESETING THE TIMER CONTROL REGISTERS*/
	TIMER1_TCCR1A=0;
	TIMER1_TCCR1B=0;
	
	/*ASSIGNING THE TRIGGERING EDGE TYPE*/
	if (ICU_EDGE==ICU_RISING)
	{
		SET_BIT(TIMER1_TCCR1B,TIMER1_ICES1);
	}
	else if(ICU_EDGE==ICU_FALLING)
	{
		CLEAR_BIT(TIMER1_TCCR1B,TIMER1_ICES1);
	}
	/*SWITCHING OVER THE ICU MODES*/
	switch(ICU_TYPE)
	{
		case ICU_NORMAL:
		{
			/*do nothing*/
			break;
		}
		case ICU_FASTPWM:
		{
			CLEAR_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
			SET_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM13);
			break;
		}
		case ICU_PHASEPWM:
		{
			CLEAR_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
			CLEAR_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM13);		
			break;
		}
		case ICU_PASE_FREQPWM:
		{
			CLEAR_BIT(TIMER1_TCCR1A,TIMER1_WGM10);
			CLEAR_BIT(TIMER1_TCCR1A,TIMER1_WGM11);
			CLEAR_BIT(TIMER1_TCCR1B,TIMER1_WGM12);
			SET_BIT(TIMER1_TCCR1A,TIMER1_WGM13);
			break;
		}
	}
	
	/*SETTING THE PRESCALER VALUE*/
	TIMER1_TCCR1B|=prescaler_value;
}

void ICU_SET_EDGE(u8_t ICU_EDGE)
{
	/*ASSIGNING THE TRIGGERING EDGE TYPE*/
	if (ICU_EDGE==ICU_RISING)
	{
		SET_BIT(TIMER1_TCCR1B,TIMER1_ICES1);
	}
	else if(ICU_EDGE==ICU_FALLING)
	{
		CLEAR_BIT(TIMER1_TCCR1B,TIMER1_ICES1);
	}
}


int ICU_READ(void)
{
	/*CREATING A VALUE TO CARRY THE ICU COUNTS*/
	u16_t ICU_READING=0;

	/*GETTING THE TICK TIME FROM THE ICU REGISTER*/
	ICU_READING=ICU_ICR1;
	
	/*RETURNING THE ICU VALUE*/
	return ICU_READING;
}																												

								/************************************************************************/
								/*					    ISRS' IMPLEMENTATION					        */
								/************************************************************************/
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	ISR_PTRS[TIMER1_ICU_I]();
}


void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	ISR_PTRS[TIMER1_COMPA_I]();
}

void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	ISR_PTRS[TIMER1_COMPB_I]();
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	ISR_PTRS[TIMER1_TOV_I]();
}