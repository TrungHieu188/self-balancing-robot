#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f10x.h"
#include "gpio.h"
#include "systick_delay.h"
#include "SysClock.h"


#define READ     1
#define WRITE    0

extern volatile int flag_dma;
extern uint8_t Raw_Data[12];

void I2C1_Init(void);
void I2C1_ResetCLK (void);
void MPU_Init(void);
void MPU_W (uint8_t address, uint8_t data);
void MPU_RW(uint8_t address, uint8_t RW) ;
void I2C1_Start(void);
void I2C1_Stop(void);
void I2C1_Send1Byte(uint8_t data);
void FIFO_INT(void);
void EXTI_Config(void);
void EXTI15_10_IRQHandler(void);
void DMA1_I2C1_Config(uint8_t *pdata);
void DMA_Read(void);
void DMA1_Channel7_IRQHandler(void);
uint8_t MPU_R1Byte (uint8_t address);
uint8_t I2C1_Read1Byte(void);
void MPU_FIFO_INT_Config(void);
void Data_MPU(float *dulieudachuyendoi);

#endif
