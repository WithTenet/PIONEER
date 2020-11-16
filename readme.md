# vscode打开出现问题解决方案





# 一般使用指令
 STM32_Programmer_CLI -c port=SWD -d build/PIONEER.bin 0x8000000 -s




echo "# PIONEER" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/WithTenet/PIONEER.git
git push -u origin main
                


# 开发日记
2020 11 14 
今天增加了TIM1的4个通道捕获 // 应该加锁进行访问。
TIM8的四通道输出还没有完成  // 应该加锁
2020 11 16
完成了四个通道的TIM捕获，遇到的问题是，没有判断中断的来源，导致了多个通道捕获的时候，会产生信号冲突。要注意，如果重新生成工程，需要重新写Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c 文件的 第3171行代码
代码如下

/***********************************************************
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
{
  /* Capture compare 1 event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) != RESET)
    {
      {
        __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
        htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;

        /* Input capture event */
        if ((htim->Instance->CCMR1 & TIM_CCMR1_CC1S) != 0x00U)
        {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
          htim->IC_CaptureCallback(htim);
#else
          //HAL_TIM_IC_CaptureCallback(htim);
    switch(capture_Cnt[0]){
			case 0:
				capture_Buf[0][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				capture_Cnt[0]++;
				break;
			case 1:
				capture_Buf[0][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //停止捕获 ;
				high_time[0] = capture_Buf[0][1]- capture_Buf[0][0];
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING); 
				HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
				capture_Cnt[0] = 0;
				break; 
		}
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
        }
        /* Output compare event */
        else
        {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
          htim->OC_DelayElapsedCallback(htim);
          htim->PWM_PulseFinishedCallback(htim);
#else
          HAL_TIM_OC_DelayElapsedCallback(htim);
          HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
        }
        htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
      }
    }
  }
  /* Capture compare 2 event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;
      /* Input capture event */
      if ((htim->Instance->CCMR1 & TIM_CCMR1_CC2S) != 0x00U)
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->IC_CaptureCallback(htim);
#else
     //   HAL_TIM_IC_CaptureCallback(htim);
      switch(capture_Cnt[1]){
			case 0:
		 		capture_Buf[1][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_2);//获取当前的捕获值.
		 		__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
		 		capture_Cnt[1]++;
		 		break;
		 	case 1:
		 		capture_Buf[1][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_2);//获取当前的捕获值.
		 		HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_2); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
		 		high_time[1] = capture_Buf[1][1]- capture_Buf[1][0];
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_2,TIM_ICPOLARITY_RISING); 
				HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
				capture_Cnt[1] = 0;
		 		break;
		 }
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
      }
      /* Output compare event */
      else
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->OC_DelayElapsedCallback(htim);
        htim->PWM_PulseFinishedCallback(htim);
#else
        HAL_TIM_OC_DelayElapsedCallback(htim);
        HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
      }
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    }
  }
  /* Capture compare 3 event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;
      /* Input capture event */
      if ((htim->Instance->CCMR2 & TIM_CCMR2_CC3S) != 0x00U)
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->IC_CaptureCallback(htim);
#else
       // HAL_TIM_IC_CaptureCallback(htim);
      switch(capture_Cnt[2]){
		 	case 0:
		 		capture_Buf[2][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//获取当前的捕获值.
		 		__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_3,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
		 		capture_Cnt[2]++;
		 		break;
		 	case 1:
				capture_Buf[2][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_3);//获取当前的捕获值.
		 		HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_3); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
				high_time[2] = capture_Buf[2][1]- capture_Buf[2][0];
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING); 
				HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
				capture_Cnt[2] = 0;
		 		break;   
		}
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
      }
      /* Output compare event */
      else
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->OC_DelayElapsedCallback(htim);
        htim->PWM_PulseFinishedCallback(htim);
#else
        HAL_TIM_OC_DelayElapsedCallback(htim);
        HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
      }
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    }
  }
  /* Capture compare 4 event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;
      /* Input capture event */
      if ((htim->Instance->CCMR2 & TIM_CCMR2_CC4S) != 0x00U)
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->IC_CaptureCallback(htim);
#else
      //  HAL_TIM_IC_CaptureCallback(htim);
         switch(capture_Cnt[3]){
		 	case 0:
		 		capture_Buf[3][0] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_4);//获取当前的捕获值.
		 		__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
		 		capture_Cnt[3]++;
		 		break;
		 	case 1:
		 		capture_Buf[3][1] = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_4);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_4);
				high_time[3] = capture_Buf[3][1]- capture_Buf[3][0];
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING); 
				HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_4);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
				capture_Cnt[3] = 0;
		 		break;     
		 }
		 
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
      }
      /* Output compare event */
      else
      {
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
        htim->OC_DelayElapsedCallback(htim);
        htim->PWM_PulseFinishedCallback(htim);
#else
        HAL_TIM_OC_DelayElapsedCallback(htim);
        HAL_TIM_PWM_PulseFinishedCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
      }
      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
    }
  }
  /* TIM Update event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_UPDATE) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->PeriodElapsedCallback(htim);
#else
      HAL_TIM_PeriodElapsedCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
    }
  }
  /* TIM Break input event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_BREAK) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_BREAK) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_BREAK);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->BreakCallback(htim);
#else
      HAL_TIMEx_BreakCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
    }
  }
  /* TIM Trigger detection event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_TRIGGER) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_TRIGGER) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_IT_TRIGGER);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->TriggerCallback(htim);
#else
      HAL_TIM_TriggerCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
    }
  }
  /* TIM commutation event */
  if (__HAL_TIM_GET_FLAG(htim, TIM_FLAG_COM) != RESET)
  {
    if (__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_COM) != RESET)
    {
      __HAL_TIM_CLEAR_IT(htim, TIM_FLAG_COM);
#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
      htim->CommutationCallback(htim);
#else
      HAL_TIMEx_CommutCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
    }
  }
}
*******************************************/

