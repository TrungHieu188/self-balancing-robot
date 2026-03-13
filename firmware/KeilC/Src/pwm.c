#include "pwm.h"

void PWM_Init (uint8_t timer, uint8_t channel, uint16_t ARR, uint16_t PSC)
{
//Bat clock cho ngoai vi (RCC)

	RCC->APB1ENR |= (1 << (timer - 2));
//Cau hinh GPIO neu co chan lien quan
	if (timer == 2)
	{
		GPIO(PORTA, (channel - 1), OUTPUT50, AFOPP);
	}
	else if (timer == 3)
	{
		if ((channel > 5) && (channel < 8))
		{
			GPIO(PORTA, (channel + 5), OUTPUT50, AFOPP);
		}
		else
		{
			GPIO(PORTB, (channel - 3), OUTPUT50, AFOPP);
		}
	}
	else if (timer == 4)
	{
		GPIO(PORTB, (channel + 5), OUTPUT50, AFOPP);
	}
	else 
	{
		return;
	}
//Cau hinh ngoai vi bang cac thanh ghi dac thu
	TIM_TypeDef *pTIMx;
	if (timer == 2)
	{
		pTIMx = TIM2;
	}
	else if (timer == 3)
	{
		pTIMx = TIM3;
	}
	else 
	{
		pTIMx = TIM4;
	}
   //Cau hinh Timer
	pTIMx->PSC = PSC;
	pTIMx->ARR = ARR;
   //Cau hinh PWM	
	if (channel < 3)
	{
		if (channel == 1)
		{
			// chon che do output compare
			pTIMx->CCMR1 &= ~(3 << 0);
			//gia tri thanh ghi CCR1 duoc cap nhat sau khi thuc hien xong 1 chu ki PWM truoc do
			pTIMx->CCMR1 |= (1 << 3);
			//chon che do pwm
			pTIMx->CCMR1 &= ~(7 << 4);
			pTIMx->CCMR1 |= (6 << 4);
			//Bat ngoai vi
			pTIMx->CR1  |= (1 << 7);
			pTIMx->EGR  |= (1 << 0);
			pTIMx->CCER |= (1 << 0);	
      pTIMx->CR1  |= (1 << 0);			
		}
		else
		{
			// chon che do output compare
			pTIMx->CCMR1 &= ~(3 << 8);	
			//gia tri thanh ghi CCR1 duoc cap nhat sau khi thuc hien xong 1 chu ki PWM truoc do
			pTIMx->CCMR1 |= (1 << 11);
			//chon che do pwm
			pTIMx->CCMR1 &= ~(7 << 12);
			pTIMx->CCMR1 |= (6 << 12);
			//Bat ngoai vi
			pTIMx->CR1  |= (1 << 7);
			pTIMx->EGR  |= (1 << 0);			
			pTIMx->CCER |= (1 << 4);
      pTIMx->CR1  |= (1 << 0);				
		}
	}
	else
	{
		if (channel == 3)
		{
			// chon che do output compare
			pTIMx->CCMR2 &= ~(3 << 0);
			//gia tri thanh ghi CCR1 duoc cap nhat sau khi thuc hien xong 1 chu ki PWM truoc do
			pTIMx->CCMR2 |= (1 << 3);
			//chon che do pwm
			pTIMx->CCMR2 &= ~(7 << 4);
			pTIMx->CCMR2 |= (6 << 4);
			//Bat ngoai vi
			pTIMx->CR1  |= (1 << 7);
			pTIMx->EGR  |= (1 << 0);			
			pTIMx->CCER |= (1 << 8);
      pTIMx->CR1  |= (1 << 0);				
		}
		else
		{
			// chon che do output compare
			pTIMx->CCMR2 &= ~(3 << 8);	
			//gia tri thanh ghi CCR1 duoc cap nhat sau khi thuc hien xong 1 chu ki PWM truoc do
			pTIMx->CCMR2 |= (1 << 11);
			//chon che do pwm
			pTIMx->CCMR2 &= ~(7 << 12);
			pTIMx->CCMR2 |= (6 << 12);
			//Bat ngoai vi
			pTIMx->CR1  |= (1 << 7);
			pTIMx->EGR  |= (1 << 0);			
			pTIMx->CCER |= (1 << 12);
      pTIMx->CR1  |= (1 << 0);				
		}
		
	}
}
void PWM_Duty (uint32_t dutycycle, uint8_t timer, uint8_t channel, uint16_t ARR)
{
	TIM_TypeDef *pTIMx;
	if (timer == 2)
	{
		pTIMx = TIM2;
	}
	else if (timer == 3)
	{
		pTIMx = TIM3;
	}
	else 
	{
		pTIMx = TIM4;
	}
	switch (channel)
	{
		case 1:
			pTIMx->CCR1 = (uint16_t)(dutycycle * (ARR + 1))/ 100;
		break;
		case 2:
			pTIMx->CCR2 = (uint16_t)(dutycycle * (ARR + 1))/ 100;
		break;
		case 3:
			pTIMx->CCR3 = (uint16_t)(dutycycle * (ARR + 1))/ 100;
		break;
		case 4:
			pTIMx->CCR4 = (uint16_t)(dutycycle * (ARR + 1))/ 100;
		break;	
	}
}
void PWM_Bit (uint16_t bit, uint8_t timer, uint8_t channel)
{
	TIM_TypeDef *pTIMx;
	if (timer == 2)
	{
		pTIMx = TIM2;
	}
	else if (timer == 3)
	{
		pTIMx = TIM3;
	}
	else 
	{
		pTIMx = TIM4;
	}
	switch (channel)
	{
		case 1:
			pTIMx->CCR1 = bit;
		break;
		case 2:
			pTIMx->CCR2 = bit;
		break;
		case 3:
			pTIMx->CCR3 = bit;
		break;
		case 4:
			pTIMx->CCR4 = bit;
		break;	
	}
}
void PWM_Servo (uint8_t angle, uint8_t timer, uint8_t channel)
{
	TIM_TypeDef *pTIMx;
	if (timer == 2)
	{
		pTIMx = TIM2;
	}
	else if (timer == 3)
	{
		pTIMx = TIM3;
	}
	else 
	{
		pTIMx = TIM4;
	}
	switch (channel)
	{
		case 1:
			pTIMx->CCR1 = 500 + ((angle * 2000) / 180);
		break;
		case 2:
			pTIMx->CCR2 = 500 + ((angle * 2000) / 180);
		break;
		case 3:
			pTIMx->CCR3 = 500 + ((angle * 2000) / 180);
		break;
		case 4:
			pTIMx->CCR4 = 500 + ((angle * 2000) /180);
		break;	
	}
}
