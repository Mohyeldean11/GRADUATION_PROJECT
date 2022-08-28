/************************************************************************/
/* Name: TIMER_PRIVATE.h                                                */
/* Author: MOHY ELDEAN                                                  */
/* Version: V1.0                                                        */
/* Usage: This file contains private information of TIMER1 Module       */
/************************************************************************/



#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define  SREG					(*(volatile u8_t*)(0x5F))
#define   I									7

#define   ICU_ICR1				(*(volatile u16_t*)(0x46))


#define	 TIMER1_OCR1B			(*(volatile u16_t*)(0x48))
#define  TIMER1_OCR1A			(*(volatile u16_t*)(0x4A))
#define  TIMER1_TCNT1			(*(volatile u16_t*)(0x4C))



#define  TIMER1_TCCR1B			(*(volatile u8_t*)(0x4E))
#define  TIMER1_ICNC1					   7
#define  TIMER1_ICES1					   6

#define  TIMER1_WGM13					   4
#define  TIMER1_WGM12					   3
#define  TIMER1_CS12					   2
#define  TIMER1_CS11					   1
#define  TIMER1_CS10					   0
			
#define	 TIMER1_TCCR1A			(*(volatile u8_t*)(0x4F))
#define  TIMER1_COM1A1					   7
#define  TIMER1_COM1A0					   6
#define  TIMER1_COM1B1					   5
#define  TIMER1_COM1B0					   4
#define  TIMER1_FOC1A					   3
#define  TIMER1_FOC1B					   2
#define  TIMER1_WGM11					   1
#define  TIMER1_WGM10					   0


#define TIMER1_TIMSK			(*(volatile u8_t*)(0x59))
#define TIMER1_TICIE1					   5
#define TIMER1_OCIE1A					   4
#define TIMER1_OCIE1B					   3
#define TIMER1_TOIE1					   2


#define TIMER1_TIFR				(*(volatile u8_t*)(0x58))
#define TIMER1_ICF1						   5
#define TIMER1_OCF1A					   4
#define TIMER1_OCF1B					   3
#define TIMER1_TOV1						   2

#endif /* TIMER1_PRIVATE_H_ */