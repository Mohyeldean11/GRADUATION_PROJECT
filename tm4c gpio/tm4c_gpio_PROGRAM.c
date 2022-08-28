/*
 * tm4c_gpio_PROGRAM.c
 *
 *  Created on: Mar 1, 2022
 *      Author: mohye
 */
#include <stdint.h>
#include "tm4c_gpio_interface.h"
#include "inc/tm4c123gh6pm.h"
#include "LBIT_Math.h"

void Set_Pin_Mode(uint16_t Port, uint16_t Pin, uint16_t Mode) /*to set a the mode of the pin in a specific port*/
{

    switch (Port)
    {
    case PORTA:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOA;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        switch (Mode)
        {
        case INPUT_FLOAT:
        {
            CLEAR_BIT(GPIO_PORTA_DIR_R, Pin); /*chosing the pin to be 0*/

            break;
        }
        case OUTPUT:
        {
            SET_BIT(GPIO_PORTA_DIR_R, Pin); /*chosing the pin to be 1*/

            break;
        }
        case INPUT_PULLUP:
        {
            SET_BIT(GPIO_PORTA_PUR_R, Pin); /*chosing the pin to be 1*/

            break;
        }
        }
        break;
    }
    case PORTB:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOB;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        switch (Mode)
        {
        case INPUT_FLOAT:
        {
            CLEAR_BIT(GPIO_PORTB_DIR_R, Pin); /*chosing the pin to be 0*/

            break;
        }
        case OUTPUT:
        {
            SET_BIT(GPIO_PORTB_DIR_R, Pin); /*chosing the pin to be 1*/

            break;
        }
        case INPUT_PULLUP:
        {
            SET_BIT(GPIO_PORTB_PUR_R, Pin); /*chosing the pin to be 1*/

            break;
        }
        }
        break;
    }

    case PORTC:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOC;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        switch (Mode)
        {
        case INPUT_FLOAT:
        {
            CLEAR_BIT(GPIO_PORTC_DIR_R, Pin); /*cho0sing the pin to be 0*/

            break;
        }
        case OUTPUT:
        {
            SET_BIT(GPIO_PORTC_DIR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        case INPUT_PULLUP:
        {
            SET_BIT(GPIO_PORTC_PUR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        }

        break;
    }

    case PORTD:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOD;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        switch (Mode)
        {
        case INPUT_FLOAT:
        {
            CLEAR_BIT(GPIO_PORTD_DIR_R, Pin); /*cho0sing the pin to be 0*/

            break;
        }
        case OUTPUT:
        {
            SET_BIT(GPIO_PORTD_DIR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        case INPUT_PULLUP:
        {
            SET_BIT(GPIO_PORTD_PUR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        }

        break;
    }

    case PORTE:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOE;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        switch (Mode)
        {
        case INPUT_FLOAT:
        {
            CLEAR_BIT(GPIO_PORTE_DIR_R, Pin); /*cho0sing the pin to be 0*/

            break;
        }
        case OUTPUT:
        {
            SET_BIT(GPIO_PORTE_DIR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        case INPUT_PULLUP:
        {
            SET_BIT(GPIO_PORTE_PUR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        }
        break;
    }

    case PORTF:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        switch (Mode)
        {
        case INPUT_FLOAT:
        {
            CLEAR_BIT(GPIO_PORTF_DIR_R, Pin); /*cho0sing the pin to be 0*/

            break;
        }
        case OUTPUT:
        {
            SET_BIT(GPIO_PORTF_DIR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        case INPUT_PULLUP:
        {
            SET_BIT(GPIO_PORTF_PUR_R, Pin); /*choosing the pin to be 1*/

            break;
        }
        }
    }
    break;
    }
}

void Set_Pin_Value(uint16_t Port, uint16_t Pin, uint16_t Value) // to assign the value of the pin in a specific port
{
    switch (Port)
    {
    case PORTA:
    {
        switch (Value)
        {
        case HIGH:
        {
            SET_BIT(GPIO_PORTA_DATA_R, Pin); /*choosing the pin to be HIGH value*/

            break;
        }
        case LOW:
        {
            CLEAR_BIT(GPIO_PORTA_DATA_R, Pin); /*choosing the pin to be LOW value*/

            break;
        }
        }
    }
    case PORTB:
    {
        switch (Value)
        {
        case HIGH:
        {
            SET_BIT(GPIO_PORTB_DATA_R, Pin); /*choosing the pin to be HIGH value*/

            break;
        }
        case LOW:
        {
            CLEAR_BIT(GPIO_PORTB_DATA_R, Pin); /*choosing the pin to be LOW value*/

            break;
        }
        }
    }
    case PORTC:
    {
        switch (Value)
        {
        case HIGH:
        {
            SET_BIT(GPIO_PORTC_DATA_R, Pin); /*choosing the pin to be HIGH value*/

            break;
        }
        case LOW:
        {
            CLEAR_BIT(GPIO_PORTC_DATA_R, Pin); /*choosing the pin to be LOW value*/

            break;
        }
        }
    }
    case PORTD:
    {
        switch (Value)
        {
        case HIGH:
        {
            SET_BIT(GPIO_PORTD_DATA_R, Pin); /*choosing the pin to be HIGH value*/

            break;
        }
        case LOW:
        {
            CLEAR_BIT(GPIO_PORTD_DATA_R, Pin); /*choosing the pin to be LOW value*/

            break;
        }
        }
    }
    case PORTE:
    {
        switch (Value)
        {
        case HIGH:
        {
            SET_BIT(GPIO_PORTE_DATA_R, Pin); /*choosing the pin to be HIGH value*/

            break;
        }
        case LOW:
        {
            CLEAR_BIT(GPIO_PORTE_DATA_R, Pin); /*choosing the pin to be LOW value*/

            break;
        }
        }
    }
    case PORTF:
    {
        switch (Value)
        {
        case HIGH:
        {
            SET_BIT(GPIO_PORTF_DATA_R, Pin); /*choosing the pin to be HIGH value*/

            break;
        }
        case LOW:
        {
            CLEAR_BIT(GPIO_PORTF_DATA_R, Pin); /*choosing the pin to be LOW value*/

            break;
        }
        }
    }
    }
}

int Read_Pin_Value(uint16_t Port, uint16_t Pin, uint16_t Value) // to read whether the pin value is high or low and return it
{
    int return_value;
    switch (Port)
    {
    case PORTA:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOA;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        return_value = GET_BIT(GPIO_PORTA_DATA_R, Pin); /*returning the value of the data register to know if its high or low*/
        break;
    }
    case PORTB:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOB;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        return_value = GET_BIT(GPIO_PORTB_DATA_R, Pin); /*returning the value of the data register to know if its high or low*/
        break;
    }
    case PORTC:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOC;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        return_value = GET_BIT(GPIO_PORTC_DATA_R, Pin); /*returning the value of the data register to know if its high or low*/
        break;
    }
    case PORTD:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOD;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        return_value = GET_BIT(GPIO_PORTD_DATA_R, Pin); /*returning the value of the data register to know if its high or low*/
        break;
    }
    case PORTE:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOE;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        return_value = GET_BIT(GPIO_PORTE_DATA_R, Pin); /*returning the value of the data register to know if its high or low*/
        break;
    }
    case PORTF:
    {
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
        SET_BIT(GPIO_PORTA_DEN_R, Pin);

        return_value = GET_BIT(GPIO_PORTF_DATA_R, Pin); /*returning the value of the data register to know if its high or low*/
        break;
    }
    }
    return return_value; /*returning the value of the register from the function*/
}

void Disable_Pin(uint16_t port, uint16_t pin)
{
    switch (port)
    {
    case PORTA:
    {
        CLEAR_BIT(GPIO_PORTA_DEN_R, pin); // deactivating the used pin in port A

        break;
    }
    case PORTB:
    {
        CLEAR_BIT(GPIO_PORTB_DEN_R, pin); // deactivating the used pin in port B

        break;
    }
    case PORTC:
    {
        CLEAR_BIT(GPIO_PORTC_DEN_R, pin); // deactivating the used pin in port c

        break;
    }
    case PORTD:
    {
        CLEAR_BIT(GPIO_PORTD_DEN_R, pin); // deactivating the used pin in port d

        break;
    }
    case PORTE:
    {
        CLEAR_BIT(GPIO_PORTE_DEN_R, pin); // deactivating the used pin in port e

        break;
    }
    case PORTF:
    {
        CLEAR_BIT(GPIO_PORTF_DEN_R, pin); // deactivating the used pin in port f

        break;
    }
    }
}

void Disable_Port(uint16_t port)
{
    switch (port)
    {
    case PORTA:
    {
        CLEAR_BIT(SYSCTL_RCGCGPIO_R, 0); // DISABLING THE CLOCK ON PORT A GPIO

        break;
    }
    case PORTB:
    {
        CLEAR_BIT(SYSCTL_RCGCGPIO_R, 1); // DISABLING THE CLOCK ON PORT B GPIO

        break;
    }
    case PORTC:
    {
        CLEAR_BIT(SYSCTL_RCGCGPIO_R, 2); // DISABLING THE CLOCK ON PORT C GPIO

        break;
    }
    case PORTD:
    {
        CLEAR_BIT(SYSCTL_RCGCGPIO_R, 3); // DISABLING THE CLOCK ON PORT D GPIO

        break;
    }
    case PORTE:
    {
        CLEAR_BIT(SYSCTL_RCGCGPIO_R, 4); // DISABLING THE CLOCK ON PORT E GPIO

        break;
    }
    case PORTF:
    {
        CLEAR_BIT(SYSCTL_RCGCGPIO_R, 5); // DISABLING THE CLOCK ON PORT F GPIO

        break;
    }
    }
}
