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

/*COMPARE MODES IN TIMER FOR OC1A/OC1B PINS*/
#define	CTC_dISC				0						//DISCONNECTING OC1 INCASE OF NORMAL MODE
#define	CTC_TOGGLE				1						//RESERVED INCASE OF THE PWM MODE 	
#define	CTC_CLEAR				2						//NON-INVERTING MODE INCASE OF THE  PWM MODE
#define	CTC_SET					3						//INVERTING	MODE INCASE OF THE  PWM MODE


/*PIN SELECTION FOR COMPARE MODE*/
#define OCR1A					1						//COMPARING FROM OCR1A IN THE CTC MODE
#define OCR1B					2						//COMPARING FROM OCR1B IN THE CTC MODE
#define OCR1					3						//COMPARING FROM THE SAME TWO PINS


/*PWM MODES IN TIMER*/
#define PWM_NON_INVERT			2						//OC1 CLEAR MODE INCASE OF THE  COMPAR MATCH MODE
#define PWM_INVERT				3						//OC1 SET MODE INCASE OF THE  COMPAR MATCH MODE

				 
/*FAST PWM MODES*/
#define FAST_PWM8				1						//SETTING THE FAST PWM TO 8 BIT COMPARE
#define FAST_PWM9				2						//SETTING THE FAST PWM TO 9 BIT COMPARE
#define FAST_PWM10				3						//SETTING THE FAST PWM TO 10 BIT COMPARE
#define FAST_PWM16				4						//SETTING THE FAST PWM TO 16 BIT VARIABLE COMPARE


/*PHASE CORRECT MODES*/
#define PHASE_PWM8				1						//SETTING THE PHASE CORRECT PWM TO 8 BIT COMPARE
#define PHASE_PWM9				2						//SETTING THE PHASE CORRECT PWM TO 9 BIT COMPARE
#define PHASE_PWM10				3						//SETTING THE PHASE CORRECT PWM TO 10 BIT COMPARE
#define PHASE_PWM16				4						//SETTING THE PHASE CORRECT PWM TO 16 BIT VARIABLE COMPARE



/*PRESCALE VALUES*/
#define NO_PRESCALE				1
#define _8_PRESCALE				2	
#define _64_PRESCALE			3
#define _256_PRESCALE			4
#define _1024_PRESCALE			5
#define _EXTCLK_FALLING			6					    //COUNTING ON FALLING EDGES ON EVENTS ON T0 PIN
#define _EXTCLK_RISING			7						//COUNTING ON RISING EDGES ON EVENTS ON T0 PIN

/*ICU TYPES*/
#define ICU_NORMAL				1
#define ICU_FASTPWM				2
#define ICU_PHASEPWM			3
#define ICU_PASE_FREQPWM		4

/*ICU EDGES*/
#define ICU_RISING				1
#define ICU_FALLING				2
							
/*RESET MODES*/
#define TIMER_RESET				1
#define TIMER_STOP				2

/*TIMER1 ISRS*/
#define TIMER1_ICU_I			0
#define TIMER1_COMPA_I			1
#define TIMER1_COMPB_I			2
#define TIMER1_TOV_I			3



									/************************************************************************/
									/*                      FUNCTION PROTOTYPES                             */
									/************************************************************************/
									
									
void TIMER1_NORMARL_MODE(u8_t prescaler_value);																					//USED TO INITIALIZE THE TIMER1 IN NORMAL MODE

void TIMER1_TURNOFF(u8_t reset_mode);																							//USED TO SHUT DOWN TIMER1

void TIMER1_PWMFAST_SETUP(u8_t pwm_inverting_mode,u8_t fast_pwm_mode,u16_t duty_cycle,u8_t prescaler_value);					//USED TO SETUP THE FAST PWM MODE

void TIMER1_PWMPHASE_SETUP(u8_t pwm_inverting_mode,u8_t phase_correct_mode,u16_t duty_cycle,u8_t prescaler_value);				//USED TO SETUP THE PHASE CORRECT MODE

void timer1_PWMPHASE_FREQUENCY(u8_t pwm_inverting_mode,u16_t duty_cycle,u8_t prescaler_value);									//USED TO SETUP THE PHASE CORRECT AND FREQUENCY MODE (COUNT UP AND DOWN)			

void TIMER1_COMPMATCH_SETUP(u8_t compare_mode,u8_t pin_selection,u16_t compare_value,u8_t prescaler_value);						//USED TO SETUP THE CTC MODE

void TIMER1_CALLBACK_FUNC(void (*funcptr)(void),u8_t timer_ISR);																//USED TO PASS THE INTERRUPT FUNCTION FOR TIMER1

void TIMER1_ICU(u8_t ICU_EDGE,u8_t ICU_TYPE,u8_t prescaler_value);																//USED TO ACTIVATE THE ICU OF TIMER1

void ICU_SET_EDGE(u8_t ICU_EDGE);																								//USED TO ASSIGN THE TRIGGERING EDGE FOR THE ICU

int ICU_READ(void);																												//USED TO READ THE VALUE OF THE ICU REGISTER		

int TIMER1_READVALUE(void);																										//USED TO KNOW THE VALUE THAT THE TIMER1 COUNTED


#endif /* TIMER_INTERFACE_H_ */	

