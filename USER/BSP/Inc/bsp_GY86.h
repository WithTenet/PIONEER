#ifndef  __MPU6050__H
#define  __MPU6050__H
#include "stm32f4xx.h"


#define MPU6050_ADDRESS         0xD0
#define MPU6050_RA_WHO_AM_I     0x75     //查询设备地址
#define MPU6050_RA_SMPLRT_DIV   0x19     //采样率
#define MPU6050_GYRO_OUT        0x43     //MPU6050陀螺仪数据寄存器地址
#define MPU6050_ACC_OUT         0x3B     //MPU6050加速度数据寄存器地址
#define MPU6050_RA_PWR_MGMT_1   0x6B     //电源管理寄存器地址
#define MPU6050_RA_CONFIG       0x1A     //
#define MPU6050_RA_GYRO_CONFIG  0x1B     //陀螺仪配置寄存器
#define MPU6050_RA_ACCEL_CONFIG 0x1C     //加速度配置寄存器
#define MPU6050_RA_TEMP_OUT_H   0x41     //MPU6050温度数据寄存器地址
#define MPU6050_RA_USER_CTRL    0x6A     //用户控制寄存器
#define MPU6050_RA_INT_PIN_CFG  0x37     //中断旁路寄存器

/**
 * @brief 外部接口
 * 
 */
void MPU6050_Init(void);
uint8_t MPU6050ReadID(void);
int MPU6050ReadAcc(uint8_t *accData);
int MPU6050ReadGyro(uint8_t *gyroData);

/**
 * @brief 内部接口
 * 
 */
static int IIC_Byte_Write(unsigned char slave_addr,unsigned char reg_addr,unsigned short lens,unsigned char* data);
static int IIC_Byte_Read(unsigned char slave_addr,unsigned char reg_addr,unsigned short lens,unsigned char* data);
static int Sensor_Read(uint8_t slave_addr,uint8_t reg_addr,unsigned short lens,uint8_t* data);
static int Sensor_Write(uint8_t slave_addr,uint8_t reg_addr,unsigned short lens,uint8_t* data);
#endif
