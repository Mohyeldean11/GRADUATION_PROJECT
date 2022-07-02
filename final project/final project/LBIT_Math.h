/**
 * @file    LBIT.h
 * @author  mohy eldean  (mohyeldean@gmail.com)
 * @brief   This header file contains required mathematical operations over bits, (Bit manipulation).
 * @version 1.0
 * @date    1-5-2022
 *
 * @copyright Copyright (c) 2022
 *
 **/

#ifndef _LBIT_h_
#define _LBIT_h_

#define SET_BIT(REG,BIT)    REG|=(1<<BIT)       //setting the required bit to 1

#define CLEAR_BIT(REG,BIT)  REG&=~(1<<BIT)      //clearing the required bit to 0

#define TOGGLE_BIT(REG,BIT) REG^=(1<<BIT)       //toggling the bit

#define GET_BIT(REG,BIT)    ((REG>>BIT)&1)      //geting the value of the bit "will need a variable to assign the value to it"


#endif