#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f4xx.h"

#include "lvgl.h"
#include "xpt2046.h"


void TIM2_Init(void);
void  TIM2_IRQHandler (void);


#endif
