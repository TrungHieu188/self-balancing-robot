#include "motor.h"

void PWM1_Init(void)
{
	RCC->APB1ENR |= (1 << 2);         //clock cho timer4
	GPIO(PORTB, 9, OUTPUT50, AFOPP);  // cau hinh chan cho B9
	TIM4->PSC = 0;                    // chia tan so
	TIM4->ARR = 3599;                 //cau hinh do phan giai(giong adc)
	// chon che do output compare
	TIM4->CCMR2 &= ~(3 << 8);
	//gia tri thanh ghi CCR1 duoc cap nhat sau khi thuc hien xong 1 chu ki PWM truoc do
	TIM4->CCMR2 |= (1 << 11);
	//chon che do pwm
	TIM4->CCMR2 &= ~(7 << 12);
	TIM4->CCMR2 |= (6 << 12);
	// cau hinh chan de set chieu quay
	GPIO(PORTB, 8, 3, 3);  
	GPIO(PORTB, 5, 3, 3);
	//Bat ngoai vi
	TIM4->CR1  |= (1 << 7);
	TIM4->EGR  |= (1 << 0);			
	TIM4->CCER |= (1 << 12);
  TIM4->CR1  |= (1 << 0);
}
void PWM1(float pwm)
{
	TIM4->CCR4 = (uint16_t)pwm;
}
void PWM_Motor1(uint8_t chieu, float pwm)
{
	if (chieu == 1)
	{
		WritePin(PORTB, 8, 1);
		WritePin(PORTB, 5, 0);
		PWM1(pwm);
	}
	else 
	{
		WritePin(PORTB, 8, 0);
		WritePin(PORTB, 5, 1);
		PWM1(pwm);
	}
}
void PWM2_Init(void)
{
	RCC->APB2ENR |= (1 << 11);         //clock cho timer 1
	GPIO(PORTA, 8, OUTPUT50, AFOPP);  // cau hinh chan cho A8
	TIM1->PSC = 0;                    // chia tan so
	TIM1->ARR = 3599;                 //cau hinh do phan giai(giong adc)
	// chon che do output compare
	TIM1->CCMR1 &= ~(3 << 0);
	//gia tri thanh ghi CCR1 duoc cap nhat sau khi thuc hien xong 1 chu ki PWM truoc do
	TIM1->CCMR1 |= (1 << 3);
	//chon che do pwm
	TIM1->CCMR1 &= ~(7 << 4);
	TIM1->CCMR1 |= (6 << 4);
	//bat MOE
	TIM1->BDTR |= (1 << 15);
	// cau hinh chan de set chieu quay
	GPIO(PORTA, 11, 3, 3);
	GPIO(PORTA, 12, 3, 3);
	//Bat ngoai vi
	TIM1->CR1  |= (1 << 7);
	TIM1->EGR  |= (1 << 0);			
	TIM1->CCER |= (1 << 0);
  TIM1->CR1  |= (1 << 0);
}
void PWM2(float pwm)
{
	TIM1->CCR1 = (uint16_t)pwm;
}
void PWM_Motor2(uint8_t chieu, float pwm)
{
	if (chieu == 1)
	{
		WritePin(PORTA, 11, 1);
		WritePin(PORTA, 12, 0);
		PWM2(pwm);
	}
	else 
	{
		WritePin(PORTA, 11, 0);
		WritePin(PORTA, 12, 1);
		PWM2(pwm);
	}
}
void PWM_Init(void)
{
	PWM1_Init();
	PWM2_Init();
}
void Encoder1_Init(void)
{
	GPIO(PORTA, 6, INPUT, PUPD);    //input push pull tro keo len
	WritePin(PORTA, 6, 1);
	GPIO(PORTA, 7, INPUT, PUPD);    //input push pull tro keo len
	WritePin(PORTA, 7, 1);
	RCC->APB1ENR |= (1 << 1);       //clock timer3
	TIM3->SMCR   &= ~(0x7U << 0);   //cau hinh dem 2 kenh
	TIM3->SMCR   |= (3 << 0);
	TIM3->CCMR1 &= ~(3<<0);
	TIM3->CCMR1  |= (1<<0);         //map CH1 cho TI1 (chon nguon la CH1 va CH2  vao TI1 va TI2 vi so sanh la so sanh TI1 va TI2)
	TIM3->CCMR1 &= ~(3<<8);
	TIM3->CCMR1  |= (1<<8);         //map CH2 cho TI2
	TIM3->CCER   = 0;               //CH1 va CH2 deu dem canh len
	TIM3->ARR = 0xFFFF;             //auto reload max
  TIM3->CNT = 0;                  //reset counter
	//Bat ngoai vi
	TIM3->CR1  |= (1 << 7);
	TIM3->EGR  |= (1 << 0);			
	TIM3->CCER |= (1 << 8);
  TIM3->CR1  |= (1 << 0);
}
void Encoder2_Init(void)
{
	GPIO(PORTA, 0, INPUT, PUPD);    //input push pull tro keo len
	WritePin(PORTA, 0, 1);
	GPIO(PORTA, 1, INPUT, PUPD);    //input push pull tro keo len
	WritePin(PORTA, 1, 1);
	RCC->APB1ENR |= (1 << 0);       //clock timer2
	TIM2->SMCR   &= ~(0x7U << 0);   //cau hinh dem 2 kenh
	TIM2->SMCR   |= (3 << 0);
	TIM2->CCMR1 &= ~(3<<0);
	TIM2->CCMR1  |= (1<<0);         //map CH1 cho TI1 (chon nguon la CH1 va CH2  vao TI1 va TI2 vi so sanh la so sanh TI1 va TI2)
	TIM2->CCMR1 &= ~(3<<8);
	TIM2->CCMR1  |= (1<<8);         //map CH2 cho TI2
	TIM2->CCER   = 0;               //CH1 va CH2 deu dem canh len
	TIM2->ARR = 0xFFFF;             //auto reload max
  TIM2->CNT = 0;                  //reset counter
	//Bat ngoai vi
	TIM2->CR1  |= (1 << 7);
	TIM2->EGR  |= (1 << 0);			
	TIM2->CCER |= (1 << 8);
  TIM2->CR1  |= (1 << 0);
}
void Encoder_Init(void)
{
	Encoder1_Init();
	Encoder2_Init();
}

