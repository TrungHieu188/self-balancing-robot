#include "delay.h"

void Tim3Config (void)
{
	RCC->APB1ENR |= (0x1 << 1); // bat xung clock cho timer
	TIM3->PSC = 71;             // bo chia prescaler de tan so la 1MHZ -> couter dem len 1 khi qua 1us
	TIM3->ARR = 0xFFFF;         // gia tri max co the dem
	TIM3->EGR |= (0x1 << 0);    //  nap lai gia tri moi cua PSC ARR CNT
	TIM3->CR1 |= (0x1 << 0);    // bat counter	
}
void delayus (uint32_t us)
{
   TIM3->CNT = 0;
	while (TIM3->CNT < us);
}
void delayms (uint32_t ms)
{
while (ms--)
{
	delayus (1000);
}
}
