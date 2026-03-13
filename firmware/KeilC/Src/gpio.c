#include "gpio.h"

void GPIO (uint8_t port, uint8_t pinnumber, uint8_t mode, uint8_t submode)
{
GPIO_TypeDef *pGPIOx;
	if (port == 0)
	{
		pGPIOx = GPIOA;
	}
	else if (port == 1)
	{
		pGPIOx = GPIOB;
	}
	else
	{
		pGPIOx = GPIOC;
	}
	RCC->APB2ENR |= (0x1 << (port + 2));
	volatile uint32_t *pConfig = (pinnumber < 8) ? &(pGPIOx->CRL) : &(pGPIOx->CRH);
	
	*pConfig &= (uint32_t)~(0xF << (4 * (pinnumber % 8)));
	*pConfig |= (uint32_t)(mode << (4 * (pinnumber % 8)));
	if(submode < 3)
	{
		*pConfig |= (uint32_t)(submode << ((4 * (pinnumber % 8)) + 2));
	}
	else
	{
		*pConfig |= (uint32_t)((submode - 3) << ((4 * (pinnumber % 8)) + 2));
	}

}
uint8_t    ReadPin    (uint8_t port, uint8_t pinnumber)
{
	GPIO_TypeDef *pGPIOx;
	if (port == 0)
	{
		pGPIOx = GPIOA;
	}
	else if (port == 1)
	{
		pGPIOx = GPIOB;
	}
	else
	{
		pGPIOx = GPIOC;
	}
	uint8_t value;
	value = (((pGPIOx->IDR) >> pinnumber) & 0x1);
	return value;
}
uint16_t   ReadPort   (uint8_t port)
{
	GPIO_TypeDef *pGPIOx;
	if (port == 0)
	{
		pGPIOx = GPIOA;
	}
	else if (port == 1)
	{
		pGPIOx = GPIOB;
	}
	else
	{
		pGPIOx = GPIOC;
	}
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

void       WritePin   (uint8_t port, uint8_t pinnumber, uint8_t data)
{
	GPIO_TypeDef *pGPIOx;
	if (port == 0)
	{
		pGPIOx = GPIOA;
	}
	else if (port == 1)
	{
		pGPIOx = GPIOB;
	}
	else
	{
		pGPIOx = GPIOC;
	}
	if (data)
	{
		pGPIOx->ODR |= (0x1 << pinnumber);
	}
	else
	{
		pGPIOx->ODR &= ~(0x1U << pinnumber);
	}
}
void       WritePort  (uint8_t port, uint16_t data)
{
	GPIO_TypeDef *pGPIOx;
	if (port == 0)
	{
		pGPIOx = GPIOA;
	}
	else if (port == 1)
	{
		pGPIOx = GPIOB;
	}
	else
	{
		pGPIOx = GPIOC;
	}
	pGPIOx->ODR = data;
}
void       TogglePin  (uint8_t port, uint8_t pinnumber)
{
		GPIO_TypeDef *pGPIOx;
	if (port == 0)
	{
		pGPIOx = GPIOA;
	}
	else if (port == 1)
	{
		pGPIOx = GPIOB;
	}
	else
	{
		pGPIOx = GPIOC;
	}
	pGPIOx->ODR ^= (0x1 << pinnumber);
}
