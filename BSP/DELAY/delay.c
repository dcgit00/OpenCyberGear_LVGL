#include "delay.h"

/**
  * @brief  毫秒级延时
  * @param  延时时间(ms)
  * @retval None
  */
void delay_ms(uint32_t nms)
{
	while(nms--)
	{
		SysTick->CTRL = 0; // Disable SysTick，关闭系统定时器
		SysTick->LOAD = 21000-1; // 决定了延时时间
		SysTick->VAL  = 0; // Clear current value as well as count flag，清空当前计数值，也会清空COUNTFLAG标志位
		SysTick->CTRL|= 0x01; // Enable SysTick timer with processor clock，使用处理器时钟168MHz作为时钟源，并启动系统定时器开始计数
		while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set，检测SysTick->CTRL的COUNTFLAG标志位是否置1
	
	}
	SysTick->CTRL = 0; // Disable SysTick，关闭系统定时器
}

/**
  * @brief  微秒级延时
  * @param  延时时间(us)
  * @retval None
  */
void delay_us(uint32_t nus)
{
	SysTick->CTRL = 0; // Disable SysTick，关闭系统定时器
	SysTick->LOAD = nus*21-1; // 决定了延时时间
	SysTick->VAL  = 0; // Clear current value as well as count flag，清空当前计数值，也会清空COUNTFLAG标志位
	SysTick->CTRL|= 0x01; // Enable SysTick timer with processor clock，使用处理器时钟168MHz作为时钟源，并启动系统定时器开始计数
	while ((SysTick->CTRL & 0x00010000)==0);// Wait until count flag is set，检测SysTick->CTRL的COUNTFLAG标志位是否置1
			
	SysTick->CTRL = 0; // Disable SysTick，关闭系统定时器
	
}

