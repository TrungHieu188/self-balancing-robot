#include "PID.h"

volatile float error_current;
volatile float error_pre;
volatile float error_sum;


float MPU_Calibrate(float *data, uint8_t x)
{
	uint16_t sample_count = 65535;
	float offset;
	float sum = 0;
	WritePin(PORTB, 1, 1);
	for (int i = 0; i < sample_count; i ++)
	{
		while(!(flag_dma))
		Data_MPU(data);
		sum += data[x];
	}
  offset = sum/ sample_count;
	WritePin(PORTB, 1, 0);
	return offset;
}

float Angle(float *data)
{
	static uint8_t x = 1;
	static float robot_angle = 0;
	float acc_angle, gyro_rate;
	acc_angle = (float)atan2((double)data[1], (double)data[2]) * 57.296f;
  if(x == 1)
	{
		robot_angle = acc_angle;
		x = 0;
	}
	gyro_rate = data[3] - GX_OFFSET;
	robot_angle = ALPHA * (robot_angle + gyro_rate * DT) + (1.0f - ALPHA) * acc_angle;
	return (float)robot_angle;
}
float PID (float angle_current, float gyro_rate)
{
	static float error_current = 0;
	static float error_pre = 0;
	static float error_sum = 0;
	float P_term, D_term, I_term, PID_output;
	error_current = angle_current - SET_POINT;
	error_sum += error_current * DT;
  if(error_sum > 1800) error_sum = 1800;
  if(error_sum < -1800) error_sum = -1800;
	P_term = KP * error_current;
  I_term = KI * error_sum;
	D_term = KD * gyro_rate;
	error_pre = error_current;
	PID_output = P_term + I_term + D_term;
  if (PID_output > 3600) PID_output = 3600;
  if (PID_output < -3600) PID_output = -3600;
	return PID_output;
}
