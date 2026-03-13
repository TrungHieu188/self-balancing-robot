#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"
#include "gpio.h"

#define THUAN   1
#define NGICH  0

void PWM1_Init(void);
void PWM1(float pwm);
void PWM_Motor1(uint8_t chieu, float pwm);
void PWM2_Init(void);
void PWM2(float pwm);
void PWM_Motor2(uint8_t chieu, float pwm);
void PWM_Init(void);
void Encoder1_Init(void);
void Encoder2_Init(void);
void Encoder_Init(void);


#endif
