#include "dma.h"

void DMA1_ADC1_Config(uint16_t *pdata)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel1->CCR &= ~(1U << 0);
	//Doc du lieu tu ngoai vi 
	DMA1_Channel1->CCR &= ~(1U << 4);
	//Lien tuc luu xoay vong trong mang
	DMA1_Channel1->CCR |= (1 << 5);
	//Sau khi luu tang dia chi cua mang len 1 
	DMA1_Channel1->CCR |= (1 << 7);
	//Kich thuoc du lieu lay tu ADC la 16 bit
	DMA1_Channel1->CCR &= ~(3U << 8);
	DMA1_Channel1->CCR |= (1 << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel1->CCR &= ~(3U << 10);
	DMA1_Channel1->CCR |= (1 << 10);
	//Muc do uu tien 
	DMA1_Channel1->CCR &= ~(3U << 12);
	DMA1_Channel1->CCR |= (3 << 12);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel1->CNDTR = 0;
	DMA1_Channel1->CNDTR |= (10 << 0);
	//Dia chi thanh ghi luu du lieu ADC
	DMA1_Channel1->CPAR = (uint32_t)&(ADC1->DR);
	//Dia chi mang luu du lieu
	DMA1_Channel1->CMAR = (uint32_t)pdata;
	//Bat ADC1 DMA
	ADC1->CR2 |= (1 << 8);
	//Bat DMA
	DMA1_Channel1->CCR |= (1 << 0);	
}
void DMA1_SPI1_RX_Config(uint8_t *pdata)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel2->CCR &= ~(1U << 0);
	//Doc du lieu tu ngoai vi 
	DMA1_Channel2->CCR &= ~(1U << 4);
	//Lien tuc luu xoay vong trong mang
	DMA1_Channel2->CCR |= (1 << 5);
	//Sau khi luu tang dia chi cua mang len 1 
	DMA1_Channel2->CCR |= (1 << 7);
	//Kich thuoc du lieu lay tu SPI1 la 8 bit
	DMA1_Channel2->CCR &= ~(3U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel2->CCR &= ~(3U << 10);
	//Muc do uu tien 
	DMA1_Channel2->CCR &= ~(3U << 12);
	DMA1_Channel2->CCR |= (2 << 12);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel2->CNDTR = 0;
	DMA1_Channel2->CNDTR |= (10 << 0);
	//Dia chi thanh ghi luu du lieu SPI1
	DMA1_Channel2->CPAR = (uint32_t)&(SPI1->DR);
	//Dia chi mang luu du lieu
	DMA1_Channel2->CMAR = (uint32_t)pdata;
	//Bat SPI1 RX DMA
  SPI1->CR2 |= (1 << 0);
	//Bat DMA
	DMA1_Channel2->CCR |= (1 << 0);	
}
void DMA1_SPI1_TX_Config(uint8_t *pdata)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel3->CCR &= ~(1U << 0);
	//Doc du lieu tu bo nho 
	DMA1_Channel3->CCR |= (1U << 4);
	//Lien tuc lay du lieu xoay vong trong mang
	DMA1_Channel3->CCR |= (1 << 5);
	//Sau khi lay du lieu tang dia chi cua mang len 1 
	DMA1_Channel3->CCR |= (1 << 7);
	//Kich thuoc du lieu ghi vao SPI1 la 8 bit
	DMA1_Channel3->CCR &= ~(3U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel3->CCR &= ~(3U << 10);
	//Muc do uu tien 
	DMA1_Channel3->CCR &= ~(3U << 12);
	DMA1_Channel3->CCR |= (1 << 12);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel3->CNDTR = 0;
	DMA1_Channel3->CNDTR |= (10 << 0);
	//Dia chi thanh ghi ghi du lieu SPI1
	DMA1_Channel3->CPAR = (uint32_t)&(SPI1->DR);
	//Dia chi mang lay du lieu
	DMA1_Channel3->CMAR = (uint32_t)pdata;
	//Bat SPI1 TX DMA
  SPI1->CR2 |= (1 << 1);
	//Bat DMA
	DMA1_Channel3->CCR |= (1 << 0);	
}
void DMA1_UART1_TX_Config(void)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel4->CCR &= ~(1U << 0);
	//Doc du lieu tu bo nho 
	DMA1_Channel4->CCR |= (1U << 4);
	//lay du lieu 1 lan trong mang
	DMA1_Channel4->CCR &= ~(1U << 5);
	//Sau khi lay du lieu tang dia chi cua mang len 1 
	DMA1_Channel4->CCR |= (1 << 7);
	//Kich thuoc du lieu ghi vao UART1 la 8 bit
	DMA1_Channel4->CCR &= ~(3U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel4->CCR &= ~(3U << 10);
	//Muc do uu tien 
	DMA1_Channel4->CCR &= ~(3U << 12);
	DMA1_Channel4->CCR |= (1 << 12);
	//Dia chi thanh ghi ghi du lieu UART1
	DMA1_Channel4->CPAR = (uint32_t)&(USART1->DR);
	//Bat UART1 TX DMA
  USART1->CR3 |= (1 << 7);
}
void DMA1_UART1_Send(uint8_t *pdata, uint16_t lenght)
{
	//Tat kenh truoc khi cau hinh
	DMA1_Channel4->CCR &= ~(1U << 0);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel4->CNDTR = lenght;
	//Dia chi mang lay du lieu
	DMA1_Channel4->CMAR = (uint32_t)pdata;
	//Bat DMA
	DMA1_Channel4->CCR |= (1 << 0);	
}
void DMA1_UART1_RX_Config(uint8_t *pdata)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel5->CCR &= ~(1U << 0);
	//Doc du lieu tu ngoai vi 
	DMA1_Channel5->CCR &= ~(1U << 4);
	//Lien tuc luu xoay vong trong mang
	DMA1_Channel5->CCR |= (1 << 5);
	//Sau khi luu tang dia chi cua mang len 1 
	DMA1_Channel5->CCR |= (1 << 7);
	//Kich thuoc du lieu lay tu UART1 la 8 bit
	DMA1_Channel5->CCR &= ~(3U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel5->CCR &= ~(3U << 10);
	//Muc do uu tien 
	DMA1_Channel5->CCR &= ~(3U << 12);
	DMA1_Channel5->CCR |= (2 << 12);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel5->CNDTR = 10;
	//Dia chi thanh ghi luu du lieu UART1
	DMA1_Channel5->CPAR = (uint32_t)&(USART1->DR);
	//Dia chi mang luu du lieu
	DMA1_Channel5->CMAR = (uint32_t)pdata;
	//Bat UART1 RX DMA
  USART1->CR3 |= (1 << 6);
	//Bat DMA
	DMA1_Channel5->CCR |= (1 << 0);	
}
void DMA1_I2C1_TX_Config(void)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel6->CCR &= ~(1U << 0);
	//Doc du lieu tu bo nho 
	DMA1_Channel6->CCR |= (1U << 4);
	//lay du lieu 1 lan trong mang
	DMA1_Channel6->CCR &= ~(1U << 5);
	//Sau khi lay du lieu tang dia chi cua mang len 1 
	DMA1_Channel6->CCR |= (1 << 7);
	//Kich thuoc du lieu ghi vao I2C1 la 8 bit
	DMA1_Channel6->CCR &= ~(3U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel6->CCR &= ~(3U << 10);
	//Muc do uu tien 
	DMA1_Channel6->CCR &= ~(3U << 12);
	DMA1_Channel6->CCR |= (1 << 12);
	//Dia chi thanh ghi ghi du lieu I2C1
	DMA1_Channel6->CPAR = (uint32_t)&(I2C1->DR);
  //bat DMA I2C1
	I2C1->CR2 |= (1 << 11);	
}
void DMA1_I2C1_Send(uint8_t *pdata, uint16_t lenght)
{
	//Tat kenh truoc khi cau hinh
	DMA1_Channel6->CCR &= ~(1U << 0);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel6->CNDTR = lenght;
	//Dia chi mang lay du lieu
	DMA1_Channel6->CMAR = (uint32_t)pdata;	
	//Bat DMA
	DMA1_Channel6->CCR |= (1 << 0);		
}
void DMA1_I2C1_RX_Config(uint8_t *pdata, uint16_t length)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel7->CCR &= ~(1U << 0);
	//Doc du lieu tu ngoai vi 
	DMA1_Channel7->CCR &= ~(1U << 4);
	//Lien tuc luu xoay vong trong mang
	DMA1_Channel7->CCR |= (1 << 5);
	//Sau khi luu tang dia chi cua mang len 1 
	DMA1_Channel7->CCR |= (1 << 7);
	//Kich thuoc du lieu lay tu I2C1 la 8 bit
	DMA1_Channel7->CCR &= ~(3U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel7->CCR &= ~(3U << 10);
	//Muc do uu tien 
	DMA1_Channel7->CCR &= ~(3U << 12);
	DMA1_Channel7->CCR |= (2 << 12);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel7->CNDTR = length;
	//Dia chi thanh ghi luu du lieu I2C1
	DMA1_Channel7->CPAR = (uint32_t)&(I2C1->DR);
	//Dia chi mang luu du lieu
	DMA1_Channel7->CMAR = (uint32_t)pdata;
	//Bat I2C1 RX DMA
  I2C1->CR2 |= (1 << 11);
	//Bat DMA
	DMA1_Channel7->CCR |= (1 << 0);	
}
void DMA1_PWM1_Duty_Config(uint16_t *pdata)
{
	//Bat clock DMA1
	RCC->AHBENR |= (1 << 0);
	//Tat kenh truoc khi cau hinh
	DMA1_Channel5->CCR &= ~(1U << 0);
	//Doc du lieu tu bo nho 
	DMA1_Channel5->CCR |= (1U << 4);
	//Lien tuc lay du lieu xoay vong trong mang
	DMA1_Channel5->CCR |= (1 << 5);
	//Sau khi lay du lieu tang dia chi cua mang len 1 
	DMA1_Channel5->CCR |= (1 << 7);
	//Kich thuoc du lieu ghi vao PWM1 la 16 bit
	DMA1_Channel5->CCR &= ~(3U << 8);
	DMA1_Channel5->CCR |= (1U << 8);
	//Kich thuoc cua 1 phan tu trong mang
	DMA1_Channel5->CCR &= ~(3U << 10);
	DMA1_Channel5->CCR |= (1U << 10);
	//Muc do uu tien 
	DMA1_Channel5->CCR &= ~(3U << 12);
	DMA1_Channel5->CCR |= (1 << 12);
	//So luong du lieu can chuyen doi = so phan tu cua mang
	DMA1_Channel5->CNDTR = 0;
	DMA1_Channel5->CNDTR |= (10 << 0);
	//Dia chi thanh ghi ghi du lieu 
	DMA1_Channel5->CPAR = (uint32_t)&(TIM2->CCR1);
	//Dia chi mang lay du lieu
	DMA1_Channel5->CMAR = (uint32_t)pdata;
	//Bat PWM  DMA
  TIM2->DIER |= (1 << 9);
	//Bat DMA
	DMA1_Channel5->CCR |= (1 << 0);	
}
