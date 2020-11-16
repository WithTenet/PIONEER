#include "bsp_GY86.h"

extern I2C_HandleTypeDef hi2c1;

/**
 * @brief MPU6050оƬ初始化
 * 
 */
void MPU6050_Init(void){
    uint8_t data;
    //唤醒MPU6050
    data=0x00;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_PWR_MGMT_1,1,&data);
    //MPU配置
    data=0x00;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_CONFIG,1,&data);
    //写入采样率 1K
    data=0x07;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_SMPLRT_DIV,1,&data); 
    
    //加速度计配置   4G
    data=0x08;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_ACCEL_CONFIG,1,&data);
    //陀螺仪配置   2000
    data=0x18;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_GYRO_CONFIG,1,&data);
    //I2C_MST关
    data=0xC0;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_USER_CTRL,1,&data);  
    //打开旁通模式
    data=0x82;
    Sensor_Write(MPU6050_ADDRESS,MPU6050_RA_INT_PIN_CFG,1,&data);
}



/**
 * @brief 读取MPU6050器件ID
 * 
 * @return uint8_t 成功返回0失败返回1
 */
uint8_t MPU6050ReadID(void)
{
	unsigned char Re = 0;
    Sensor_Read(MPU6050_ADDRESS,MPU6050_RA_WHO_AM_I,1,&Re);    
    
	if(Re != 0x68)
	{
		printf("MPU6050 dectected error!\r\n");
		return 0;
	}
	else
	{
		printf("MPU6050 ID = %d\r\n",Re);
		return 1;
	}		
}

/**
 * @brief 读取加速度计数据
 * 
 * @param accData 加速度计数据存储指针
 * @return int 成功返回1
 */
int MPU6050ReadAcc(uint8_t *accData)
{
  Sensor_Read(MPU6050_ADDRESS,MPU6050_ACC_OUT,6, accData);
	return 1;
}

/**
 * @brief 读取陀螺仪数据
 * 
 * @param gyroData 陀螺仪 数据存储指针
 * @return int 成功返回1
 */
int MPU6050ReadGyro(uint8_t *gyroData)
{
    Sensor_Read(MPU6050_ADDRESS,MPU6050_GYRO_OUT,6,gyroData); //��ȡ���������ֽ�����
		return 1;
}


/**
 * @brief 写入传感器
 * 
 * @param slave_addr 
 * @param reg_addr 
 * @param lens 
 * @param data 
 * @return int 
 */

static int Sensor_Write(uint8_t slave_addr,uint8_t reg_addr,unsigned short lens,uint8_t* data){
    int ret=0;
    ret = 0;
    ret = IIC_Byte_Write( slave_addr, reg_addr, lens, data);
    return ret;
}

/**
 * @brief 读取传感器
 * 
 * @param slave_addr 
 * @param reg_addr 
 * @param lens 
 * @param data 
 * @return int 
 */
static int Sensor_Read(uint8_t slave_addr,uint8_t reg_addr,unsigned short lens,uint8_t* data){
    int ret=0;
    ret = 0;
    ret = IIC_Byte_Read( slave_addr, reg_addr, lens, data);
    return ret;
}

/**
 * @brief 包装库函数 实现 I2C写入字节
 * 
 * @param slave_addr 
 * @param reg_addr 
 * @param lens 
 * @param data 
 * @return int 
 */
static int IIC_Byte_Write(unsigned char slave_addr,unsigned char reg_addr,unsigned short lens,unsigned char* data){
	HAL_I2C_Mem_Write(&hi2c1, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, data, lens, 100);
	return 0;
}

/**
 * @brief 包装库函数 I2C读字节
 * 
 * @param slave_addr 
 * @param reg_addr 
 * @param lens 
 * @param data 
 * @return int 
 */
static int IIC_Byte_Read(unsigned char slave_addr,unsigned char reg_addr,unsigned short lens,unsigned char* data){
	HAL_I2C_Mem_Read(&hi2c1, slave_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, data, lens, 100);
	return 0;

}
