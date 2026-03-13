#ifndef __NGAT_H
#define __NGAT_H

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "gpio.h"
//#include "dma.h"
//#include "uart.h"
//#include "spi.h"

void INTERRUPT_TIM2_Init_Us (uint16_t us);
void INTERRUPT_TIM2_Init_Ms (uint16_t ms);
void TIM2_IRQHandler(void);
void INTERRUPT_EXTI1_Config(uint8_t port);
void EXTI1_IRQHandler(void);
void INTERRUPT_UART1_TX_DMA(uint8_t *pdata, uint16_t length);
void DMA1_Channel4_IRQHandler(void);
void INTERRUPT_UART1_RX_DMA(uint8_t *pdata);
void DMA1_Channel5_IRQHandler(void);
void INTERRUPT_UART1_RX(void);
void USART1_IRQHandler (void);
void INTERRUPT_UART1_TX(void);
void INTERRUPT_SPI1_TX(void);
void INTERRUPT_SPI1_RX(void);
void SPI1_IRQHandler (void);
void INTERRUPT_SPI1_TX_DMA(uint8_t *pdata);
void INTERRUPT_SPI1_RX_DMA(uint8_t *pdata);
void DMA1_Channel3_IRQHandler(void);
void DMA1_Channel2_IRQHandler(void);
#define PA   0
#define PB   1
#define PC   2



#endif
