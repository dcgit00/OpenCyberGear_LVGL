#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"
#include <stdio.h>





//移植参数区 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  LED_RED_GPIO      GPIOC
#define  LED_RED_PIN       GPIO_Pin_5   

#define  LED_BLUE_GPIO     GPIOB
#define  LED_BLUE_PIN      GPIO_Pin_2
//END 移植 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



// 按色简化功能, 移植时不用修改
// red                      
#define LED_RED_ON         (LED_RED_GPIO->BSRRH = LED_RED_PIN)     // 点亮，置低电平
#define LED_RED_OFF        (LED_RED_GPIO->BSRRL = LED_RED_PIN)     // 熄灭，置高电平
#define LED_RED_TOGGLE     (LED_RED_GPIO->ODR  ^= LED_RED_PIN)     // 反转，电平取反
// blue
#define LED_BLUE_ON        (LED_BLUE_GPIO->BSRRH  = LED_BLUE_PIN)  // 点亮，置低电平
#define LED_BLUE_OFF       (LED_BLUE_GPIO->BSRRL  = LED_BLUE_PIN)  // 熄灭，置高电平
#define LED_BLUE_TOGGLE    (LED_BLUE_GPIO->ODR   ^= LED_BLUE_PIN)  // 反转，电平取反



/*****************************************************************************
 ** 声明全局函数
****************************************************************************/
void Led_Init(void);



#endif

