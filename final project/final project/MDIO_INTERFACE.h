/************************************************************************/
/* Name: MDIO_INTERFACE.h                                               */
/* Author: MOHY ELDEAN                                                  */
/* Version: V1.0                                                        */
/* Usage: This file contains INTERFACING MACROS  of DIO Module          */
/************************************************************************/

/*HEADER GUARD*/
#ifndef _MDIO_INTERFACE_h_
#define _MDIO_INTERFACE_h_

/*interfacing macros*/


/*PORTS*/
#define PORTA   (0)
#define PORTB   (1)
#define PORTC   (2)
#define PORTD   (3)


/*PINS*/
#define PIN0    (0b00000001)
#define PIN1    (0b00000010)
#define PIN2    (0b00000100)
#define PIN3    (0b00001000)
#define PIN4    (0b00010000)
#define PIN5    (0b00100000)
#define PIN6    (0b01000000)
#define PIN7    (0b10000000)



/*PIN VALUE*/
#define HIGH    (1)
#define LOW     (0)



/*PINSTATUES*/
#define OUTPUT          (0)
#define INPUT_FLOAT     (1)
#define INPUT_PULLUP    (2)




/*prototypes for the DIO functions*/

/*FOR ENTERING THE STATUES OF THE PORTPIN -->>OUTPUT|INPUT_FLOAT|INPUT_PULLUP*/
void MDIO_SETPIN_STATUS(u8_t au8_port,u8_t au8_pin,u8_t au8_status);

/*FOR SETTING THE PIN VALUE TO--->>HIGH,LOW*/

void MDIO_SETPIN_VALUE(u8_t au8_port,u8_t au8_pin,u8_t au8_value);

/*FOR TOGGLEING THE PIN VALUE*/
void MDIO_TOGGLEPIN_VALUE(u8_t au8_port,u8_t au8_pin);

/*FOR KNOWING THE VALUE OF THE PIN*/
u8_t MDIO_GETPIN_VALUE(u8_t au8_port,u8_t au8_pin);


#endif
