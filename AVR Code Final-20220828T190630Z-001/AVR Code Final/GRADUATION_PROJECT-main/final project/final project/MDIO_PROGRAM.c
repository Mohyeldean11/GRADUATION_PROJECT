/************************************************************************/
/* Name: MDIO_PROGRAM.c                                                 */
/* Author: MOHIEE ELDEAN                                                */
/* Version: V1.0                                                        */
/* Usage: This file contains logical implementations of DIO Module      */
/************************************************************************/

/************************************************************************/
/*                              Includes                                */
/************************************************************************/

#include "DATA_TYPES.h"
#include "LBIT_MATH.h"
#include "MDIO_PRIVATE.h"
#include "MDIO_INTERFACE.h"

/*FUNCTIONS DEFINITIONS*/

void MDIO_SETPIN_STATUS(u8_t au8_port, u8_t au8_pin, u8_t au8_status)
{

    switch (au8_port)
    {
    /*incase of port A*/
    case PORTA:
    {
        /*GETTING THE STATUS*/
        switch (au8_status)
        {
            /*INCASE OF OUTPUT*/
        case OUTPUT:
            MDIO_DDRA |= au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 1*/

            break;

            /*INCASE OF INPUT FLOAT*/
        case INPUT_FLOAT:

            MDIO_DDRA &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 0*/

            break;

            /*INCASE OF INPUT PULLUP*/
        case INPUT_PULLUP:

            MDIO_DDRA &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN PINS BY 0*/

            MDIO_PORTA |= au8_pin; /*Set the specified pins to 1 in PORT*/
            break;
        }
        /*incase of port B*/
        break;
    }

    case PORTB:
    {
        /*GETTING THE STATUS*/
        switch (au8_status)
        {
            /*INCASE OF OUTPUT*/
        case OUTPUT:
            MDIO_DDRB |= au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 1*/

            break;

            /*INCASE OF INPUT FLOAT*/
        case INPUT_FLOAT:

            MDIO_DDRB &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 0*/

            break;

            /*INCASE OF INPUT PULLUP*/
        case INPUT_PULLUP:

            MDIO_DDRB &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN PINS BY 0*/

            MDIO_PORTB |= au8_pin; /*Set the specified pins to 1 in PORT*/
            break;
        }
        break;
    }
        /*incase of port C*/
    case PORTC:
    {
        /*GETTING THE STATUS*/
        switch (au8_status)
        {
            /*INCASE OF OUTPUT*/
        case OUTPUT:
            MDIO_DDRC |= au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 1*/

            break;

            /*INCASE OF INPUT FLOAT*/
        case INPUT_FLOAT:

            MDIO_DDRC &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 0*/

            break;

            /*INCASE OF INPUT PULLUP*/
        case INPUT_PULLUP:

            MDIO_DDRC &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN PINS BY 0*/

            MDIO_PORTC |= au8_pin; /*Set the specified pins to 1 in PORT*/

            break;
        }
        break;
    }
        /*incase of port D*/
    case PORTD:
    {
        /*GETTING THE STATUS*/
        switch (au8_status)
        {
            /*INCASE OF OUTPUT*/
        case OUTPUT:
            MDIO_DDRD |= au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 1*/

            break;

            /*INCASE OF INPUT FLOAT*/
        case INPUT_FLOAT:

            MDIO_DDRD &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN DDRA BY 0*/

            break;

            /*INCASE OF INPUT PULLUP*/
        case INPUT_PULLUP:

            MDIO_DDRD &= ~au8_pin; /*SETTING THE VALUE OF THE PINS IN PINS BY 0*/

            MDIO_PORTD |= au8_pin; /*Set the specified pins to 1 in PORT*/

            break;
        }
        break;
    }
        return;
    }
}
void MDIO_SETPIN_VALUE(u8_t au8_port, u8_t au8_pin, u8_t au8_value)
{
    switch (au8_port)
    {
    /*incase of portA*/
    case PORTA:
    {
        switch (au8_value)
        {
        /*INCASE OF HIGH VALUE*/
        case HIGH:
            MDIO_PORTA |= au8_pin; /*SETTING THE PINS TO 1*/

            break;

        /*INCASE OF LOW VALUE*/
        case LOW:
            MDIO_PORTA &= ~au8_pin; /*SETTING THE PINS TO 0*/

            break;
        }
        break;
    }
        /*incase of portB*/
    case PORTB:
    {
        switch (au8_value)
        {
        /*INCASE OF HIGH VALUE*/
        case HIGH:
            MDIO_PORTB |= au8_pin; /*SETTING THE PINS TO 1*/

            break;

        /*INCASE OF LOW VALUE*/
        case LOW:
            MDIO_PORTB &= ~au8_pin; /*SETTING THE PINS TO 0*/

            break;
        }
        break;
    }
        /*incase of portC*/
    case PORTC:
    {
        switch (au8_value)
        {
        /*INCASE OF HIGH VALUE*/
        case HIGH:
            MDIO_PORTC |= au8_pin; /*SETTING THE PINS TO 1*/

            break;

        /*INCASE OF LOW VALUE*/
        case LOW:
            MDIO_PORTC &= ~au8_pin; /*SETTING THE PINS TO 0*/

            break;
        }
        break;
    }
        /*incase of portD*/
    case PORTD:
    {
        switch (au8_value)
        {
        /*INCASE OF HIGH VALUE*/
        case HIGH:
            MDIO_PORTD |= au8_pin; /*SETTING THE PINS TO 1*/

            break;

        /*INCASE OF LOW VALUE*/
        case LOW:
            MDIO_PORTD &= ~au8_pin; /*SETTING THE PINS TO 0*/

            break;
        }
        break;
    }
    }
    return;
}

void MDIO_TOGGLEPIN_VALUE(u8_t au8_port, u8_t au8_pin)
{
    switch (au8_port)
    {
    /*incase of portA*/
    case PORTA:

        MDIO_PORTA ^= au8_pin; /*TOGGLEING THE PIN VALUE*/

        break;
    /*incase of portB*/
    case PORTB:

        MDIO_PORTB ^= au8_pin; /*TOGGLEING THE PIN VALUE*/

        break;
    /*incase of portC*/
    case PORTC:

        MDIO_PORTC ^= au8_pin; /*TOGGLEING THE PIN VALUE*/

        break;
    /*incase of portD*/
    case PORTD:

        MDIO_PORTD ^= au8_pin; /*TOGGLEING THE PIN VALUE*/

        break;
    }
    return;
}

u8_t MDIO_GETPIN_VALUE(u8_t au8_port, u8_t au8_pin)
{
    u8_t au8_pinvalue = 0; /*creating a variable to carry the value of the pin*/

    switch (au8_port)
    {
    /*INCASE OF PORT A*/
    case PORTA:
        if (MDIO_PINA & au8_pin) // the value is 1
        {
            au8_pinvalue = HIGH;
        }
        else
            au8_pinvalue = LOW; // the value is 0

        break;

    /*INCASE OF PORT B*/
    case PORTB:
        if (MDIO_PINB & au8_pin) // the value is 1
        {
            au8_pinvalue = HIGH;
        }
        else
            au8_pinvalue = LOW; // the value is 0

        break;

    /*INCASE OF PORT C*/
    case PORTC:
        if (MDIO_PINC & au8_pin) // the value is 1
        {
            au8_pinvalue = HIGH;
        }
        else
            au8_pinvalue = LOW; // the value is 0

        break;

    /*INCASE OF PORT D*/
    case PORTD:
        if (MDIO_PIND & au8_pin) // the value is 1
        {
            au8_pinvalue = HIGH;
        }
        else
            au8_pinvalue = LOW; // the value is 0

        break;
    }

    return au8_pinvalue;
}
