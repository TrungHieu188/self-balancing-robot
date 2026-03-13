#include "systick_delay.h"

void delayms(uint16_t ms)
{
  SysTick->CTRL |= (1 << 2);            //chon nguon clock
  SysTick->LOAD |= 72000 - 1;           //chia tan so 1 tick = 1ms
	
  SysTick->CTRL |= (1 << 0);            //bat counter
	for (volatile int i = 0; i < ms; i ++)
	{
		while (!((SysTick->CTRL) & (1 << 16)));
	}
	SysTick->CTRL &= ~(1U << 0);          //tat counter
}
