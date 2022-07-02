


#ifndef PROJECT_INTERFACING_H_
#define PROJECT_INTERFACING_H_

/************************************************************************/
/*							MACROS DEFINITIONS						    */
/************************************************************************/
#define  idle_state			0
#define  start_state		1
#define	 stop_state			2

#define Z_AXIS_M			1
#define BASE_M				2
#define FEED_M				3
#define Y_AXIS_M			4

#define relay_1				1
#define relay_2				2
#define relay_3				3
#define relay_4				4
#define relay_5				5
#define relay_6				6




/************************************************************************/
/*							FUNCTION PROTOTYPE							*/
/************************************************************************/
void keys_init();
void relay_ACTIVATE(u8_t);
void motor_init(u8_t,u8_t);




#endif /* PROJECT_INTERFACING_H_ */