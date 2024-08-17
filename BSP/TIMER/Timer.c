#include "Timer.h"

/**
  * @brief  定时器2配置(1ms触发一次定时器中断)
  * @param  NONE
  * @retval NONE
  */
void TIM2_Init(void)
{   	
    /** 使能相关时钟 **/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);          // 使能定时器时钟 
	
    /** 配置TIM2中断优先级 **/
    NVIC_InitTypeDef NVIC_InitStructure;                          // 声明优先级配置结构体
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 	          // 中断通道来源		
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  // 抢占优先级	  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	          // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               // 使能通道
    NVIC_Init(&NVIC_InitStructure);                               // 配置写入寄存器

    /** 配置所用TIM的时基 **/
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;               // 声明时基配置结构体
    TIM_TimeBaseStructure.TIM_Prescaler = 84-1;	              // 分频; 把接口时钟分频后给计数器使用, 即多少个接口脉冲，才产生一次计数器脉冲; 简单理解：计算每一计数器脉冲的时长;
    TIM_TimeBaseStructure.TIM_Period = 1000-1;                    // ARR, 自动重载值; 多少个计数器脉冲作为一周期; 注意：TIM2和5是32位的，其它TIM是16位的;
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;         // 采样时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;     // 计数方式	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);               // 初始化定时器，把配置写入寄存器
	
	//t = (arr+1) * (psc+1) / Freq
	//t = (84-1+1) * (1000-1+1) / 84 000 000
	//t = 0.001
	
    /** 配置中断 **/
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);                         // 清除定时器更新中断标志位
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);	                  // 开启定时器更新中断

    /** 使能定时器 **/

	TIM_Cmd(TIM2, ENABLE);	                                      // 使能定时器            
}

// 中断服务函数
void  TIM2_IRQHandler (void)
{
	if ( TIM_GetITStatus( TIM2, TIM_IT_Update) != RESET ) 
	{	
		lv_tick_inc(1);	//LVGL定时器心跳
		XPT2046_TouchHandler();
		
		TIM_ClearITPendingBit(TIM2 , TIM_IT_Update);  		 
	}		 	
}

