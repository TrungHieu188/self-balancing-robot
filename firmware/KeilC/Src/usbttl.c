#include "usbttl.h"

char debug[200];

void USART1_Init(void)
{
	RCC->APB2ENR |= (1 << 14);
	GPIO(PORTA, 9, 3, 5);
	GPIO(PORTA, 10, 0, 1);
	USART1->CR1 |= (1 << 13);
	USART1->CR1 &= ~(1U << 12);
	USART1->CR2 &= ~(3U << 12);
	USART1->BRR = 0x271;
	USART1->CR1 |= (1 << 3);
}
void USART1_Send1Byte(char x)
{
	while(!((USART1->SR >> 7) & 1));
	USART1->DR = x;
}
void USART1_SendData(uint8_t *data, uint8_t n)
{
	for(uint8_t i = 0; i < n; i ++)
	{
		USART1->DR = data[i];
	}
}
void USART1_SendString(char *str) 
	{
    while (*str) {             
        USART1_Send1Byte(*str++);
    }
}
void USART1_Debug_Array(float *data)
{
	sprintf(debug, "Gia tri cua Ax: %.2f | Ay: %.2f | Az: %.2f\r\nGia tri cua Gx: %.2f | Gy: %.2f | Gz: %.2f\r\n", (double)data[0], (double)data[1], (double)data[2], (double)data[3], (double)data[4], (double)data[5]);
	USART1_SendString(debug);
	delayms(1000);
}
void USART1_Debug(float data)
{
	sprintf(debug, "%.6f\r\n", (double)data);
	USART1_SendString(debug);
}
void USART1_Debug2var(float data, float data1)
{
	sprintf(debug, "%.2f,%.2f\r\n", (float)data, (float)data1);
	USART1_SendString(debug);

}
