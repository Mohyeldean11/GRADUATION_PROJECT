/************************************************************************/
/* Name: TIMER_PRIVATE.h                                                */
/* Author: MOHY ELDEAN                                                  */
/* Version: V1.0                                                        */
/* Usage: This file contains private information of TIMER Module        */
/************************************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

										/************************************************************************/
										/*                                  REGISTERS                           */
										/************************************************************************/
										
#define  TIMER_TCCR0		(*(volatile u8_t*)(0x53))

	/*bits for TCCR0*/
	#define  CS00			0
	#define  CS01			1
	#define  CS02			2
	#define  WGM01			3
	#define  COM00			4
	#define  COM01			5
	#define  WGM00			6
	#define  F0C0			7							

#define  TIMER_TCNT0		(*(volatile u8_t*)(0x52))

#define	 TIMER_OCR0			(*(volatile u8_t*)(0x5C))

#define  TIMER_TIMSK		(*(volatile u8_t*)(0x59))

	/*bits for TIMSK*/
	#define  TOIE0			0
	#define  OCIE0			1
	#define  TOIE1			2
	#define  OCIE1B			3
	#define  OCIE1A			4
	#define  TICIE1			5
	#define  TOIE2			6
	#define  OCIE2			7
	
	
#define  TIMER_TIFR			(*(volatile u8_t*)(0x58))

	/*bits for TIFR*/
	#define  TOV0			0
	#define  OCF0			1
	#define  TOV1			2
	#define  OCF1B			3
	#define  OCF1A			4
	#define  ICF1			5
	#define  TOV2			6
	#define  OCF2			7


#define  SREG				(*(volatile u8_t*)(0x5F))						//GENERAL REGISTER FOR INTERRUPTS
	/*bits for SREG*/
	#define I				7


#endif /* TIMER_PRIVATE_H_ */