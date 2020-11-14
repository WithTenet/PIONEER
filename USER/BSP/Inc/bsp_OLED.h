#ifndef __OLED_H
#define __OLED_H	 

#include "stm32f4xx_hal.h"
#define u8 uint8_t
#define u32 uint32_t

/**
 * @brief OLED屏幕寄存器的地址
 * 
 */
#define OLED0561_ADD	0x78  // OLED的I2C地址（禁止修改）
#define COM				0x00  // OLED 指令（禁止修改）
#define DAT 			0x40  // OLED 数据（禁止修改）

/**
 * @brief OLED屏幕的外部接口
 * OLED_Init()  OLED屏幕初始化≤
 * 
 */

void bsp_OLED_Init(void);//初始化
void bsp_OLED_SetPos(unsigned char x, unsigned char y);
void bsp_OLED_Fill(unsigned char fill_Data);//全屏填充
void bsp_OLED_CLR(void);
void bsp_OLED_ON(void);
void bsp_OLED_OFF(void);
void bsp_OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);//显示字符串
void bsp_OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);//显示汉字
void bsp_OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//显示图片（取模：阴，列行，逆，输出索引，精简）

void bsp_OLED_ShowCN_STR(u8 x , u8 y , u8 begin , u8 num);  //自己写的输出中文字符串

void bsp_OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
u32  bsp_OLED_pow(u8 m,u8 n);
void bsp_OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);//size2(16|12)

static void WriteCmd(unsigned char I2C_Command);//写命令
static void WriteDat(unsigned char I2C_Data);//写数据


/**
 * @brief 使用案例
 * /
 /*****************
	OLED_ShowStr(0, 0, "hello world", 2);//显示字符串
    OLED_ShowStr(0, 2, "hello world", 1);//显示字符串
	OLED_ShowCN_STR(0, 4 , 0 , 8);
	sprintf(num_temp_buffer,"show num:%0.2f",num);
	OLED_ShowStr(0, 6, num_temp_buffer, 2);//显示字符串
	OLED_CLS();
	OLED_DrawBMP(0,0,128,7,BMP2);

 */

#endif


