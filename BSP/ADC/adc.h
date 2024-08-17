#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"



/*****************************************************************************
 ** ����ȫ�ֺ���
*****************************************************************************/
float    ADC1_GetVoltage(GPIO_TypeDef *GPIOx, uint32_t PINx);    // ��ȡͨ�������ϵ�ģ���ѹֵ; GPIOx��ѡֵ: GPIOA~GPIOG, PINxȡֵ��Χ��GPIO_Pin_0 ~ GPIO_Pin_15
float    ADC1_GetInternalTemperature(void);                      // ��ȡADC1оƬ�ڲ��¶�ֵ; ��Χ��-40~125�ȣ����ȣ��� 1.5������; �����ѻ���õ����϶�ֵ����ADCֵ

#endif


