#include <avr/io.h>
#include "DATA_TYPES.h"
#include "LBIT_Math.h"
#include "MDIO_INTERFACE.h"
#include "TIMER_INTERFACE.h"
#include "PROJECT_INTERFACING.h"


						/************************************************************************/
						/*						global variables								*/
						/************************************************************************/
						
u8_t Z_AXIS_UP , Z_AXIS_DOWN ,BASE_RIGHT , BASE_LEFT ,FEED_UP ,FEED_DOWN,Y_AXIS_LEFT,Y_AXIS_RIGHT=0;



void PWM_Init();


int main(void)
{
	
	MDIO_SETPIN_STATUS(PORTB,PIN1|PIN3,OUTPUT);      //SETTING THE OC0 AND DIRECTION FOR CYTRON
	
	TIMER0_INITIALIZE(PWM_PHASE,NO_PRESCALE);		//OC0 PWM
	
	PWM_Init();								// OC2 PWM
	
	

	motor_init(idle_state,BASE_M);
	OCR2=255*.21;
	TIMER0_INITIALIZE(PWM_PHASE,NO_PRESCALE);
	TIMER0_PWM_SETUP(PWM_NON_INVERT,255*.7);
	while (1)
	{
					
		/*INITIALIZING THE PWM SIGNALS*/					
		TIMER0_PWM_SETUP(PWM_NON_INVERT,255*.7);
	
		/*GETTING THE VALUES OF THE SWITCHES*/
		keys_init();
		
		if (Z_AXIS_UP==1)
		{
			motor_init(start_state,Z_AXIS_M);
			MDIO_SETPIN_VALUE(PORTB,PIN1,HIGH);
		}
		if (Z_AXIS_DOWN==1)
		{
			motor_init(start_state,Z_AXIS_M);
			MDIO_SETPIN_VALUE(PORTB,PIN1,LOW);
		}
		if(BASE_RIGHT==1)
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
		}
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
	/*KEYS VALUES*/
	Z_AXIS_UP=MDIO_GETPIN_VALUE(PORTA,PIN0);
	Z_AXIS_DOWN=MDIO_GETPIN_VALUE(PORTA,PIN1);
	
	BASE_RIGHT=MDIO_GETPIN_VALUE(PORTA,PIN2);
	BASE_LEFT=MDIO_GETPIN_VALUE(PORTA,PIN3);
	
	FEED_UP=MDIO_GETPIN_VALUE(PORTA,PIN4);
	FEED_DOWN=MDIO_GETPIN_VALUE(PORTA,PIN5);
	
	Y_AXIS_RIGHT=MDIO_GETPIN_VALUE(PORTA,PIN6);
	Y_AXIS_LEFT=MDIO_GETPIN_VALUE(PORTA,PIN7);
	
	
	
}

void relay_ACTIVATE(u8_t relay_numb)
{
	MDIO_SETPIN_STATUS(PORTC,PIN1|PIN2|PIN3|PIN4|PIN5|PIN6,OUTPUT);
	switch(relay_numb)
	{
		case relay_1:
		{
			MDIO_SETPIN_VALUE(PORTC,PIN1,HIGH);
			break;
		}
		case relay_2:
		{
			MDIO_SETPIN_VALUE(PORTC,PIN1,HIGH);
			break;

		}
		case relay_3:
		{
			MDIO_SETPIN_VALUE(PORTC,PIN3,HIGH);
			break;
		}
		case relay_4:
		{
			MDIO_SETPIN_VALUE(PORTC,PIN4,HIGH);
			break;
		}
		case relay_5:
		{
			MDIO_SETPIN_VALUE(PORTC,PIN5,HIGH);
			break;
		}
		case relay_6:
		{
			MDIO_SETPIN_VALUE(PORTC,PIN6,HIGH);
			break;
		}
	}
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
				MDIO_SETPIN_VALUE(PORTD,PIN5,LOW);
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
				MDIO_SETPIN_VALUE(PORTD,PIN5,LOW);
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
