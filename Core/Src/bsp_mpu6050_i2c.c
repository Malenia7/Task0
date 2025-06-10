#include "bsp_mpu6050_i2c.h"
#include "i2c.h"
#include "usart.h"
#include "stdio.h"

int16_t AccX, AccY, AccZ;			//3轴加速度
int16_t GyroX, GyroY, GyroZ;		//3轴陀螺仪


void mpu6050_init(void)
{
    uint8_t reg_buf[1];	

	// 唤醒MPU6050
    reg_buf[0] = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS << 1, PWR_MGMT_1, 
					  I2C_MEMADD_SIZE_8BIT, reg_buf, 1, 100);

    // 设置采样率
    reg_buf[0] = 0x07; // 125Hz
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS << 1, SMPLRT_DIV, 
					  I2C_MEMADD_SIZE_8BIT, reg_buf, 1, 100);

    // 配置陀螺仪
    reg_buf[0] = 0x18; // 陀螺仪范围±2000°/s
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS << 1, GYRO_CONFIG, 
					  I2C_MEMADD_SIZE_8BIT, reg_buf, 1, 100);

    // 配置加速度计
    reg_buf[0] = 0x01; // 加速度计范围±2g
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS << 1, ACCEL_CONFIG, 
					  I2C_MEMADD_SIZE_8BIT, reg_buf, 1, 100);

    //HAL_Delay(10);
}

// 读取MPU6050的数据
inline void ReadMPU6050Data(int16_t* accX, int16_t* accY, int16_t* accZ, 
                            int16_t* gyroX, int16_t* gyroY, int16_t* gyroZ)
{
    uint8_t readBuffer[14];

    // 读取加速度计和陀螺仪的原始数据
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDRESS << 1, ACCEL_XOUT_H, 
                     I2C_MEMADD_SIZE_8BIT, readBuffer, 14, 100);
	
    *accX  = (int16_t)((readBuffer[0]  << 8) | readBuffer[1]);
    *accY  = (int16_t)((readBuffer[2]  << 8) | readBuffer[3]);
    *accZ  = (int16_t)((readBuffer[4]  << 8) | readBuffer[5]);
	*gyroX = (int16_t)((readBuffer[8]  << 8) | readBuffer[9]);
    *gyroY = (int16_t)((readBuffer[10] << 8) | readBuffer[11]);
    *gyroZ = (int16_t)((readBuffer[12] << 8) | readBuffer[13]);

	//将原始数据转化为单精度浮点数
	float accX_f  = *accX  / 16384.0; 		//-2 ~ 2g量程，灵敏度为 4 / 2^16 = 16384
	float accY_f  = *accY  / 16384.0;
	float accZ_f  = *accZ  / 16384.0;
	float gyroX_f = *gyroX / 32.7;			//-2000 ~ 2000dps量程，灵敏度为 4000 / 2^16 = 32.7
	float gyroY_f = *gyroY / 32.7;	
	float gyroZ_f = *gyroZ / 32.7;

	printf("acc_x:  %+7.2fg      acc_y:  %+7.2fg      acc_z:  %+7.2fg\n", 
		accX_f, accY_f, accZ_f);
	printf("gyro_x: %+7.2fdps    gyro_y: %+7.2fdps    gyro_z: %+7.2fdps\n", 
		gyroY_f, gyroY_f, gyroZ_f);
    HAL_Delay(3000);
}

