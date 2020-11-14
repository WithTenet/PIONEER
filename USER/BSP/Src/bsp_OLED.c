#include "bsp_OLED.h"
#include "bsp_ascii.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

/**
 * @brief 基本的两个I2C输入输出命令
 *
 * @param I2C_Command 
 * 如果需要重新定向到另外的I2C，更改两个函数的内容 hi2c2
 */

static void WriteCmd(unsigned char I2C_Command);//写命令
static void WriteDat(unsigned char I2C_Data);//写数据

/**
 * @brief OLED 屏幕初始化
 * 
 */
void bsp_OLED_Init(void)
{
	HAL_Delay(100); //这里的延时很重要
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

/**
 * @brief 设置起始点坐标
 * 
 * @param x 
 * @param y 
 */
void bsp_OLED_SetPos(unsigned char x, unsigned char y) 
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}



/**
 * @brief 全屏幕显示
 * 
 * @param fill_Data 
 */
void bsp_OLED_Fill(unsigned char fill_Data)
{ 
	unsigned char m,n;
	for(m=0;m<8;m++)
    {
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
        {
			WriteDat(fill_Data);
		}
	}
}

/**
 * @brief 全屏幕清空
 * 
 */
void bsp_OLED_CLR(void)
{
	bsp_OLED_Fill(0x00);
}

/**
 * @brief bsp_OLED屏幕启动
 * 
 */
void bsp_OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

/**
 * @brief bsp_OLED屏幕关闭
 * 
 */
void bsp_OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}



/**
 * @brief 字符串显示
 * 
 * @param x 起始坐标x
 * @param y 起始坐标y
 * @param ch[] 要显示字符串
 * @param TextSize 文字大小 1:6*8   2:8*16
 */
void bsp_OLED_ShowStr(unsigned char x, unsigned char y, unsigned char *ch, unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
    {
		case 1:
        {
			while(ch[j] != '\0')
            {
				c = ch[j] - 32;
				if(x > 126)
                {
					x = 0;
					y++;
				}
				bsp_OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
        {
			while(ch[j] != '\0')
            {
				c = ch[j] - 32;
				if(x > 120)
                {
					x = 0;
					y++;
				}
				bsp_OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				bsp_OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}


/**
 * @brief 中文显示
 * 
 * @param x 起始点坐标X
 * @param y 起始点坐标Y
 * @param N 要显示的汉字
 */
void bsp_OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	bsp_OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	bsp_OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}




// 这是自己写的显示中文字符串的函数，要先把中文字符串“共阴——列行式——逆向输出”取字模后存入ascll.h相应的位置(连续存入)
//传入参数分别为：x:起始横坐标  
//								y：纵坐标(填入0-7)  
//								begin:填入的中文字符串的第一个字在我们ascll.c字库里面的序号  
//                num:我们要填写几个字
//                比如要填“测试”，取完字模存入后这两个字在字库中序号为0,1,横坐标0，纵坐标第二行，就填：x：0，y：2，begin：0，num：2
void bsp_OLED_ShowCN_STR(u8 x , u8 y , u8 begin , u8 num)
{
	u8 i;
	for(i=0;i<num;i++)
    {
        bsp_OLED_ShowCN(i*16+x,y,i+begin);
    }    //OLED显示标题
}



// Parameters     : x0,y0 -- ; x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
/**
 * @brief 
 * 
 * @param x0 起始坐标点 起始点坐标(x0:0~127, y0:0~7)
 * @param y0 
 * @param x1 结束点坐标  起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
 * @param y1 
 * @param BMP 显示BMP位图
 */
void bsp_OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
        bsp_OLED_SetPos(x0,y);
        for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}

/**
 * @brief 显示单个字母
 * 
 * @param x 起始点坐标 
 * @param y 
 * @param chr 字符
 * @param Char_Size  
 */
void bsp_OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';//得到偏移后的值			
	if(x>128-1){x=0;y=y+2;}
	if(Char_Size ==16)
	{
		bsp_OLED_SetPos(x,y);	
		for(i=0;i<8;i++)
		WriteDat(F8X16[c*16+i]);
		bsp_OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
		WriteDat(F8X16[c*16+i+8]);
	}
	else 
    {	
		bsp_OLED_SetPos(x,y);
		for(i=0;i<6;i++)
		WriteDat(F6x8[c][i]);	
	}
}



u32 bsp_OLED_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);
/**
 * @brief 显示数字
 * 
 * @param x 起始坐标
 * @param y 
 * @param num 要显示的数值
 * @param len 数字位数
 * @param size2 大小
 */
void bsp_OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/bsp_OLED_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				bsp_OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		}
	 	bsp_OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

/**
 * @brief 对OLED进行指令数据写入
 * 
 * @param I2C_Command 
 */
static void WriteCmd(unsigned char I2C_Command)
{
	HAL_I2C_Mem_Write(&hi2c2,OLED0561_ADD,COM,I2C_MEMADD_SIZE_8BIT,&I2C_Command,1,100);
}

/**
 * @brief 对OLED进行显示数据写入
 * 
 * @param I2C_Data 
 */
static void WriteDat(unsigned char I2C_Data)
{
	HAL_I2C_Mem_Write(&hi2c2,OLED0561_ADD,DAT,I2C_MEMADD_SIZE_8BIT,&I2C_Data,1,100);
}
