/************************************************************************/
/* Name: TIMER_INTERFACE.h                                              */
/* Author: MOHY ELDEAN                                                  */
/* Version: V1.0                                                        */
/* Usage: This file contains INTERFACING  of TIMER Module				*/
/************************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

									/************************************************************************/
									/*						INTERFACING MACROS                              */
									/************************************************************************/
/*TIMER MODES*/								
#define NORMAL_TIMER			1
#define PWM_PHASE				2
#define COMP_MATCH				3
#define PWM_FAST				4

/*COMPARE MODES IN TIMER FOR OC0 PIN*/
#define OC0_dISC				0						//DISCONNECTING OC0 INCASE OF NORMAL MODE
#define OC0_TOGGLE				1						//RESERVED INCASE OF THE PWM MODE 	
#define OC0_CLEAR				2						//NON-INVERTING MODE INCASE OF THE  PWM MODE
#define OC0_SET					3						//	  INVERTING	MODE INCASE OF THE  PWM MODE

/*PWM MODES IN TIMER FOR OC0 PIN*/
#define PWM_NON_INVERT			2						//OC0 CLEAR MODE INCASE OF THE  COMPAR MATCH MODE
#define PWM_INVERT				3						//OC0 SET MODE INCASE OF THE  COMPAR MATCH MODE
				 

/*PRESCALE VALUES*/
#define NO_PRESCALE				1
#define _8_PRESCALE				2	
#define _64_PRESCALE			3
#define _256_PRESCALE			4
#define _1024_PRESCALE			5
#define _EXTCLK_FALLING			6					    //COUNTING ON FALLING EDGES ON EVENTS ON T0 PIN
#define _EXTCLK_RISING			7						//COUNTING ON RISING EDGES ON EVENTS ON T0 PIN
							
/*RESET MODES*/
#define TIMER_RESET				1
#define TIMER_STOP				2
									
									/************************************************************************/
									/*                      FUNCTION PROTOTYPES                             */
									/************************************************************************/
									
									
void TIMER0_INITIALIZE(u8_t timer_mode,u8_t prescale_value);										//USED TO INITIALIZE THE TIMER0 AFTER SETTING ALL THE VALUES OF THE TIMER

void TIMER0_TURNOFF(u8_t reset_mode);																//USED TO SHUT DOWN TIMER0

void TIMER0_READVALUE(u8_t* READVALUE);																//USED TO KNOW THE VALUE THAT THE TIMER0 COUNTED

void TIMER0_PWM_SETUP(u8_t pwm_mode,u8_t duty_value);												//USED TO SET UP THE PWM MODE OF TIMER0 BEFORE INITIALIZING IT

void TIMER0_COMPMATCH_SETUP(u8_t compare_mode, u8_t compare_value);									//USED TO SET UP THE COMPARE MATCH MODE OF TIMER0 BEFORE INITIALIZING IT

void TIMER0_CALLBACK_FUNC( u8_t timer_mode,void (*funcptr)(void));									// A FUNCTION TO PASS THE INTERRUPT FUNCTION FOR TIMER0

void TIMER0_delay(u16_t time_value);																//A TIMER TO MAKE A DELAY (BUSY WAITING)
#endif /* TIMER_INTERFACE_H_ */	