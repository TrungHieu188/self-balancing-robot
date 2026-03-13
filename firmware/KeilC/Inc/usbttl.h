#ifndef __USBTTL
#define __USBTTL

#include "stm32f10x.h"
#include "gpio.h"
#include "stdio.h"
#include "systick_delay.h"

extern char debug[200];

void USART1_Init(void);
void USART1_Send1Byte(char x);
void USART1_SendData(uint8_t *data, uint8_t n);
void USART1_SendString(char *str);
void USART1_Debug_Array(float *data);
void USART1_Debug(float data);
void USART1_Debug2var(float data, float data1);
#endif
