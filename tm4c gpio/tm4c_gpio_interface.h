/*
 * tm4c_gpio_interface.h
 *
 *  Created on: Mar 1, 2022
 *      Author: mohye
 */

#ifndef TM4C_GPIO_INTERFACE_H_
#define TM4C_GPIO_INTERFACE_H_

/*INTERFACING MACROS*/
/*values*/
#define HIGH 1
#define LOW 0

/*mode*/
#define INPUT_FLOAT 0
#define INPUT_PULLUP 1
#define OUTPUT 2

/*disabling mode*/
#define P0RT 0
#define PIN 1

/*ports*/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

/*PINS*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

/*FUNCTIONS PROTOTYPES*/

void Set_Pin_Mode(uint16_t Port, uint16_t Pin, uint16_t Mode); // to set a the mode of the pin in a specific port

void Set_Pin_Value(uint16_t Port, uint16_t Pin, uint16_t Value); // to assign the value of the pin in a specific port

int Read_Pin_Value(uint16_t Port, uint16_t Pin, uint16_t Value); // to read whether the pin value is high or low and return it

void Disable_Pin(uint16_t port, uint16_t pin); // to disable the pin from the port.

void Disable_Port(uint16_t port); // to disable the port.
#endif                            /* TM4C_GPIO_INTERFACE_H_ */
