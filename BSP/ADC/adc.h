#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"



/*****************************************************************************
 ** 声明全局函数
*****************************************************************************/
float    ADC1_GetVoltage(GPIO_TypeDef *GPIOx, uint32_t PINx);    // 获取通道引脚上的模拟电压值; GPIOx可选值: GPIOA~GPIOG, PINx取值范围：GPIO_Pin_0 ~ GPIO_Pin_15
float    ADC1_GetInternalTemperature(void);                      // 获取ADC1芯片内部温度值; 范围：-40~125度，精度：± 1.5℃左右; 返回已换算好的摄氏度值，非ADC值

#endif


