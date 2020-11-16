#include "bsp_USART.h"

/**
 * @brief 输出重定向，将printf定向到串口发送
 * 
 * @param ch 发送的字符
 * @param f 文件指针
 * @return int 成功返回字符ascii码
 */

extern UART_HandleTypeDef huart3;

int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart3,temp,1,2);       
		return ch;
}
