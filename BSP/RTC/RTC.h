#ifndef __RTC_H
#define __RTC_H

#include "stm32f4xx.h" 



/*****************************************************************************
 ** 全局变量
****************************************************************************/
typedef struct
{
    uint8_t   InitFlag;       // 初始化标记; 0=未初始化, 1=已初始化
    uint16_t  Year;           // 年，  20xx, 00~99
    uint8_t   Month;          // 月，  1~12
    uint8_t   Day;            // 日，  1~31
    uint8_t   Week;           // 星期，1~7
    uint8_t   Hour;           // 时,   0~24
    uint8_t   Minute;         // 分,   0~59
    uint8_t   Second;         // 秒，  0~59
    uint8_t   WeekChinese[3]; // 星期，”一"~"日"
} xRTC_TypeDef; 
extern xRTC_TypeDef xRTC;;    // 用于记录实时时间，当调用RTC_Update()后，数据被更新一次



/*****************************************************************************
 ** 声明全局函数
****************************************************************************/
uint8_t RTC_Config(void);
uint8_t RTC_Set(uint16_t year, uint8_t month, uint8_t day, uint8_t week, uint8_t hour, uint8_t minute, uint8_t second);
uint8_t RTC_Update(void);


#endif

