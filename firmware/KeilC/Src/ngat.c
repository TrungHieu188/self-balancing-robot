#include "ngat.h"
void INTERRUPT_TIM2_Init_Us (uint16_t us)
{
	//clock timer2
	RCC->APB1ENR |= (1 << 0);
  //bat auto reload
	TIM2->CR1 |= (1 << 7);
	//ngat khi tran
	TIM2->EGR |= (1 << 0);
	//bo chia clock 
	TIM2->PSC = 71;
	//dem toi bao nhieu thi tran
	TIM2->ARR = us - 1;
	//bat ngat
	TIM2->DIER |= (1 << 0);
	//xoa co ngat truoc khi chay
	TIM2->SR &= ~(1U << 0);
	//bat counter
	TIM2->CR1 |= (1 << 0);
	//bat NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
	//cau hinh muc uu tien
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(2, 1, 0)); //cung nhom uu tien 2, pre = 1, sub = 2
}
void TIM2_IRQHandler(void)
{
	if (TIM2->SR & 0x1)
	{
    TIM2->SR &= ~(1U << 0);
		TogglePin(PORTB, 13);
	}
}
void INTERRUPT_TIM2_Init_Ms (uint16_t ms)
{
	//clock timer2
	RCC->APB1ENR |= (1 << 0);
  //bat auto reload
	TIM2->CR1 |= (1 << 7);
	//ngat khi tran
	TIM2->EGR |= (1 << 0);
	//bo chia clock 
	TIM2->PSC = 7199;
	//dem toi bao nhieu thi tran
	TIM2->ARR = (ms * 10) - 1;
	//bat ngat
	TIM2->DIER |= (1 << 0);
	//xoa co ngat truoc khi chay
	TIM2->SR &= ~(1U << 0);
	//bat counter
	TIM2->CR1 |= (1 << 0);
	//bat NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
	//cau hinh muc uu tien
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(TIM2_IRQn, NVIC_EncodePriority(2, 1, 0)); //cung nhom uu tien 2, pre = 1, sub = 0
}
void INTERRUPT_EXTI1_Config(uint8_t port)
{
	//bat clock AFIO
	RCC->APB2ENR |= (1 << 0);
	if (port == 1)
	{
		GPIO(PORTA, 1, INPUT, PUPD);
		//tro keo xuong
		GPIOA->ODR &= ~(1U << 1);
	}
	else if (port == 2)
	{
		GPIO(PORTB, 1, INPUT, PUPD);
		//tro keo xuong
		GPIOB->ODR &= ~(1U << 1);		
	}
	else 
	{
		GPIO(PORTC, 1, INPUT, PUPD);
		//tro keo xuong
		GPIOC->ODR &= ~(1U << 1);		
	}
	//cau hinh AFIO, AFIO->EXTICR[0] tu line 0 den line 3
 AFIO->EXTICR[0] &= ~(0xFU << 4);
 AFIO->EXTICR[0] |= (uint8_t)(port << 4);
	//cau hinh line (chan 1 = line 1)
	EXTI->IMR |= (1 << 1);
	//nhan canh len 
	EXTI->RTSR |= (1 << 1);
	//nhan canh xuong
	EXTI->FTSR |= (1 << 1);
	//bat ngat
	NVIC_EnableIRQ(EXTI1_IRQn);
		//cau hinh muc uu tien
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(EXTI1_IRQn, NVIC_EncodePriority(2, 1, 1)); //cung nhom uu tien 2, pre = 1, sub = 1
}
void EXTI1_IRQHandler(void)
{
	if (EXTI->PR & (0x1 << 1))
	{
		EXTI->PR |= (1 << 1);
		TogglePin(PORTB, 13);
	}
}
void INTERRUPT_UART1_TX_DMA(uint8_t *pdata, uint16_t length)
{
	DMA1_UART1_TX_Config();
	DMA1_UART1_Send(pdata, length);
	DMA1_Channel4->CCR |= (1 << 1);
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(DMA1_Channel4_IRQn, NVIC_EncodePriority(2, 2, 1)); //cung nhom uu tien 2, pre = 2, sub = 1
}
void DMA1_Channel4_IRQHandler(void)
{
	if (DMA1->ISR & (1 << 13))
	{
		//xoa co
		DMA1->IFCR |= (1 << 13);
		TogglePin(PORTB, 13);
	}
}
void INTERRUPT_UART1_RX_DMA(uint8_t *pdata)
{
	DMA1_UART1_RX_Config(pdata);
	DMA1_Channel5->CCR |= (1 << 1);
	NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(DMA1_Channel5_IRQn, NVIC_EncodePriority(2, 3, 1)); //cung nhom uu tien 2, pre = 3, sub = 1	
}
void DMA1_Channel5_IRQHandler(void)
{
	if (DMA1->ISR & (1 << 17))
	{
		//xoa co
		DMA1->IFCR |= (1 << 17);
		TogglePin(PORTB, 13);
	}
}
void INTERRUPT_UART1_RX(void)
{
	UART1_Init();
	USART1->CR1 |= (1 << 5);
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(2, 3, 2)); //cung nhom uu tien 2, pre = 3, sub = 2	
}
void USART1_IRQHandler (void)
{
 if (USART1->SR & (0x1 << 5))
 {
	 //doc du lieu de xoa co 
	 uint8_t data1 = (uint8_t)USART1->DR;
	 if (data1 == '1')
	 {
		 TogglePin(PORTB, 13);
	 }
 }
 else if (USART1->SR & (0x1 << 7)) 
 {
	 //ghi du lieu de xoa co 
	 USART1->DR = 'A';
	 TogglePin(PORTB, 13);
 }
}
void INTERRUPT_UART1_TX(void)
{
	UART1_Init();	
	USART1->CR1 |= (1 << 7);
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(2, 3, 2)); //cung nhom uu tien 2, pre = 3, sub = 2	
}
void INTERRUPT_SPI1_TX(void)
{
  SPI1_Master_Cofig();
	SPI1->CR2 |= (1 << 7);
	NVIC_EnableIRQ(SPI1_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(SPI1_IRQn, NVIC_EncodePriority(2, 3, 2)); //cung nhom uu tien 2, pre = 3, sub = 2	
}
void INTERRUPT_SPI1_RX(void)
{
  SPI1_Master_Cofig();
	SPI1->CR2 |= (1 << 6);
	NVIC_EnableIRQ(SPI1_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(SPI1_IRQn, NVIC_EncodePriority(2, 1, 2)); //cung nhom uu tien 2, pre = 3, sub = 2		
}
void SPI1_IRQHandler (void)
{
	if (SPI1->SR & (1 << 0))
	{
		//clear co
		uint8_t data = (uint8_t)SPI1->DR;
		if (data == '1')
		{
			TogglePin(PORTB, 13);
		}
	}
	if (SPI1->SR & (1 << 1))
	{
		// clear co 
		SPI1->DR = 'A';
		TogglePin(PORTB, 13);
	}
}
void INTERRUPT_SPI1_TX_DMA(uint8_t *pdata)
{
	SPI1_Master_Cofig();
	DMA1_SPI1_TX_Config(pdata);
	DMA1_Channel3->CCR |= (1 << 1);
	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(DMA1_Channel3_IRQn, NVIC_EncodePriority(2, 3, 1)); //cung nhom uu tien 2, pre = 3, sub = 1	
}
void INTERRUPT_SPI1_RX_DMA(uint8_t *pdata)
{
	SPI1_Master_Cofig();
	DMA1_SPI1_RX_Config(pdata);
	DMA1_Channel2->CCR |= (1 << 1);
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);
	NVIC_SetPriorityGrouping(2); //2 bit uu tien cho preempriority 2 bit subpriority
	NVIC_SetPriority(DMA1_Channel2_IRQn, NVIC_EncodePriority(2, 3, 1)); //cung nhom uu tien 2, pre = 3, sub = 1		
}
void DMA1_Channel3_IRQHandler(void)
{
	if (DMA1->ISR & (1 << 9))
	{
		//xoa co
		DMA1->IFCR |= (1 << 9);
		TogglePin(PORTB, 13);
	}
}
void DMA1_Channel2_IRQHandler(void)
{
	if (DMA1->ISR & (1 << 5))
	{
		//xoa co
		DMA1->IFCR |= (1 << 5);
		TogglePin(PORTB, 13);
	}
}
