#include <avr/io.h>
#include "DATA_TYPES.h"
#include "LBIT_Math.h"
#include "MDIO_INTERFACE.h"
#include "TIMER_INTERFACE.h"
#include "TIMER1_INTERFACE.h"
#include "PROJECT_INTERFACING.h"
						/************************************************************************/
						/*						global variables								*/
						/************************************************************************/
						
u8_t Z_AXIS_UP , Z_AXIS_DOWN ,BASE_RIGHT , BASE_LEFT ,FEED_UP ,FEED_DOWN,Y_AXIS_LEFT,Y_AXIS_RIGHT=0;


/************************************************************************/
/*				FUNCTIONS DEFINITIONS                                   */
/************************************************************************/


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
