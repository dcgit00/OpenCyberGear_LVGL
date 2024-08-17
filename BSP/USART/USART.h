#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>
#include "string.h"       // C标准库头文件: 字符数组常用：strcpy()、strncpy()、strcmp()、strlen()、strnset()
#include "lvgl.h"



/*****************************************************************************
 ** 移植配置
 ** (大部份情况下都不用修改,如蓝牙通信、ESP8266通信、串口屏等)
****************************************************************************/
// 数据接收缓冲区大小
#define USART1_RX_BUF_SIZE           1024             // 配置每个USARTx接收缓冲区的大小(字节数)，包括中断里的缓存大小，和xUSART结构体里的缓存区大小
#define USART2_RX_BUF_SIZE           1024             // --- 当每帧接收到的数据字节数，小于此值时，数据正常；剩余空间数据为: 0
#define USART3_RX_BUF_SIZE           1024             // --- 当每帧接收到的数据字节数，超过此值时，超出部分，将在中断中直接弃舍，直到接收结束(发生空闲中断); 
#define UART4_RX_BUF_SIZE            1024             // --- 有效区域：仅在各个USARTx的中断服务函数中工作；
#define UART5_RX_BUF_SIZE            1024             // --- 主要作用:  1:配合空闲中断接收数据帧;  2:灵活配置缓存大小;  3:防止数据溢出!!!!
#define USART6_RX_BUF_SIZE           1024


/*****************************************************************************
 ** 全局变量
****************************************************************************/
typedef struct
{
    uint8_t   InitFlag;                               // 初始化标记; 0=未初始化, 1=已初始化
    uint16_t  ReceivedNum;                            // 接收到多少个字节数据
    uint8_t   ReceivedData[USART1_RX_BUF_SIZE];       // 存放接收到的一帧完整数据; 存放的是空闲中断后，从临时缓存复制过来的完整数据包，非接收过程中的不完整数据;
} xUSATR_TypeDef;                                    
                                                     
extern xUSATR_TypeDef  xUSART1;                       // 声明为全局变量,方便记录信息、状态
extern xUSATR_TypeDef  xUSART2;                       // 声明为全局变量,方便记录信息、状态
extern xUSATR_TypeDef  xUSART3;                       // 声明为全局变量,方便记录信息、状态
extern xUSATR_TypeDef  xUART4;                        // 声明为全局变量,方便记录信息、状态
extern xUSATR_TypeDef  xUART5;                        // 声明为全局变量,方便记录信息、状态
extern xUSATR_TypeDef  xUSART6;                       // 声明为全局变量,方便记录信息、状态




/*****************************************************************************
 ** 声明全局函数
****************************************************************************/
// USART1
void    USART1_Init(uint32_t baudrate);                       // 初始化串口的GPIO、通信参数配置、中断优先级; (波特率可设、8位数据、无校验、1个停止位)
void    USART1_SendData(uint8_t *buf, uint16_t cnt);          // 通过中断发送数据，适合各种数据
void    USART1_SendString(char *stringTemp);                  // 通过中断发送字符串，适合字符串，长度在256个长度内的
// USART2
void    USART2_Init(uint32_t baudrate);                       // 初始化串口的GPIO、通信参数配置、中断优先级; (波特率可设、8位数据、无校验、1个停止位)
void    USART2_SendData(uint8_t *buf, uint16_t cnt);          // 通过中断发送数据，适合各种数据
void    USART2_SendString(char *stringTemp);                  // 通过中断发送字符串，适合字符串，长度在256个长度内的
// USART3
void    USART3_Init(uint32_t baudrate);                       // 初始化串口的GPIO、通信参数配置、中断优先级; (波特率可设、8位数据、无校验、1个停止位)
void    USART3_SendData(uint8_t *buf, uint16_t cnt);          // 通过中断发送数据，适合各种数据
void    USART3_SendString(char *stringTemp);                  // 通过中断发送字符串，适合字符串，长度在256个长度内的
// USART4
void    UART4_Init(uint32_t baudrate);                        // 初始化串口的GPIO、通信参数配置、中断优先级; (波特率可设、8位数据、无校验、1个停止位)
void    UART4_SendData(uint8_t *buf, uint16_t cnt);           // 通过中断发送数据，适合各种数据
void    UART4_SendString(char *stringTemp);                   // 通过中断发送字符串，适合字符串，长度在256个长度内的
// USART5
void    UART5_Init(uint32_t baudrate);                        // 初始化串口的GPIO、通信参数配置、中断优先级; (波特率可设、8位数据、无校验、1个停止位)
void    UART5_SendData(uint8_t *buf, uint16_t cnt);           // 通过中断发送数据，适合各种数据
void    UART5_SendString(char *stringTemp);                   // 通过中断发送字符串，适合字符串，长度在256个长度内的
// USART6
void    USART6_Init(uint32_t baudrate);                       // 初始化串口的GPIO、通信参数配置、中断优先级; (波特率可设、8位数据、无校验、1个停止位)
void    USART6_SendData(uint8_t *buf, uint16_t cnt);          // 通过中断发送数据，适合各种数据
void    USART6_SendString(char *stringTemp);                  // 通过中断发送字符串，适合字符串，长度在256个长度内的

#endif

