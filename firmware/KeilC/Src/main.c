#include "main.h"

int main (void)
{
	delayms(1);
	SysClock();
	float data1[6];
	USART1_Init();
	MPU_FIFO_INT_Config();
	GPIO(PORTC, 13, 3, 3);
	GPIO(PORTB, 1 ,3, 3);
	float angle = 0, pid_output;
	Encoder_Init();
	PWM_Init();
  WritePin(PORTC, 13, 0);
	while (1)
	{	
  if (flag_dma == 1)
	 {
	 Data_MPU(data1);
	 angle = Angle(data1);
	 pid_output = PID(angle, data1[4]);
	 if (pid_output < 0)
	 {
		 if(pid_output > -1000)
		 {
			 pid_output += -1000;
		 }
		 pid_output = -1 * pid_output;
		 PWM_Motor1(THUAN, pid_output);
	   PWM_Motor2(THUAN, pid_output);
	 }
	 else
	 {
		 if(pid_output < 1000)
		 {
			 pid_output += 1000;
		 }
		 PWM_Motor1(NGICH, pid_output);
	   PWM_Motor2(NGICH, pid_output);
	 }
	 
	 }
 }
}
