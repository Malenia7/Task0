//MPU6050 6--axis sensor driver
#ifndef __BSP_MPU6050_I2C_H__
#define __BSP_MPU6050_I2C_H__

#include "main.h"

// MPU6050 I2C地址
#define MPU6050_ADDRESS 0x69

// MPU6050寄存器定义
#define SMPLRT_DIV      0x19  // 陀螺仪采样率寄存器
//#define CONFIG          0x1A  // 配置寄存器
#define GYRO_CONFIG     0x1B  // 陀螺仪配置寄存器
#define ACCEL_CONFIG    0x1C  // 加速度计配置寄存器
#define PWR_MGMT_1      0x6B  // 电源管理寄存器
//#define WHO_AM_I        0x75  // MPU6050设备ID寄存器

#define ACCEL_XOUT_H    0x3B  // 加速度计X轴高字节
#define ACCEL_XOUT_L    0x3C  // 加速度计X轴低字节
#define ACCEL_YOUT_H    0x3D  // 加速度计Y轴高字节
#define ACCEL_YOUT_L    0x3E  // 加速度计Y轴低字节
#define ACCEL_ZOUT_H    0x3F  // 加速度计Z轴高字节
#define ACCEL_ZOUT_L    0x40  // 加速度计Z轴低字节
#define TEMP_OUT_H      0x41  // 温度传感器高字节
#define TEMP_OUT_L      0x42  // 温度传感器低字节
#define GYRO_XOUT_H     0x43  // 陀螺仪X轴高字节
#define GYRO_XOUT_L     0x44  // 陀螺仪X轴低字节
#define GYRO_YOUT_H     0x45  // 陀螺仪Y轴高字节
#define GYRO_YOUT_L     0x46  // 陀螺仪Y轴低字节
#define GYRO_ZOUT_H     0x47  // 陀螺仪Z轴高字节
#define GYRO_ZOUT_L     0x48  // 陀螺仪Z轴低字节


extern int16_t AccX, AccY, AccZ;
extern int16_t GyroX, GyroY, GyroZ;


void mpu6050_init(void);
void ReadMPU6050Data(int16_t* accX, int16_t* accY, int16_t* accZ, 
					 int16_t* gyroX, int16_t* gyroY, int16_t* gyroZ);

void test();

#endif
