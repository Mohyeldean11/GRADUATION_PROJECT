#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
//#include "inc/hw_memmap.h
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"


#include "inc/hw_memmap.h"
#include "inc/hw_GPIO.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

#include "tm4c_gpio_interface.h"
#define LOAD_VALUE    8000
#define PULSE_TIME_uS 100

//volatile uint32_t pulses [17]={1600, 2400, 3200, 4000, 4800, 5600, 6400, 7200, 8000, 8800, 9600, 10400, 11200, 12000, 12800, 13600, 14400};
//volatile uint16_t pulses [9]={1600, 3200, 4800, 6400, 8000, 9600, 11200, 12800, 14400};
volatile uint16_t pulses [9]={LOAD_VALUE-(100*LOAD_VALUE/1000),
                              LOAD_VALUE-(200*LOAD_VALUE/1000),
                              LOAD_VALUE-(300*LOAD_VALUE/1000),
                              LOAD_VALUE-(400*LOAD_VALUE/1000),
                              LOAD_VALUE-(500*LOAD_VALUE/1000),
                              LOAD_VALUE-(600*LOAD_VALUE/1000),
                              LOAD_VALUE-(700*LOAD_VALUE/1000),
                              LOAD_VALUE-(800*LOAD_VALUE/1000),
                              LOAD_VALUE-(900*LOAD_VALUE/1000)};
volatile uint16_t idx = 0;

volatile uint16_t counter;
int mmm;
volatile int error = 0;
//void PWM1_G1_Handler (void){
//    if ((PWM1_1_RIS_R&0x2) && (PWM1_1_CMPA_R != pulses[idx])){
//        PWM1_1_CMPA_R = pulses[idx];
//        idx +=1;
//        if (idx == 9)
//                idx = 0;
//
//}
//}

void PWM1_G1_Handler (void){
    if ((PWM1_1_RIS_R&0x2)&& (PWM1_1_CMPA_R != pulses[idx])){
        PWM1_1_ISC_R |= 0xF;
        PWM1_1_CMPA_R = pulses[idx];
        idx++;
        if (idx == 9)
                idx = 0;

}
}


int main(void){

   SYSCTL_RCGCPWM_R |= 2;    /* PWM1 Clock enable*/
   SYSCTL_RCC_R &= ~0x100000; /*PWM1 module--No Prescaller. */
   SYSCTL_RCC_R |= (1<<19)|(1<<18)|(1<<17);
   SYSCTL_RCGCGPIO_R |= (1<<4); /*Enable Clock To GPIOE*/
   SYSCTL_GPIOHBCTL_R |= (1<<4);

   GPIO_PORTE_AHB_DIR_R |= (1<<4); /*Set GPIOE Direction Is output*/
//   GPIO_PORTE_AFSEL_R = 0x10;
   GPIO_PORTE_AHB_AFSEL_R = (1<<4);
   GPIO_PORTE_AHB_PCTL_R = 0x50000;
   GPIO_PORTE_AHB_DR8R_R|= (1<<4);
   GPIO_PORTE_AHB_SLR_R |= (1<<4);
   GPIO_PORTE_AHB_DEN_R |= (1<<4); /*GPIOE Digital Enable*/

//   GPIO_PORTE_AHB_DEN_R

   /*Control Section*/
   PWM1_1_GENA_R |= PWM_1_GENA_ACTCMPAD_INV | PWM_1_GENA_ACTCMPAU_INV; // PWM_1_GENA_ACTLOAD_ONE
//   PWM1_1_GENA_R |= PWM_1_GENA_ACTZERO_INV; // Debug Time Sample Don't Forget to Comment Interrupt Section
   PWM1_1_LOAD_R = LOAD_VALUE; // Time Sample = 1 mS

   PWM1_1_CMPA_R = LOAD_VALUE-(PULSE_TIME_uS*LOAD_VALUE/1000); // 16000*.5

   /*Interrupt Section*/
   PWM1_INTEN_R |= (1<<1);   /* Enable Global Interrupt */
   PWM1_1_INTEN_R |= PWM_1_INTEN_INTCNTLOAD; /* Enable PWM1 Module 1 Interrupt for Counter=PWMnZero */
//   NVIC_EN4_R |= (1<<7);     /*NVIC*/

   /*Update Comparator Value Section*/
   PWM1_1_CTL_R |= (1<<1); /*Count-UP/Down Mode*/

//   PWM1_1_CTL_R |= (1<<2);
//   PWM1_CTL_R   |= (1<<1);
//   PWM1_1_CTL_R |= (1<<1);
//   PWM1_ENUPD_R |= PWM_ENUPD_ENUPD2_LSYNC; /*PWM Enable Update*/

   /*Enable Section*/
   PWM1_ENABLE_R |= (1<<2); /*MnPWM1 Output Enable*/
   PWM1_1_CTL_R |= PWM_1_CTL_ENABLE; /*Enable Counter*/



   while(1){

   }
}

