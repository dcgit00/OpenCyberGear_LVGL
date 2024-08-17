#include "USART.h"



xUSATR_TypeDef  xUSART1;                       // 声明为全局变量,方便记录信息、状态
xUSATR_TypeDef  xUSART2;                       // 声明为全局变量,方便记录信息、状态
xUSATR_TypeDef  xUSART3;                       // 声明为全局变量,方便记录信息、状态
xUSATR_TypeDef  xUART4;                        // 声明为全局变量,方便记录信息、状态
xUSATR_TypeDef  xUART5;                        // 声明为全局变量,方便记录信息、状态
xUSATR_TypeDef  xUSART6;                       // 声明为全局变量,方便记录信息、状态



//////////////////////////////////////////////////////////////   USART-1   //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * 函  数： vUSART1_Init
 * 功  能： 初始化USART1的GPIO、通信参数配置、中断优先级
 *          (8位数据、无校验、1个停止位)
 * 参  数： uint32_t baudrate  通信波特率
 * 返回值： 无
 ******************************************************************************/
void USART1_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 时钟使能
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN ;

    // 配置TX_PA9
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;                     // 引脚编号：TX_PA9
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                   // 引脚方向: 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  // 输出模式：推挽
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                   // 上下拉：上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               // 输出速度：50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器
    // 配置RX_PA10
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;                    // 引脚编号：RX_PA10
    GPIO_Init(GPIOA, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器

    // 配置引脚的具体复用功能
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);       // 配置PA9复用功能： USART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);      // 配置PA10复用功能：USART1

    // 中断配置
    NVIC_InitStructure .NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure .NVIC_IRQChannelPreemptionPriority = 2 ;     // 抢占优先级
    NVIC_InitStructure .NVIC_IRQChannelSubPriority = 2;             // 子优先级
    NVIC_InitStructure .NVIC_IRQChannelCmd = ENABLE;                // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);

    //USART 初始化设置
    USART_DeInit(USART1);
    USART_InitStructure.USART_BaudRate   = baudrate;                // 串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;        // 一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;         // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 使能收、发模式
    USART_Init(USART1, &USART_InitStructure);                       // 初始化串口

    USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  // 使能接受中断
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);                  // 使能空闲中断

    USART_Cmd(USART1, ENABLE);                                      // 使能串口, 开始工作

    USART1->SR = ~(0x00F0);                                         // 清理中断

    xUSART1.InitFlag = 1;                                           // 标记初始化标志
    xUSART1.ReceivedNum = 0;                                        // 接收字节数清零
	
}

/******************************************************************************
 * 函  数： USART1_IRQHandler
 * 功  能： USART1的接收中断、空闲中断、发送中断
 * 参  数： 无
 * 返回值： 无
 *
******************************************************************************/
static uint8_t usart1TxBuffer[256] ;    // 用于中断发送：环形缓冲区，256个字节
static uint8_t usart1TxCounter = 0 ;    // 用于中断发送：标记已发送的字节数(环形)
static uint8_t usart1TxCount   = 0 ;    // 用于中断发送：标记将要发送的字节数(环形)

void USART1_IRQHandler(void)
{
    static uint16_t cnt = 0;                                         // 接收字节数累计：每一帧数据已接收到的字节数
    static uint8_t  RxTemp[USART1_RX_BUF_SIZE];                      // 接收数据缓存数组：每新接收１个字节，先顺序存放到这里，当一帧接收完(发生空闲中断), 再转存到全局变量：xUSART.USARTxReceivedData[xx]中；
    // 接收中断
    if (USART1->SR & (1 << 5))                                       // 检查RXNE(读数据寄存器非空标志位); RXNE中断清理方法：读DR时自动清理；
    {
        if ((cnt >= USART1_RX_BUF_SIZE))//||(xUSART1.ReceivedFlag==1 // 判断1: 当前帧已接收到的数据量，已满(缓存区), 为避免溢出，本包后面接收到的数据直接舍弃．
        {
            // 判断2: 如果之前接收好的数据包还没处理，就放弃新数据，即，新数据帧不能覆盖旧数据帧，直至旧数据帧被处理．缺点：数据传输过快于处理速度时会掉包；好处：机制清晰，易于调试
            USART1->DR;                                              // 读取数据寄存器的数据，但不保存．主要作用：读DR时自动清理接收中断标志；
            return;
        }
        RxTemp[cnt++] = USART1->DR ;                                 // 把新收到的字节数据，顺序存放到RXTemp数组中；注意：读取DR时自动清零中断位；
	}
	
    // 空闲中断, 用于配合接收中断，以判断一帧数据的接收完成
    if (USART1->SR & (1 << 4))                                       // 检查IDLE(空闲中断标志位); IDLE中断标志清理方法：序列清零，USART1 ->SR;  USART1 ->DR;
    {
        xUSART1.ReceivedNum  = 0;                                    // 把接收到的数据字节数清0
        memcpy(xUSART1.ReceivedData, RxTemp, USART1_RX_BUF_SIZE);    // 把本帧接收到的数据，存放到全局变量xUSART.USARTxReceivedData中, 等待处理; 注意：复制的是整个数组，包括0值，以方便字符串数据
        xUSART1.ReceivedNum  = cnt;                                  // 把接收到的字节数，存放到全局变量xUSART.USARTxReceivedCNT中；
        cnt = 0;                                                     // 接收字节数累计器，清零; 准备下一次的接收
        memset(RxTemp, 0, USART1_RX_BUF_SIZE);                       // 接收数据缓存数组，清零; 准备下一次的接收
        USART1 ->SR;
        USART1 ->DR;                                                 // 清零IDLE中断标志位!! 序列清零，顺序不能错!!
    }

    // 发送中断
    if ((USART1->SR & 1 << 7) && (USART1->CR1 & 1 << 7))             // 检查TXE(发送数据寄存器空)、TXEIE(发送缓冲区空中断使能)
    {
        USART1->DR = usart1TxBuffer[usart1TxCounter++];              // 读取数据寄存器值；注意：读取DR时自动清零中断位；
        if (usart1TxCounter == usart1TxCount)
            USART1->CR1 &= ~(1 << 7);                                // 已发送完成，关闭发送缓冲区空置中断 TXEIE
    }
}

/******************************************************************************
 * 函  数： vUSART1_SendData
 * 功  能： UART通过中断发送数据,适合各种数据类型
 *         【适合场景】本函数可发送各种数据，而不限于字符串，如int,char
 *         【不 适 合】注意环形缓冲区容量256字节，如果发送频率太高，注意波特率
 * 参  数： uint8_t* buffer   需发送数据的首地址
 *          uint8_t  cnt      发送的字节数 ，限于中断发送的缓存区大小，不能大于256个字节
 * 返回值：
 ******************************************************************************/
void USART1_SendData(uint8_t *buf, uint16_t cnt)
{
    if (cnt > 256) cnt = 256;                     // 本函数只适用于最大发送256个字节; 如果超过最大发送量，请自行分包发送，或者重写本函数

    for (uint16_t i = 0; i < cnt; i++)
        usart1TxBuffer[usart1TxCount++] = buf[i];

    if ((USART1->CR1 & 1 << 7) == 0)              // 检查发送缓冲区空置中断(TXEIE)是否已打开
        USART1->CR1 |= 1 << 7;
}

/******************************************************************************
 * 函  数： vUSART1_SendString
 * 功  能： UART通过中断发送输出字符串,无需输入数据长度
 *         【适合场景】字符串，长度<=256字节
 *         【不 适 合】int,float等数据类型
 * 参  数： char* stringTemp   需发送数据的缓存首地址
 * 返回值： 元
 ******************************************************************************/
void USART1_SendString(char *stringTemp)
{
    uint16_t num = 0;                                 // 字符串长度
    char *t = stringTemp ;                       // 用于配合计算发送的数量
    while (*t++ != 0)  num++;                    // 计算要发送的数目，这步比较耗时，测试发现每多6个字节，增加1us，单位：8位

    USART1_SendData((u8 *)stringTemp, num);      // 注意调用函数所需要的真实数据长度;
}





//////////////////////////////////////////////////////////////   USART-2   //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * 函  数： vUSART2_Init
 * 功  能： 初始化USART的GPIO、通信参数配置、中断优先级
 *          (8位数据、无校验、1个停止位)
 * 参  数： uint32_t baudrate  通信波特率
 * 返回值： 无
 ******************************************************************************/
void USART2_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 时钟使能
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN ;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // 配置TX_PA2
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;                     // 引脚编号：TX_PA2
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                   // 引脚方向: 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  // 输出模式：推挽
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                   // 上下拉：上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               // 输出速度：50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器
    // 配置RX_PA3
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;                     // 引脚编号：RX_PA3
    GPIO_Init(GPIOA, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器

    // 配置引脚的具体复用功能
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);       // 配置引脚复用功能：USART2
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);       // 配置引脚复用功能：USART2

    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // 中断配置
    NVIC_InitStructure .NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure .NVIC_IRQChannelPreemptionPriority = 2 ;     // 抢占优先级
    NVIC_InitStructure .NVIC_IRQChannelSubPriority = 2;             // 子优先级
    NVIC_InitStructure .NVIC_IRQChannelCmd = ENABLE;                // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);

    //USART 初始化设置
    //USART_DeInit(USART2);
    USART_InitStructure.USART_BaudRate   = baudrate;                // 串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;        // 一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;         // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 使能收、发模式
    USART_Init(USART2, &USART_InitStructure);                       // 初始化串口

    USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                  // 使能接受中断
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);                  // 使能空闲中断

    USART_Cmd(USART2, ENABLE);                                      // 使能串口, 开始工作

    USART2->SR = ~(0x00F0);                                         // 清理中断

    xUSART2.InitFlag = 1;                                           // 标记初始化标志
    xUSART2.ReceivedNum = 0;                                        // 接收字节数清零

    printf("USART2初始化配置         接收中断、空闲中断, 发送中断\r\n");
}

/******************************************************************************
 * 函  数： USART2_IRQHandler
 * 功  能： USART2的接收中断、空闲中断、发送中断
 * 参  数： 无
 * 返回值： 无
 ******************************************************************************/
static uint8_t usart2TxBuffer[256] ;    // 用于中断发送：环形缓冲区，256个字节
static uint8_t usart2TxCounter = 0 ;    // 用于中断发送：标记已发送的字节数(环形)
static uint8_t usart2TxCount   = 0 ;    // 用于中断发送：标记将要发送的字节数(环形)

void USART2_IRQHandler(void)
{
    static uint16_t cnt = 0;                                         // 接收字节数累计：每一帧数据已接收到的字节数
    static uint8_t  RxTemp[USART2_RX_BUF_SIZE];                      // 接收数据缓存数组：每新接收１个字节，先顺序存放到这里，当一帧接收完(发生空闲中断), 再转存到全局变量：xUSART.USARTxReceivedData[xx]中；

    // 接收中断
    if (USART2->SR & (1 << 5))                                       // 检查RXNE(读数据寄存器非空标志位); RXNE中断清理方法：读DR时自动清理；
    {
        if ((cnt >= USART2_RX_BUF_SIZE))//||xUSART2.ReceivedFlag==1  // 判断1: 当前帧已接收到的数据量，已满(缓存区), 为避免溢出，本包后面接收到的数据直接舍弃．
        {
            // 判断2: 如果之前接收好的数据包还没处理，就放弃新数据，即，新数据帧不能覆盖旧数据帧，直至旧数据帧被处理．缺点：数据传输过快于处理速度时会掉包；好处：机制清晰，易于调试
            USART2->DR;                                              // 读取数据寄存器的数据，但不保存．主要作用：读DR时自动清理接收中断标志；
            return;
        }
        RxTemp[cnt++] = USART2->DR ;                                 // 把新收到的字节数据，顺序存放到RXTemp数组中；注意：读取DR时自动清零中断位；
    }

    // 空闲中断, 用于配合接收中断，以判断一帧数据的接收完成
    if (USART2->SR & (1 << 4))                                       // 检查IDLE(空闲中断标志位); IDLE中断标志清理方法：序列清零，USART1 ->SR;  USART1 ->DR;
    {
        xUSART2.ReceivedNum  = 0;                                    // 把接收到的数据字节数清0
        memcpy(xUSART2.ReceivedData, RxTemp, USART2_RX_BUF_SIZE);    // 把本帧接收到的数据，存放到全局变量xUSART.USARTxReceivedData中, 等待处理; 注意：复制的是整个数组，包括0值，以方便字符串数据
        xUSART2.ReceivedNum  = cnt;                                  // 把接收到的字节数，存放到全局变量xUSART.USARTxReceivedCNT中；
        cnt = 0;                                                     // 接收字节数累计器，清零; 准备下一次的接收
        memset(RxTemp, 0, USART2_RX_BUF_SIZE);                       // 接收数据缓存数组，清零; 准备下一次的接收
        USART2 ->SR;
        USART2 ->DR;                                                 // 清零IDLE中断标志位!! 序列清零，顺序不能错!!
    }

    // 发送中断
    if ((USART2->SR & 1 << 7) && (USART2->CR1 & 1 << 7))             // 检查TXE(发送数据寄存器空)、TXEIE(发送缓冲区空中断使能)
    {
        USART2->DR = usart2TxBuffer[usart2TxCounter++];              // 读取数据寄存器值；注意：读取DR时自动清零中断位；
        if (usart2TxCounter == usart2TxCount)
            USART2->CR1 &= ~(1 << 7);                                // 已发送完成，关闭发送缓冲区空置中断 TXEIE
    }
}


/******************************************************************************
 * 函  数： vUSART2_SendData
 * 功  能： UART通过中断发送数据,适合各种数据类型
 *         【适合场景】本函数可发送各种数据，而不限于字符串，如int,char
 *         【不 适 合】注意环形缓冲区容量256字节，如果发送频率太高，注意波特率
 * 参  数： uint8_t* buffer   需发送数据的首地址
 *          uint8_t  cnt      发送的字节数 ，限于中断发送的缓存区大小，不能大于256个字节
 * 返回值：
 ******************************************************************************/
void USART2_SendData(uint8_t *buf, uint16_t cnt)
{
    if (cnt > 256) cnt = 256;              // 本函数只适用于最大发送256个字节; 如果超过最大发送量，请自行分包发送，或者重写本函数

    for (uint16_t i = 0; i < cnt; i++)
        usart2TxBuffer[usart2TxCount++] = buf[i];

    if ((USART2->CR1 & 1 << 7) == 0)       // 检查发送缓冲区空置中断(TXEIE)是否已打开
        USART2->CR1 |= 1 << 7;
}

/******************************************************************************
 * 函  数： vUSART2_SendString
 * 功  能： UART通过中断发送输出字符串,无需输入数据长度
 *         【适合场景】字符串，长度<=256字节
 *         【不 适 合】int,float等数据类型
 * 参  数： char* stringTemp   需发送数据的缓存首地址
 * 返回值： 元
 ******************************************************************************/
void USART2_SendString(char *stringTemp)
{
    uint16_t num = 0;                                 // 字符串长度
    char *t = stringTemp ;                       // 用于配合计算发送的数量
    while (*t++ != 0)  num++;                    // 计算要发送的数目，这步比较耗时，测试发现每多6个字节，增加1us，单位：8位
    USART2_SendData((u8 *)stringTemp, num);      // 注意调用函数所需要的真实数据长度; 如果目标需要以0作结尾判断，需num+1：字符串以0结尾，即多发一个:0
}





//////////////////////////////////////////////////////////////   USART-3   //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * 函  数： vUSART3_Init
 * 功  能： 初始化USART的GPIO、通信参数配置、中断优先级
 *          (8位数据、无校验、1个停止位)
 * 参  数： uint32_t baudrate  通信波特率
 * 返回值： 无
 ******************************************************************************/
void USART3_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 时钟使能
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN ;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // 配置TX_PA2
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;                    // 引脚编号：TX_PB10
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                   // 引脚方向: 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  // 输出模式：推挽
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                   // 上下拉：上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               // 输出速度：50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器
    // 配置RX_PA3
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;                    // 引脚编号：RX_PB11
    GPIO_Init(GPIOB, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器

    // 配置引脚的具体复用功能
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);      // 配置引脚复用功能
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);      // 配置引脚复用功能

    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // 中断配置
    NVIC_InitStructure .NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure .NVIC_IRQChannelPreemptionPriority = 2 ;     // 抢占优先级
    NVIC_InitStructure .NVIC_IRQChannelSubPriority = 2;             // 子优先级
    NVIC_InitStructure .NVIC_IRQChannelCmd = ENABLE;                // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);

    //USART 初始化设置
    USART_DeInit(USART3);
    USART_InitStructure.USART_BaudRate   = baudrate;                // 串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;        // 一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;         // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 使能收、发模式
    USART_Init(USART3, &USART_InitStructure);                       // 初始化串口

    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                  // 使能接受中断
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);                  // 使能空闲中断

    USART_Cmd(USART3, ENABLE);

    USART3->SR = ~(0x00F0);                                         // 清理中断

    xUSART3.InitFlag = 1;                                           // 标记初始化标志
    xUSART3.ReceivedNum = 0;                                        // 接收字节数清零

    printf("USART3初始化配置         接收中断、空闲中断, 发送中断\r\n");
}

/******************************************************************************
 * 函  数： USART3_IRQHandler
 * 功  能： USART的接收中断、空闲中断、发送中断
 * 参  数： 无
 * 返回值： 无
 ******************************************************************************/
static uint8_t usart3TxBuffer[256] ;    // 用于中断发送：环形缓冲区，256个字节
static uint8_t usart3TxCounter = 0 ;    // 用于中断发送：标记已发送的字节数(环形)
static uint8_t usart3TxCount   = 0 ;    // 用于中断发送：标记将要发送的字节数(环形)

void USART3_IRQHandler(void)
{
    static uint16_t cnt = 0;                                         // 接收字节数累计：每一帧数据已接收到的字节数
    static uint8_t  RxTemp[USART3_RX_BUF_SIZE];                      // 接收数据缓存数组：每新接收１个字节，先顺序存放到这里，当一帧接收完(发生空闲中断), 再转存到全局变量：xUSART.USARTxReceivedData[xx]中；

    // 接收中断
    if (USART3->SR & (1 << 5))                                       // 检查RXNE(读数据寄存器非空标志位); RXNE中断清理方法：读DR时自动清理；
    {
        if ((cnt >= USART3_RX_BUF_SIZE))//||xUSART3.ReceivedFlag==1  // 判断1: 当前帧已接收到的数据量，已满(缓存区), 为避免溢出，本包后面接收到的数据直接舍弃．
        {
            // 判断2: 如果之前接收好的数据包还没处理，就放弃新数据，即，新数据帧不能覆盖旧数据帧，直至旧数据帧被处理．缺点：数据传输过快于处理速度时会掉包；好处：机制清晰，易于调试
            USART3->DR;                                              // 读取数据寄存器的数据，但不保存．主要作用：读DR时自动清理接收中断标志；
            return;
        }
        RxTemp[cnt++] = USART3->DR ;                                 // 把新收到的字节数据，顺序存放到RXTemp数组中；注意：读取DR时自动清零中断位；
    }

    // 空闲中断, 用于配合接收中断，以判断一帧数据的接收完成
    if (USART3->SR & (1 << 4))                                       // 检查IDLE(空闲中断标志位); IDLE中断标志清理方法：序列清零，USART1 ->SR;  USART1 ->DR;
    {
        xUSART3.ReceivedNum  = 0;                                    // 把接收到的数据字节数清0
        memcpy(xUSART3.ReceivedData, RxTemp, USART3_RX_BUF_SIZE);    // 把本帧接收到的数据，存放到全局变量xUSART.USARTxReceivedData中, 等待处理; 注意：复制的是整个数组，包括0值，以方便字符串数据
        xUSART3.ReceivedNum  = cnt;                                  // 把接收到的字节数，存放到全局变量xUSART.USARTxReceivedCNT中；
        cnt = 0;                                                     // 接收字节数累计器，清零; 准备下一次的接收
        memset(RxTemp, 0, USART3_RX_BUF_SIZE);                       // 接收数据缓存数组，清零; 准备下一次的接收
        USART3 ->SR;
        USART3 ->DR;                                                 // 清零IDLE中断标志位!! 序列清零，顺序不能错!!
    }

    // 发送中断
    if ((USART3->SR & 1 << 7) && (USART3->CR1 & 1 << 7))             // 检查TXE(发送数据寄存器空)、TXEIE(发送缓冲区空中断使能)
    {
        USART3->DR = usart3TxBuffer[usart3TxCounter++];              // 读取数据寄存器值；注意：读取DR时自动清零中断位；
        if (usart3TxCounter == usart3TxCount)
            USART3->CR1 &= ~(1 << 7);                                // 已发送完成，关闭发送缓冲区空置中断 TXEIE
    }
}

/******************************************************************************
 * 函  数： vUSART3_SendData
 * 功  能： UART通过中断发送数据,适合各种数据类型
 *         【适合场景】本函数可发送各种数据，而不限于字符串，如int,char
 *         【不 适 合】注意环形缓冲区容量256字节，如果发送频率太高，注意波特率
 * 参  数： uint8_t* buffer   需发送数据的首地址
 *          uint8_t  cnt      发送的字节数 ，限于中断发送的缓存区大小，不能大于256个字节
 * 返回值：
 ******************************************************************************/
void USART3_SendData(uint8_t *buf, uint16_t cnt)
{
    if (cnt > 256) cnt = 256;                     // 本函数只适用于最大发送256个字节; 如果超过最大发送量，请自行分包发送，或者重写本函数

    for (uint16_t i = 0; i < cnt; i++)
        usart3TxBuffer[usart3TxCount++] = buf[i];

    if ((USART3->CR1 & 1 << 7) == 0)              // 检查发送缓冲区空置中断(TXEIE)是否已打开
        USART3->CR1 |= 1 << 7;
}

/******************************************************************************
 * 函  数： vUSART3_SendString
 * 功  能： UART通过中断发送输出字符串,无需输入数据长度
 *         【适合场景】字符串，长度<=256字节
 *         【不 适 合】int,float等数据类型
 * 参  数： char* stringTemp   需发送数据的缓存首地址
 * 返回值： 元
 ******************************************************************************/
void USART3_SendString(char *stringTemp)
{
    uint16_t num = 0;                                 // 字符串长度
    char *t = stringTemp ;                       // 用于配合计算发送的数量
    while (*t++ != 0)  num++;                    // 计算要发送的数目，这步比较耗时，测试发现每多6个字节，增加1us，单位：8位
    USART3_SendData((u8 *)stringTemp, num);      // 注意调用函数所需要的真实数据长度; 如果目标需要以0作结尾判断，需num+1：字符串以0结尾，即多发一个:0
}






//////////////////////////////////////////////////////////////   UART-4   //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * 函  数： vUART4_Init
 * 功  能： 初始化USART的GPIO、通信参数配置、中断优先级
 *          (8位数据、无校验、1个停止位)
 * 参  数： uint32_t baudrate  通信波特率
 * 返回值： 无
 ******************************************************************************/
void UART4_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 时钟使能
    RCC->APB1ENR |= RCC_APB1ENR_UART4EN ;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // 配置TX_PA2
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;                    // 引脚编号：TX_PC10
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                   // 引脚方向: 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  // 输出模式：推挽
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                   // 上下拉：上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               // 输出速度：50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器
    // 配置RX_PA3
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;                    // 引脚编号：RX_PC11
    GPIO_Init(GPIOC, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器

    // 配置引脚的具体复用功能
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);       // 配置引脚复用功能：UART4
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);       // 配置引脚复用功能：UART4

    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // 中断配置
    NVIC_InitStructure .NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure .NVIC_IRQChannelPreemptionPriority = 2 ;     // 抢占优先级
    NVIC_InitStructure .NVIC_IRQChannelSubPriority = 2;             // 子优先级
    NVIC_InitStructure .NVIC_IRQChannelCmd = ENABLE;                // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);

    //USART 初始化设置
    USART_DeInit(UART4);
    USART_InitStructure.USART_BaudRate   = baudrate;                // 串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;        // 一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;         // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 使能收、发模式
    USART_Init(UART4, &USART_InitStructure);                        // 初始化串口

    USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);                   // 使能接受中断
    USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);                   // 使能空闲中断

    USART_Cmd(UART4, ENABLE);                                       // 使能串口, 开始工作

    UART4->SR = ~(0x00F0);                                          // 清理中断

    xUART4.InitFlag = 1;                                            // 标记初始化标志
    xUART4.ReceivedNum = 0;                                         // 接收字节数清零

    printf("UART4 初始化配置         接收中断、空闲中断, 发送中断\r\n");
}

/******************************************************************************
 * 函  数： UART4_IRQHandler
 * 功  能： USART2的接收中断、空闲中断、发送中断
 * 参  数： 无
 * 返回值： 无
 ******************************************************************************/
static uint8_t uart4TxBuffer[256] ;    // 用于中断发送：环形缓冲区，256个字节
static uint8_t uart4TxCounter = 0 ;    // 用于中断发送：标记已发送的字节数(环形)
static uint8_t uart4TxCount   = 0 ;    // 用于中断发送：标记将要发送的字节数(环形)

void UART4_IRQHandler(void)
{
    static uint16_t cnt = 0;                                        // 接收字节数累计：每一帧数据已接收到的字节数
    static uint8_t  RxTemp[UART4_RX_BUF_SIZE];                      // 接收数据缓存数组：每新接收１个字节，先顺序存放到这里，当一帧接收完(发生空闲中断), 再转存到全局变量：xUSART.USARTxReceivedData[xx]中；

    // 接收中断
    if (UART4->SR & (1 << 5))                                       // 检查RXNE(读数据寄存器非空标志位); RXNE中断清理方法：读DR时自动清理；
    {
        if ((cnt >= UART4_RX_BUF_SIZE))//||xUART4.ReceivedFlag==1   // 判断1: 当前帧已接收到的数据量，已满(缓存区), 为避免溢出，本包后面接收到的数据直接舍弃．
        {
            // 判断2: 如果之前接收好的数据包还没处理，就放弃新数据，即，新数据帧不能覆盖旧数据帧，直至旧数据帧被处理．缺点：数据传输过快于处理速度时会掉包；好处：机制清晰，易于调试
            UART4->DR;                                              // 读取数据寄存器的数据，但不保存．主要作用：读DR时自动清理接收中断标志；
            return;
        }
        RxTemp[cnt++] = UART4->DR ;                                 // 把新收到的字节数据，顺序存放到RXTemp数组中；注意：读取DR时自动清零中断位；
    }

    // 空闲中断, 用于配合接收中断，以判断一帧数据的接收完成
    if (UART4->SR & (1 << 4))                                       // 检查IDLE(空闲中断标志位); IDLE中断标志清理方法：序列清零，USART1 ->SR;  USART1 ->DR;
    {
        xUART4.ReceivedNum  = 0;                                    // 把接收到的数据字节数清0
        memcpy(xUART4.ReceivedData, RxTemp, UART4_RX_BUF_SIZE);     // 把本帧接收到的数据，存放到全局变量xUSART.USARTxReceivedData中, 等待处理; 注意：复制的是整个数组，包括0值，以方便字符串数据
        xUART4.ReceivedNum  = cnt;                                  // 把接收到的字节数，存放到全局变量xUSART.USARTxReceivedCNT中；
        cnt = 0;                                                    // 接收字节数累计器，清零; 准备下一次的接收
        memset(RxTemp, 0, UART4_RX_BUF_SIZE);                       // 接收数据缓存数组，清零; 准备下一次的接收
        UART4 ->SR;
        UART4 ->DR;                                                 // 清零IDLE中断标志位!! 序列清零，顺序不能错!!
    }

    // 发送中断
    if ((UART4->SR & 1 << 7) && (UART4->CR1 & 1 << 7))              // 检查TXE(发送数据寄存器空)、TXEIE(发送缓冲区空中断使能)
    {
        UART4->DR = uart4TxBuffer[uart4TxCounter++];                // 读取数据寄存器值；注意：读取DR时自动清零中断位；
        if (uart4TxCounter == uart4TxCount)
            UART4->CR1 &= ~(1 << 7);                                // 已发送完成，关闭发送缓冲区空置中断 TXEIE
    }
}

/******************************************************************************
 * 函  数： vUART4_SendData
 * 功  能： UART通过中断发送数据,适合各种数据类型
 *         【适合场景】本函数可发送各种数据，而不限于字符串，如int,char
 *         【不 适 合】注意环形缓冲区容量256字节，如果发送频率太高，注意波特率
 * 参  数： uint8_t* buffer   需发送数据的首地址
 *          uint8_t  cnt      发送的字节数 ，限于中断发送的缓存区大小，不能大于256个字节
 * 返回值：
 ******************************************************************************/
void UART4_SendData(uint8_t *buf, uint16_t cnt)
{
    if (cnt > 256) cnt = 256;                     // 本函数只适用于最大发送256个字节; 如果超过最大发送量，请自行分包发送，或者重写本函数

    for (uint16_t i = 0; i < cnt; i++)
        uart4TxBuffer[uart4TxCount++] = buf[i];

    if ((UART4->CR1 & 1 << 7) == 0)               // 检查发送缓冲区空置中断(TXEIE)是否已打开
        UART4->CR1 |= 1 << 7;
}

/******************************************************************************
 * 函  数： vUART4_SendString
 * 功  能： UART通过中断发送输出字符串,无需输入数据长度
 *         【适合场景】字符串，长度<=256字节
 *         【不 适 合】int,float等数据类型
 * 参  数： char* stringTemp   需发送数据的缓存首地址
 * 返回值： 元
 ******************************************************************************/
void UART4_SendString(char *stringTemp)
{
    uint16_t num = 0;                                 // 字符串长度
    char *t = stringTemp ;                       // 用于配合计算发送的数量
    while (*t++ != 0)  num++;                    // 计算要发送的数目，这步比较耗时，测试发现每多6个字节，增加1us，单位：8位
    UART4_SendData((u8 *)stringTemp, num);       // 调用函数完成发送，num+1：字符串以0结尾，需多发一个:0
}




//////////////////////////////////////////////////////////////   UART-5   //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * 函  数： vUART5_Init
 * 功  能： 初始化USART的GPIO、通信参数配置、中断优先级
 *          (8位数据、无校验、1个停止位)
 * 参  数： uint32_t baudrate  通信波特率
 * 返回值： 无
 ******************************************************************************/
void UART5_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 时钟使能
    RCC->APB1ENR |= RCC_APB1ENR_UART5EN ;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // 配置TX_PA2
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;                    // 引脚编号：TX_PC12
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                   // 引脚方向: 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  // 输出模式：推挽
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                   // 上下拉：上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               // 输出速度：50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器
    // 配置RX_PA3
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;                     // 引脚编号：RX_PD2
    GPIO_Init(GPIOD, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器

    // 配置引脚的具体复用功能
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);       // 配置引脚复用功能：UART5
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);        // 配置引脚复用功能：UART5

    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    // 中断配置
    NVIC_InitStructure .NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure .NVIC_IRQChannelPreemptionPriority = 2 ;     // 抢占优先级
    NVIC_InitStructure .NVIC_IRQChannelSubPriority = 2;             // 子优先级
    NVIC_InitStructure .NVIC_IRQChannelCmd = ENABLE;                // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);

    //USART 初始化设置
    USART_DeInit(UART5);
    USART_InitStructure.USART_BaudRate   = baudrate;                // 串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;        // 一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;         // 无奇偶校验位
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 使能收、发模式
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(UART5, &USART_InitStructure);                        // 初始化串口

    USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);                   // 使能接受中断
    USART_ITConfig(UART5, USART_IT_IDLE, ENABLE);                   // 使能空闲中断

    USART_Cmd(UART5, ENABLE);                                       // 使能串口, 开始工作

    UART5->SR = ~(0x00F0);                                          // 清理中断

    xUART5.InitFlag = 1;                                            // 标记初始化标志
    xUART5.ReceivedNum = 0;                                         // 接收字节数清零

    printf("UART5 初始化配置         接收中断、空闲中断, 发送中断\r\n");
}

/******************************************************************************
 * 函  数： UART5_IRQHandler
 * 功  能： USART2的接收中断、空闲中断、发送中断
 * 参  数： 无
 * 返回值： 无
 ******************************************************************************/
static uint8_t uart5TxBuffer[256] ;    // 用于中断发送：环形缓冲区，256个字节
static uint8_t uart5TxCounter = 0 ;    // 用于中断发送：标记已发送的字节数(环形)
static uint8_t uart5TxCount   = 0 ;    // 用于中断发送：标记将要发送的字节数(环形)

void UART5_IRQHandler(void)
{
    static uint16_t cnt = 0;                                        // 接收字节数累计：每一帧数据已接收到的字节数
    static uint8_t  RxTemp[UART5_RX_BUF_SIZE];                      // 接收数据缓存数组：每新接收１个字节，先顺序存放到这里，当一帧接收完(发生空闲中断), 再转存到全局变量：xUSART.USARTxReceivedData[xx]中；

    // 接收中断
    if (UART5->SR & (1 << 5))                                       // 检查RXNE(读数据寄存器非空标志位); RXNE中断清理方法：读DR时自动清理；
    {
        if ((cnt >= UART5_RX_BUF_SIZE))//||xUART5.ReceivedFlag==1   // 判断1: 当前帧已接收到的数据量，已满(缓存区), 为避免溢出，本包后面接收到的数据直接舍弃．
        {
            // 判断2: 如果之前接收好的数据包还没处理，就放弃新数据，即，新数据帧不能覆盖旧数据帧，直至旧数据帧被处理．缺点：数据传输过快于处理速度时会掉包；好处：机制清晰，易于调试
            UART5->DR;                                              // 读取数据寄存器的数据，但不保存．主要作用：读DR时自动清理接收中断标志；
            return;
        }
        RxTemp[cnt++] = UART5->DR ;                                 // 把新收到的字节数据，顺序存放到RXTemp数组中；注意：读取DR时自动清零中断位；
    }

    // 空闲中断, 用于配合接收中断，以判断一帧数据的接收完成
    if (UART5->SR & (1 << 4))                                       // 检查IDLE(空闲中断标志位); IDLE中断标志清理方法：序列清零，USART1 ->SR;  USART1 ->DR;
    {
        xUART5.ReceivedNum  = 0;                                    // 把接收到的数据字节数清0
        memcpy(xUART5.ReceivedData, RxTemp, UART5_RX_BUF_SIZE);     // 把本帧接收到的数据，存放到全局变量xUSART.USARTxReceivedData中, 等待处理; 注意：复制的是整个数组，包括0值，以方便字符串数据
        xUART5.ReceivedNum  = cnt;                                  // 把接收到的字节数，存放到全局变量xUSART.USARTxReceivedCNT中；
        cnt = 0;                                                    // 接收字节数累计器，清零; 准备下一次的接收
        memset(RxTemp, 0, UART5_RX_BUF_SIZE);                          // 接收数据缓存数组，清零; 准备下一次的接收
        UART5 ->SR;
        UART5 ->DR;                                                 // 清零IDLE中断标志位!! 序列清零，顺序不能错!!
    }

    // 发送中断
    if ((UART5->SR & 1 << 7) && (UART5->CR1 & 1 << 7))              // 检查TXE(发送数据寄存器空)、TXEIE(发送缓冲区空中断使能)
    {
        UART5->DR = uart5TxBuffer[uart5TxCounter++];                // 读取数据寄存器值；注意：读取DR时自动清零中断位；
        if (uart5TxCounter == uart5TxCount)
            UART5->CR1 &= ~(1 << 7);                                // 已发送完成，关闭发送缓冲区空置中断 TXEIE
    }
}

/******************************************************************************
 * 函  数： vUART5_SendData
 * 功  能： UART通过中断发送数据,适合各种数据类型
 *         【适合场景】本函数可发送各种数据，而不限于字符串，如int,char
 *         【不 适 合】注意环形缓冲区容量256字节，如果发送频率太高，注意波特率
 * 参  数： uint8_t* buffer   需发送数据的首地址
 *          uint8_t  cnt      发送的字节数 ，限于中断发送的缓存区大小，不能大于256个字节
 * 返回值：
 ******************************************************************************/
void UART5_SendData(uint8_t *buf, uint16_t cnt)
{
    if (cnt > 256) cnt = 256;                     // 本函数只适用于最大发送256个字节; 如果超过最大发送量，请自行分包发送，或者重写本函数

    for (uint16_t i = 0; i < cnt; i++)
        uart5TxBuffer[uart5TxCount++] = buf[i];

    if ((UART5->CR1 & 1 << 7) == 0)               // 检查发送缓冲区空置中断(TXEIE)是否已打开
        UART5->CR1 |= 1 << 7;
}

/******************************************************************************
 * 函  数： vUART5_SendString
 * 功  能： UART通过中断发送输出字符串,无需输入数据长度
 *         【适合场景】字符串，长度<=256字节
 *         【不 适 合】int,float等数据类型
 * 参  数： char* stringTemp   需发送数据的缓存首地址
 * 返回值： 元
 ******************************************************************************/
void UART5_SendString(char *stringTemp)
{
    uint16_t num = 0;                                 // 字符串长度
    char *t = stringTemp ;                       // 用于配合计算发送的数量
    while (*t++ != 0)  num++;                    // 计算要发送的数目，这步比较耗时，测试发现每多6个字节，增加1us，单位：8位
    UART5_SendData((u8 *)stringTemp, num);       // 注意调用函数所需要的真实数据长度; 如果目标需要以0作结尾判断，需num+1：字符串以0结尾，即多发一个:0
}



//////////////////////////////////////////////////////////////   USART-6   //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * 函  数： vUSART6_Init
 * 功  能： 初始化USART6的GPIO、通信参数配置、中断优先级
 *          (8位数据、无校验、1个停止位)
 * 参  数： uint32_t baudrate  通信波特率
 * 返回值： 无
 ******************************************************************************/
void USART6_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 时钟使能
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART6EN ;

    // 配置TX_PA9
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;                     // 引脚编号：TX_PC6
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;                   // 引脚方向: 复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  // 输出模式：推挽
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;                   // 上下拉：上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               // 输出速度：50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器
    // 配置RX_PA10
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;                     // 引脚编号：RX_PC7
    GPIO_Init(GPIOC, &GPIO_InitStructure);                          // 初始化：把上述参数，更新到芯片寄存器

    // 配置引脚的具体复用功能
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);       // 配置PC6复用功能：USART6
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);       // 配置PC7复用功能：USART6

    // 中断配置
    NVIC_InitStructure .NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure .NVIC_IRQChannelPreemptionPriority = 2 ;     // 抢占优先级
    NVIC_InitStructure .NVIC_IRQChannelSubPriority = 2;             // 子优先级
    NVIC_InitStructure .NVIC_IRQChannelCmd = ENABLE;                // IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);

    //USART 初始化设置
    USART_DeInit(USART6);
    USART_InitStructure.USART_BaudRate   = baudrate;                // 串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     // 字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;        // 一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;         // 无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 使能收、发模式
    USART_Init(USART6, &USART_InitStructure);                       // 初始化串口

    USART_ITConfig(USART6, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);                  // 使能接受中断
    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);                  // 使能空闲中断

    USART_Cmd(USART6, ENABLE);                                      // 使能串口, 开始工作

    USART6->SR = ~(0x00F0);                                         // 清理中断

    xUSART6.InitFlag = 1;                                           // 标记初始化标志
    xUSART6.ReceivedNum = 0;                                        // 接收字节数清零

    printf("USART6初始化配置         接收中断、空闲中断, 发送中断\r\n");
}

/******************************************************************************
 * 函  数： USART6_IRQHandler
 * 功  能： USART1的接收中断、空闲中断、发送中断
 * 参  数： 无
 * 返回值： 无
 *
******************************************************************************/
static uint8_t usart6TxBuffer[256] ;    // 用于中断发送：环形缓冲区，256个字节
static uint8_t usart6TxCounter = 0 ;    // 用于中断发送：标记已发送的字节数(环形)
static uint8_t usart6TxCount   = 0 ;    // 用于中断发送：标记将要发送的字节数(环形)

void USART6_IRQHandler(void)
{
    static uint16_t cnt = 0;                                         // 接收字节数累计：每一帧数据已接收到的字节数
    static uint8_t  RxTemp[USART6_RX_BUF_SIZE];                      // 接收数据缓存数组：每新接收１个字节，先顺序存放到这里，当一帧接收完(发生空闲中断), 再转存到全局变量：xUSART.USARTxReceivedData[xx]中；

    // 接收中断
    if (USART6->SR & (1 << 5))                                       // 检查RXNE(读数据寄存器非空标志位); RXNE中断清理方法：读DR时自动清理；
    {
        if ((cnt >= USART6_RX_BUF_SIZE))//||(xUSART1.ReceivedFlag==1 // 判断1: 当前帧已接收到的数据量，已满(缓存区), 为避免溢出，本包后面接收到的数据直接舍弃．
        {
            // 判断2: 如果之前接收好的数据包还没处理，就放弃新数据，即，新数据帧不能覆盖旧数据帧，直至旧数据帧被处理．缺点：数据传输过快于处理速度时会掉包；好处：机制清晰，易于调试
            USART6->DR;                                              // 读取数据寄存器的数据，但不保存．主要作用：读DR时自动清理接收中断标志；
            return;
        }
        RxTemp[cnt++] = USART6->DR ;                                 // 把新收到的字节数据，顺序存放到RXTemp数组中；注意：读取DR时自动清零中断位；
    }

    // 空闲中断, 用于配合接收中断，以判断一帧数据的接收完成
    if (USART6->SR & (1 << 4))                                       // 检查IDLE(空闲中断标志位); IDLE中断标志清理方法：序列清零，USART1 ->SR;  USART1 ->DR;
    {
        xUSART6.ReceivedNum  = 0;                                    // 把接收到的数据字节数清0
        memcpy(xUSART6.ReceivedData, RxTemp, USART6_RX_BUF_SIZE);    // 把本帧接收到的数据，存放到全局变量xUSART.USARTxReceivedData中, 等待处理; 注意：复制的是整个数组，包括0值，以方便字符串数据
        xUSART6.ReceivedNum  = cnt;                                  // 把接收到的字节数，存放到全局变量xUSART.USARTxReceivedCNT中；
        cnt = 0;                                                     // 接收字节数累计器，清零; 准备下一次的接收
        memset(RxTemp, 0, USART6_RX_BUF_SIZE);                       // 接收数据缓存数组，清零; 准备下一次的接收
        USART6 ->SR;
        USART6 ->DR;                                                 // 清零IDLE中断标志位!! 序列清零，顺序不能错!!
    }

    // 发送中断
    if ((USART6->SR & 1 << 7) && (USART6->CR1 & 1 << 7))             // 检查TXE(发送数据寄存器空)、TXEIE(发送缓冲区空中断使能)
    {
        USART6->DR = usart6TxBuffer[usart6TxCounter++];              // 读取数据寄存器值；注意：读取DR时自动清零中断位；
        if (usart6TxCounter == usart6TxCount)
            USART6->CR1 &= ~(1 << 7);                                // 已发送完成，关闭发送缓冲区空置中断 TXEIE
    }
}


/******************************************************************************
 * 函  数： vUSART6_SendData
 * 功  能： UART通过中断发送数据,适合各种数据类型
 *         【适合场景】本函数可发送各种数据，而不限于字符串，如int,char
 *         【不 适 合】注意环形缓冲区容量256字节，如果发送频率太高，注意波特率
 * 参  数： uint8_t* buffer   需发送数据的首地址
 *          uint8_t  cnt      发送的字节数 ，限于中断发送的缓存区大小，不能大于256个字节
 * 返回值：
 ******************************************************************************/
void USART6_SendData(uint8_t *buf, uint16_t cnt)
{
    if (cnt > 256) cnt = 256;                      // 本函数只适用于最大发送256个字节; 如果超过最大发送量，请自行分包发送，或者重写本函数

    for (uint16_t i = 0; i < cnt; i++)
        usart6TxBuffer[usart6TxCount++] = buf[i];

    if ((USART6->CR1 & 1 << 7) == 0)               // 检查发送缓冲区空置中断(TXEIE)是否已打开
        USART6->CR1 |= 1 << 7;
}

/******************************************************************************
 * 函  数： vUSART6_SendString
 * 功  能： UART通过中断发送输出字符串,无需输入数据长度
 *         【适合场景】字符串，长度<=256字节
 *         【不 适 合】int,float等数据类型
 * 参  数： char* stringTemp   需发送数据的缓存首地址
 * 返回值： 元
 ******************************************************************************/
void USART6_SendString(char *stringTemp)
{
    uint16_t num = 0;                                 // 字符串长度
    char *t = stringTemp ;                       // 用于配合计算发送的数量
    while (*t++ != 0)  num++;                    // 计算要发送的数目，这步比较耗时，测试发现每多6个字节，增加1us，单位：8位

    USART6_SendData((u8 *)stringTemp, num);      // 注意调用函数所需要的真实数据长度;
}







//////////////////////////////////////////////////////////////  printf   //////////////////////////////////////////////////////////////
/******************************************************************************
 * 功  能： printf函数支持代码
 *         【特别注意】加入以下代码, 使用printf函数时, 不再需要选择use MicroLIB
 * 参  数：
 * 返回值：
 * 备  注： 最后修改_2020年07月15日
 ******************************************************************************/
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#pragma import(__use_no_semihosting)
struct __FILE
{
    int handle;
};                     // 标准库需要的支持函数
FILE __stdout;         // FILE 在stdio.h文件
void _sys_exit(int x)
{
    x = x;             // 定义_sys_exit()以避免使用半主机模式
}



int fputc(int ch, FILE *f)                   // 重定向fputc函数，使printf的输出，由fputc输出到UART,  这里使用串口1(USART1)
{
#if 1                                        // 方式1-使用常用的poll方式发送数据，比较容易理解，但等待耗时大  
    while ((USART1->SR & 0X40) == 0);        // 等待上一次串口数据发送完成
    USART1->DR = (u8) ch;                    // 写DR,串口1将发送数据
    return ch;
#else                                        // 方式2-使用queue+中断方式发送数据; 无需像方式1那样等待耗时，但要借助已写好的函数、环形缓冲
    USART1_SendData((uint8_t*)&ch, 1);
    return ch;
#endif
}

