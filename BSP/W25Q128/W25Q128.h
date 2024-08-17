#ifndef __W25Q_H
#define __W25Q_H

#include <stm32f4xx.h>
#include <stdio.h>



/*****************************************************************************
 ** 引脚定义
 ** 移植时，如果使用SPI1,只需要修改这个区域
****************************************************************************/
#define  W25Q128_SPI                    SPI1
                                      
#define  W25Q128_SCK_GPIO               GPIOA  
#define  W25Q128_SCK_PIN                GPIO_Pin_5        
#define  W25Q128_SCK_PINSOURCE          GPIO_PinSource5
#define  W25Q128_SCK_AF                 GPIO_AF_SPI1
                                      
#define  W25Q128_MISO_GPIO              GPIOA 
#define  W25Q128_MISO_PIN               GPIO_Pin_6                
#define  W25Q128_MISO_PINSOURCE         GPIO_PinSource6
#define  W25Q128_MISO_AF                GPIO_AF_SPI1
                                      
#define  W25Q128_MOSI_GPIO              GPIOA 
#define  W25Q128_MOSI_PIN               GPIO_Pin_7                
#define  W25Q128_MOSI_PINSOURCE         GPIO_PinSource7
#define  W25Q128_MOSI_AF                GPIO_AF_SPI1

#define  W25Q128_CS_GPIO                GPIOC 
#define  W25Q128_CS_PIN                 GPIO_Pin_13      

#define  GBK_STORAGE_ADDR               0x00A00000    // GBK字库起始地址,魔女开发板的W25Q128已保存宋体12、16、24、32号字体



/*****************************************************************************
 ** 声明全局变量
****************************************************************************/
typedef struct
{
    uint8_t   FlagInit;                 // 初始化状态   0:失败, 1:成功
    uint8_t   FlagGBKStorage;           // GBK字库标志; 0=没有, 1=可用; 作用: 用于判断地址段的写保护, 防止字库被错误写履盖; 并可作LCD的中文输出判断
    char      type[20];                 // 型号
    uint16_t  StartupTimes;             // 记录启动次数
} xW25Q_TypeDef;
extern xW25Q_TypeDef  xW25Q128;         // 声明全局结构体, 用于记录w25qxx信息





/*****************************************************************************
 ** 声明全局函数
 ** 为统一代码以方便移植，已封装成4个对外函数，可完成对其所有存取操作
****************************************************************************/
void W25Q128_Init(void);                                                  // 初始化
void W25Q128_ReadBuffer(uint32_t addr, uint8_t *buf, uint16_t num);       // 读数据：addr-地址，*p-读取后数据缓存，num-要读取的字节数
void W25Q128_WriteBuffer(uint32_t addr, uint8_t *buf, uint16_t num);      // 写数据：addr-地址，*p-待写的数据缓存，num-要写入的字节数
void W25Q128_ReadGBK(uint8_t *typeface, uint8_t size, uint8_t *dataBuf);  // 从w25qxx的字库中读取出字模数据



#endif




