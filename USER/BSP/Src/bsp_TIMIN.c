#include "bsp_TIMIN.h"
/**
 * @brief 数据存储结构
 * 
 */
extern unsigned int capture_Buf[4][2]; //存放计数值
extern unsigned int capture_Cnt[4] ;//状态标志位
extern unsigned int high_time[4]; //高电平时间
extern  TIM_HandleTypeDef htim1;



/**
 * @brief TIM捕获中需要在Task中使用本函数，完成PWM的高电平时间获取
 * 
 */

void bsp_TIMIN_C(void)
{
    // Channel 1
    switch (capture_Cnt[0])
    {
	    case 0:
		    capture_Cnt[0]++;
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
		    break;
	    case 3:
		    high_time[0] = capture_Buf[0][1]- capture_Buf[0][0];    //高电平时间
		    capture_Cnt[0] = 0;  //清空标志位
			break;
    }

    // Channel 2
    switch (capture_Cnt[1])
    {
	    case 0:
		    capture_Cnt[1]++;
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
		    break;
	    case 3:
		    high_time[1] = capture_Buf[1][1]- capture_Buf[1][0];    //高电平时间
		    capture_Cnt[1] = 0;  //清空标志位
			break;
    }

    // Channel 3
    switch (capture_Cnt[2])
    {
	    case 0:
		    capture_Cnt[2]++;
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
		    break;
	    case 3:
		    high_time[2] = capture_Buf[2][1]- capture_Buf[2][0];    //高电平时间
		    capture_Cnt[2] = 0;  //清空标志位
			break;
    }
    
    // Channel 4
    switch (capture_Cnt[3])
    {
	    case 0:
		    capture_Cnt[3]++;
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_RISING);
            HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
		    break;
	    case 3:
		    high_time[3] = capture_Buf[3][1]- capture_Buf[3][0];    //高电平时间
		    capture_Cnt[3] = 0;  //清空标志位
			break;
    }




}















/**
 * @brief 函数是在中断服务函数中被调用，转换中断触发条件
 * 
 * @param htim 
 */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(TIM1 == htim->Instance)
	{   
        //Channel 1 caputure interrupt
		switch(capture_Cnt[0]){
			case 1:
				capture_Buf[0][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt[0]++;
				break;
			case 2:
				capture_Buf[0][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //停止捕获 ;
				capture_Cnt[0]++; 
				break; 
		}

        //Channel 2 caputure interrupt
        switch(capture_Cnt[1]){
			case 1:
				capture_Buf[1][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_2);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt[1]++;
				break;
			case 2:
				capture_Buf[1][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				capture_Cnt[1]++; 
				break;
		}

        //Channel 3 caputure interrupt
        switch(capture_Cnt[2]){
			case 1:
				capture_Buf[2][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt[2]++;
				break;
			case 2:
				capture_Buf[2][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				capture_Cnt[2]++; 
				break;   
		}

        //Channel 4 caputure interrupt
        switch(capture_Cnt[3]){
			case 1:
				capture_Buf[3][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt[3]++;
				break;
			case 2:
				capture_Buf[3][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				capture_Cnt[3]++;
				break;    
		}
	
	}
	
}

