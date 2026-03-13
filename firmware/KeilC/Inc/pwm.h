#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"
#include "gpio.h"

//timer2 CH1->CH4 PA0 -> PA3
//timer3 CH1->CH2 PA6 -> PA7, CH3->CH4 PB0->PB1
//timer4 CH1->CH4 PB6->PB9
#define TIMER2   2
#define TIMER3   3
#define TIMER4   4
#define CH1      1
#define CH2      2
#define CH3      3
#define CH4      4



void PWM_Init (uint8_t timer, uint8_t channel, uint16_t ARR, uint16_t PSC);
void PWM_Duty (uint32_t dutycycle, uint8_t timer, uint8_t channel, uint16_t ARR);
void PWM_Bit (uint16_t bit, uint8_t timer, uint8_t channel);
void PWM_Servo (uint8_t angle, uint8_t timer, uint8_t channel);

#endif


