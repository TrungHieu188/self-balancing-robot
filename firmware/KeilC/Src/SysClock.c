#include "SysClock.h"

void SysClock (void) 
{
	RCC->CR |= (0x1 << 16);             // bat HSE
	while (!((RCC->CR >> 17) & (0x1))); // cho xung clock HSE bat on dinh
	FLASH->ACR &= ~(0x7U << 0);         // cau hinh de flash theo kip xung clock
	FLASH->ACR |= (0x2 << 0);
	FLASH->ACR |= (0x1 << 4);
	RCC->CFGR  &= ~(0x1U << 16);
	RCC->CFGR  |= (0x1 << 16);          // cau hinh dau vao PLL la HSE
	RCC->CFGR  &= ~(0x7U << 8);         // cau hinh cac bo chia prescaler
	RCC->CFGR  |= (0x4 << 8);
	RCC->CFGR  &= ~(0xFU << 18);
	RCC->CFGR  |= (0x7 << 18); 
	RCC->CR    |= (0x1 << 24);          // bat PLL
	while(!((RCC->CR >> 25) & (0x1)));  // cho de PLL bat
	RCC->CFGR  &= ~(0x3U << 0);         //dat PLL la systemclock
	RCC->CFGR  |= (0x2 << 0);
	while ((0x2) != ((RCC->CFGR >> 2) & (0x3))); // cho PLL thanh systemclock
}
