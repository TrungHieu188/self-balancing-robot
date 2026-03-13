#ifndef __PID_H
#define __PID_H

#include "gpio.h"
#include "mpu6050.h"
#include "math.h"
#include "usbttl.h"
extern volatile float h;

#define GX_OFFSET        -1.663918f
#define ALPHA            0.98f
#define DT               0.005f
#define KP               2000.0f
#define KI               0.0f
#define KD               100.0f
#define SET_POINT        0.1f

extern volatile float error_current;
extern volatile float error_pre;
extern volatile float error_sum;

float MPU_Calibrate(float *data, uint8_t x);
float Angle(float *data);
float PID (float angle_current, float gyro_rate);



#endif
