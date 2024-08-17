#include "LCD_ILI9341.h"
#include "stdlib.h"
#include "font.h"



/*****************************************************************************
 ** 全局有效    声明、定义
****************************************************************************/
__attribute__((section(".noinit")))
volatile xLCD_TypeDef xLCD;	                                     // 管理LCD重要参数





/*****************************************************************************
 ** 本地有效    声明、定义
****************************************************************************/
#define LCD_BL_ON    LCD_BL_GPIO-> BSRRL = LCD_BL_PIN;   // 背光引脚，置高电平
#define LCD_BL_OFF   LCD_BL_GPIO-> BSRRH = LCD_BL_PIN;   // 背光引脚，置低电平

static void setDir(void);                                // 设置屏幕显示方向
static void setCursor(uint16_t Xpos, uint16_t Ypos);	 // 设置光标

typedef struct                                           // LCD地址结构体
{
	uint16_t LCD_REG;
	uint16_t LCD_RAM;
} LCD_TypeDef;
//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A6作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111 1110=0X7E			    
#define LCD       ((volatile LCD_TypeDef *) 0x6001FFFE)           // (0x60000000 | 0x0001FFFE)



// us延时
static void delay_us(volatile uint32_t times)   // 定义一个us延时函数，减少移植时对外部文件依赖; 本函数仅作粗略延时使用，而并非精准延时;
{                                          
    times = times * 20;                    
    while (--times)                        
        __nop();                           
}                                      
                                           
                                           
                                           
// ms延时                                  
static void delay_ms(volatile uint32_t ms)           // 定义一个ms延时函数，减少移植时对外部文件依赖; 本函数仅作粗略延时使用，而并非精准延时;
{                                          
    ms = ms * 42001;                        // 注意：此参考值运行条件：打勾 Options/ c++ / One ELF Section per Function
    for (volatile uint32_t i = 0; i < ms; i++);      // 注意系统时钟下，大约多少个空循环耗时1ms
}                                          



// 读寄存器; 
uint16_t  readReg(volatile uint16_t  LCD_Reg)
{
    LCD->LCD_REG=LCD_Reg;      // 写入要读的寄存器序号
    delay_us(5);
    return LCD->LCD_RAM;       // 返回读到的值
}



// BGR转换RGB值; 返回值：RGB格式的颜色值
uint16_t  LCD_BGR2RGB( uint16_t  c)
{
     uint16_t   r, g, b, rgb;
    b = (c >> 0) & 0x1f;
    g = (c >> 5) & 0x3f;
    r = (c >> 11) & 0x1f;
    rgb = (b << 11) + (g << 5) + (r << 0);
    return (rgb);
}



// 读取个某点的颜色值; x,y:坐标、返回值:此点的颜色
uint16_t  LCD_ReadPoint( uint16_t  x,  uint16_t  y)
{
     uint16_t  r = 0, g = 0, b = 0;
    if (x >= xLCD.width || y >= xLCD.height)return 0; // 超过了范围,直接返回
    setCursor(x, y);
    LCD->LCD_REG=0X2E;                                // 发送读GRAM指令

    r = LCD->LCD_RAM;                                 // dummy Read

    delay_us (20);
    r = LCD->LCD_RAM;                                 // 实际坐标颜色

    delay_us (20);
    b = LCD->LCD_RAM;
    g = r & 0XFF;                                     // 第一次读取的是RG的值,R在前,G在后,各占8位
    g <<= 8;

    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));
}



//LCD开启显示
void LCD_DisplayOn(void)
{
    LCD->LCD_REG = 0X29;  // 开启显示
}



//LCD关闭显示
void LCD_DisplayOff(void)
{
    LCD->LCD_REG = 0X28;  // 关闭显示
}



//设置光标位置; Xpos:横坐标、Ypos:纵坐标
static void setCursor( uint16_t  Xpos,  uint16_t  Ypos)
{
    LCD->LCD_REG = 0X2A;
    LCD->LCD_RAM = Xpos >> 8;
    LCD->LCD_RAM = Xpos & 0XFF;
    LCD->LCD_REG = 0X2B;
    LCD->LCD_RAM = Ypos >> 8;
    LCD->LCD_RAM = Ypos & 0XFF;
}



/******************************************************************
 * 函数名： LCD_DrawPoint
 * 功  能： 画点函数
 * 参  数： x,y:    坐标 
 *          _color: 此点的颜色
 * 备  注： 
 *****************************************************************/
void LCD_DrawPoint( uint16_t  x,  uint16_t  y,  uint16_t _color)
{
    LCD->LCD_REG = 0X2A;        // 设置x坐标
    LCD->LCD_RAM = x >> 8;
    LCD->LCD_RAM = x & 0XFF;
    LCD->LCD_REG = 0X2B;        // 设置y坐标
    LCD->LCD_RAM = y >> 8;
    LCD->LCD_RAM = y & 0XFF;
    LCD->LCD_REG = 0X2C;        // 开始写GRAM
    LCD->LCD_RAM = _color;
}



//设置LCD显示方向
void setDir(void)
{
     uint16_t  regval = 0;
     uint16_t  temp;

    if (LCD_DIR == 0 || LCD_DIR == 3) // 竖屏
    {
        xLCD.dir = 0;
        xLCD.width = LCD_WIDTH;
        xLCD.height = LED_HEIGHT;
    }
    else                              // 横屏
    {
        xLCD.dir = 1;
        xLCD.width = LED_HEIGHT;
        xLCD.height = LCD_WIDTH;
    }
	
    if (LCD_DIR == 0) regval |= (0 << 7) | (0 << 6) | (0 << 5); // 从左到右,从上到下
    if (LCD_DIR == 3) regval |= (1 << 7) | (1 << 6) | (0 << 5); // 从右到左,从下到上
    if (LCD_DIR == 5) regval |= (0 << 7) | (1 << 6) | (1 << 5); // 从上到下,从右到左
    if (LCD_DIR == 6) regval |= (1 << 7) | (0 << 6) | (1 << 5); // 从下到上,从左到右

    regval |= 0X08;
    LCD->LCD_REG = 0X36;     // 写入要写的寄存器序号
    LCD->LCD_RAM = regval;   // 写入数据

    if (regval & 0X20)
    {
        if (xLCD.width < xLCD.height)  // 交换X,Y
        {
            temp = xLCD.width;
            xLCD.width = xLCD.height;
            xLCD.height = temp;
        }
    }
    else
    {
        if (xLCD.width > xLCD.height)  // 交换X,Y
        {
            temp = xLCD.width;
            xLCD.width = xLCD.height;
            xLCD.height = temp;
        }
    }

    LCD->LCD_REG = 0X2A;
    LCD->LCD_RAM = 0;
    LCD->LCD_RAM = 0;
    LCD->LCD_RAM = (xLCD.width - 1) >> 8;
    LCD->LCD_RAM = (xLCD.width - 1) & 0XFF;
    LCD->LCD_REG = 0X2B;
    LCD->LCD_RAM = 0;
    LCD->LCD_RAM = 0;
    LCD->LCD_RAM = (xLCD.height - 1) >> 8;
    LCD->LCD_RAM = (xLCD.height - 1) & 0XFF;
}



/******************************************************************
 * 函数名： LCD_Init
 * 功  能： 初始化LCD，适用驱动芯片ILI9341
 * 参  数： 
 * 备  注： 
 *****************************************************************/
void LCD_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;
    FSMC_NORSRAMTimingInitTypeDef  writeTiming;
    
    xLCD.FlagInit =0;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE); //使能PD,PE,PF,PG时钟
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);     // 使能FSMC时钟

    // 背光
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;               // PA15 推挽输出,控制背光
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;            // 普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        // 50MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             // 上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   // 初始化 ,推挽输出,控制背光

    GPIO_InitStructure.GPIO_Pin   = (3 << 0) | (3 << 4) | (7 << 8) | (3 << 14); //PD0,1,4,5,8,9,10,14,15 AF OUT
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            // 复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       // 100MHz
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            // 上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);                   // 初始化

    GPIO_InitStructure.GPIO_Pin = (0X1FF << 7);              // PE7~15,AF OUT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;             // 复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       // 100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             // 上拉
    GPIO_Init(GPIOE, &GPIO_InitStructure);                   // 初始化
                                                             
    // RS_PD11                                               
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;               // PF12,RS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;             // 复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       // 100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             // 上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);                   // 初始化
    // NE4_PD7                                               
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                // PD7, FSMC_NE1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;             // 复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       // 100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             // 上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);                   // 初始化

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);  // D2
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);  // D3
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);  // NOE_RD
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);  // NWE_WE
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);  // D13
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);  // D14
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC); // D15
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC); // D0
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC); // D1

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FSMC);  //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FSMC);  //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FSMC);  //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC); //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC); //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC); //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC); //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC); //
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC); //

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC); // RS
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);  // CS

    readWriteTiming.FSMC_AddressSetupTime = 0XF;             // 地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns
    readWriteTiming.FSMC_AddressHoldTime = 0x00;             // 地址保持时间（ADDHLD）模式A未用到
    readWriteTiming.FSMC_DataSetupTime = 60;                 // 数据保存时间为60个HCLK    =6*60=360ns
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;     // 模式A

    writeTiming.FSMC_AddressSetupTime = 9;                   // 地址建立时间（ADDSET）为9个HCLK =54ns
    writeTiming.FSMC_AddressHoldTime = 0x00;                 // 地址保持时间（A
    writeTiming.FSMC_DataSetupTime = 8;                      // 数据保存时间为6ns*9个HCLK=54ns
    writeTiming.FSMC_BusTurnAroundDuration = 0x00;
    writeTiming.FSMC_CLKDivision = 0x00;
    writeTiming.FSMC_DataLatency = 0x00;
    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;         // 模式A

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;                       // 这里我们使用NE4 ，也就对应BTCR[6],[7]。
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;     // 不复用数据地址
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;                // FSMC_MemoryType_SRAM;  //SRAM
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;       // 存储器数据宽度为16bit
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;   // FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;      // 存储器写使能
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;          // 读写使用不同的时序
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;         // 读写时序
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;                 // 写时序
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);                                    // 初始化FSMC配置

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  // 使能BANK1

    delay_ms(50);                    // delay 50 ms
    LCD->LCD_REG = 0x0000;           // 写入要写的寄存器序号
    LCD->LCD_RAM = 0x0000;           // 写入数据
    delay_ms(50);                    // delay 50 ms
    xLCD.id = readReg(0x0000);

//    if (xLCD.id < 0XFF || xLCD.id == 0XFFFF || xLCD.id == 0X9300) //读到ID不正确,新增xLCD.id==0X9300判断，因为9341在未被复位的情况下会被读成9300
//    {        
        LCD->LCD_REG=0XD3;           // 尝试9341 ID的读取
        xLCD.id = LCD->LCD_RAM;      // dummy read
        xLCD.id = LCD->LCD_RAM;      // 读到0X00
        xLCD.id = LCD->LCD_RAM;      // 读取93
        xLCD.id <<= 8;
        xLCD.id |= LCD->LCD_RAM;     // 读取41
//    }
    printf("LCD Chip ID: %x\r\n", xLCD.id);    //打印 LCD ID
	
    //重新配置写时序控制寄存器的时序
    FSMC_Bank1E->BWTR[6] &= ~(0XF << 0); // 地址建立时间(ADDSET)清零
    FSMC_Bank1E->BWTR[6] &= ~(0XF << 8); // 数据保存时间清零
    FSMC_Bank1E->BWTR[6] |= 3 << 0;      // 地址建立时间(ADDSET)为3个HCLK =18ns
    FSMC_Bank1E->BWTR[6] |= 2 << 8;      // 数据保存时间(DATAST)为6ns*3个HCLK=18ns

    LCD->LCD_REG=0xCF;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0xC1;
    LCD->LCD_RAM=0X30;
    LCD->LCD_REG=0xED;
    LCD->LCD_RAM=0x64;
    LCD->LCD_RAM=0x03;
    LCD->LCD_RAM=0X12;
    LCD->LCD_RAM=0X81;
    LCD->LCD_REG=0xE8;
    LCD->LCD_RAM=0x85;
    LCD->LCD_RAM=0x10;
    LCD->LCD_RAM=0x7A;
    LCD->LCD_REG=0xCB;
    LCD->LCD_RAM=0x39;
    LCD->LCD_RAM=0x2C;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x34;
    LCD->LCD_RAM=0x02;
    LCD->LCD_REG=0xF7;
    LCD->LCD_RAM=0x20;
    LCD->LCD_REG=0xEA;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x00;
    LCD->LCD_REG=0xC0;    // Power control
    LCD->LCD_RAM=0x1B;    // VRH[5:0]
    LCD->LCD_REG=0xC1;    // Power control
    LCD->LCD_RAM=0x01;    // SAP[2:0];BT[3:0]
    LCD->LCD_REG=0xC5;    // VCM control
    LCD->LCD_RAM=0x30;    // 3F
    LCD->LCD_RAM=0x30;    // 3C
    LCD->LCD_REG=0xC7;    // VCM control2
    LCD->LCD_RAM=0XB7;
    LCD->LCD_REG=0x36;    // Memory Access Control
    LCD->LCD_RAM=0x48;
    LCD->LCD_REG=0x3A;
    LCD->LCD_RAM=0x55;
    LCD->LCD_REG=0xB1;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x1A;
    LCD->LCD_REG=0xB6;    // Display Function Control
    LCD->LCD_RAM=0x0A;
    LCD->LCD_RAM=0xA2;
    LCD->LCD_REG=0xF2;    // 3Gamma Function Disable
    LCD->LCD_RAM=0x00;
    LCD->LCD_REG=0x26;    // Gamma curve selected
    LCD->LCD_RAM=0x01;
    LCD->LCD_REG=0xE0;    // Set Gamma
    LCD->LCD_RAM=0x0F;
    LCD->LCD_RAM=0x2A;
    LCD->LCD_RAM=0x28;
    LCD->LCD_RAM=0x08;
    LCD->LCD_RAM=0x0E;
    LCD->LCD_RAM=0x08;
    LCD->LCD_RAM=0x54;
    LCD->LCD_RAM=0XA9;
    LCD->LCD_RAM=0x43;
    LCD->LCD_RAM=0x0A;
    LCD->LCD_RAM=0x0F;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x00;
    LCD->LCD_REG=0XE1;     // Set Gamma
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x15;
    LCD->LCD_RAM=0x17;
    LCD->LCD_RAM=0x07;
    LCD->LCD_RAM=0x11;
    LCD->LCD_RAM=0x06;
    LCD->LCD_RAM=0x2B;
    LCD->LCD_RAM=0x56;
    LCD->LCD_RAM=0x3C;
    LCD->LCD_RAM=0x05;
    LCD->LCD_RAM=0x10;
    LCD->LCD_RAM=0x0F;
    LCD->LCD_RAM=0x3F;
    LCD->LCD_RAM=0x3F;
    LCD->LCD_RAM=0x0F;
    LCD->LCD_REG=0x2B;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x01;
    LCD->LCD_RAM=0x3f;
    LCD->LCD_REG=0x2A;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0x00;
    LCD->LCD_RAM=0xef;
    LCD->LCD_REG=0x11;    // Exit Sleep
    delay_ms(120);
    LCD->LCD_REG=0x29;    // display on

    setDir();             // 设置显示的方向
    LCD_BL_ON;            // 打开LCD背光
    LCD_Fill(0, 0,xLCD.width, xLCD.height ,WHITE);
    xLCD.FlagInit =1;
}



/******************************************************************
 * 函数名： LCD_Fill
 * 功  能： 在指定区域内填充单个颜色
 * 参  数： uint16_t sx     左上角X坐标
 *          uint16_t sy     左上角Y坐标
 *          uint16_t ex     右下角X坐标
 *          uint16_t ey     右下角Y坐标
 *          uint16_t color  颜色值
 * 备  注： 
 *****************************************************************/
void LCD_Fill( uint16_t sx,  uint16_t sy,  uint16_t ex,  uint16_t ey,  uint16_t color)
{
     uint16_t  i, j;
     uint16_t  xlen = 0;
    xlen = ex - sx + 1;
    for (i = sy; i <= ey; i++)
    {
        setCursor(sx, i);          // 设置光标位置
        LCD->LCD_REG = 0X2C;       // 开始写GRAM
        for (j = 0; j < xlen; j++)
        LCD->LCD_RAM = color;      // 显示颜色
    }
}



/******************************************************************
 * 函数名： LCD_Line
 * 功  能： 画直线
 * 参  数： uint16_t x1     起点X坐标
 *          uint16_t y1     起点Y坐标
 *          uint16_t x2     终点X坐标
 *          uint16_t y2     终点Y坐标
 *          uint16_t color  颜色值
 * 备  注： 
 *****************************************************************/
void LCD_Line( uint16_t  x1,  uint16_t  y1,  uint16_t  x2,  uint16_t  y2,  uint16_t _color)
{
     uint16_t  t;
     int xerr = 0, yerr = 0, delta_x, delta_y, distance;
     int incx, incy, uRow, uCol;
    delta_x = x2 - x1;                         // 计算坐标增量
    delta_y = y2 - y1;                         
    uRow = x1;                                 
    uCol = y1;                                 
    if (delta_x > 0)incx = 1;                  // 设置单步方向
    else if (delta_x == 0)incx = 0;            // 垂直线
    else                                       
    {                                          
        incx = -1;                             
        delta_x = -delta_x;                    
    }                                          
    if (delta_y > 0)incy = 1;                  
    else if (delta_y == 0)incy = 0;            // 水平线
    else                                       
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)distance = delta_x; // 选取基本增量坐标轴
    else distance = delta_y;
    for (t = 0; t <= distance + 1; t++)       // 画线输出
    {
        LCD_DrawPoint(uRow, uCol, _color);    // 画点
        xerr += delta_x ;
        yerr += delta_y ;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}



/******************************************************************
 * 函数名： LCD_Circle
 * 功  能： 在指定位置画圆
 * 参  数： uint16_t Xpos     X坐标
 *          uint16_t Ypos     起点Y坐标
 *          uint16_t Radius   半径
 *          uint16_t _color   颜色
 * 备  注： 
 *****************************************************************/
void LCD_Circle( uint16_t Xpos,  uint16_t Ypos,  uint16_t Radius,  uint16_t _color)
{
     int16_t mx = Xpos, my = Ypos, x = 0, y = Radius;
     int16_t d = 1 - Radius;
    while (y > x)
    {
        LCD_DrawPoint(x + mx, y + my, _color);
        LCD_DrawPoint(-x + mx, y + my, _color);
        LCD_DrawPoint(-x + mx, -y + my, _color);
        LCD_DrawPoint(x + mx, -y + my, _color);
        LCD_DrawPoint(y + mx, x + my, _color);
        LCD_DrawPoint(-y + mx, x + my, _color);
        LCD_DrawPoint(y + mx, -x + my, _color);
        LCD_DrawPoint(-y + mx, -x + my, _color);
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}



/******************************************************************
 * 函数名： drawAscii
 * 功  能： 在指定位置显示一个字符
 * 参  数： uint16_t x,y     起始坐标
 *          uint8_t  num     要显示的字符:" "--->"~"
 *          uint8_t  size    字体大小 12/16/24/32
 *          uint32_t bColor  背景颜色
 *          uint32_t fColor  字体颜色
 * 备  注： 参考原子哥和野火大神的代码后修改
 *****************************************************************/
void drawAscii( uint16_t x,  uint16_t y,  uint8_t num,  uint8_t size,  uint32_t bColor,  uint32_t fColor)
{
    static  uint8_t temp;
    static  uint8_t csize;
    static  uint16_t y0;

    y0 = y;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);  // 得到字体一个字符对应点阵集所占的字节数
    num = num - ' ';                                         // 得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
    for (uint8_t t = 0; t < csize; t++)
    {
        if (size == 12)         temp = aFontASCII12[num][t]; // 调用1206字体
        else if (size == 16)    temp = aFontASCII16[num][t]; // 调用1608字体
        else if (size == 24)    temp = aFontASCII24[num][t]; // 调用2412字体
        else if (size == 32)    temp = aFontASCII32[num][t]; // 调用3216字体
        else                    return;                      // 没有字模 
                                                             
        for (uint8_t t1 = 0; t1 < 8; t1++)                   
        {                                                    
            if (temp & 0x80) LCD_DrawPoint(x, y, fColor);    // 字体 画点
            else             LCD_DrawPoint(x, y, bColor);    // 背景 画点
                                                             
            temp <<= 1;                                      
            y++;                                             
            if (y >= xLCD.height)    return;                 // 超出屏幕高度(底)
            if ((y - y0) == size)                            
            {                                                
                y = y0;                                      
                x++;                                         
                if (x >= xLCD.width) return;                 // 超出屏幕宽度(宽)
                break;
            }
        }
    }
}



/******************************************************************
 * 函数名： drawGBK
 * 功  能： 在指定位置显示一个字符
 * 参  数： uint16_t x,y     起始坐标
 *          uint8_t  num     要显示的字符:" "--->"~"
 *          uint8_t  size    字体大小 12/16/24/32
 *          uint32_t bColor  背景颜色
 *          uint32_t fColor  字体颜色
 * 备  注： 参考原子哥和野火大神的代码后修改
 *****************************************************************/
void drawGBK( uint16_t x,  uint16_t y, uint8_t *font,  uint8_t size,  uint32_t bColor,  uint32_t fColor)
{
    static  uint8_t temp;
    static  uint16_t y0;
    static  uint8_t GBK[128];
    static  uint8_t csize;

    csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size);     // 得到字体一个字符对应点阵集所占的字节数
    W25Q128_ReadGBK(font, size, GBK);                       // 得到相应大小的点阵数据


    y0 = y;
    for (uint8_t t = 0; t < csize; t++)
    {
        temp = GBK[t];                                      // 得到GBK点阵数据
        for (uint8_t t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)   LCD_DrawPoint(x, y, fColor);
            else               LCD_DrawPoint(x, y, bColor);
            temp <<= 1;
            y++;
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}



/******************************************************************************
 * 函  数： LCD_String
 * 功  能： 在LCD上显示字符串(支持英文、汉字)
 * 描  述： 英文：字模数据保存在font.h，编译后和代码一起保存在芯片内部Flash
 *          汉字：字模保存在外部Flash中，本函数字库在W25Q128中
 *                魔女开发板中W25Q128已烧录宋体4种字号大小字模数据
 * 参  数： uint16_t   x      字体左上角X坐标
 *          uint16_t   y      字体左上角y坐标
 *          char* pFont  要显示的字符串数据
 *          uint8_t    size   字号大小：12 16 24 32
 *          uint32_t   bColor 背景颜色
 *          uint32_t   fColor 字体颜色
 * 返回值:  无
 * 备  注： 最后修改_2020年05月1８日
 ******************************************************************************/
void LCD_String( uint16_t x,  uint16_t y,  char *pFont,  uint8_t size,  uint32_t bColor,  uint32_t fColor)
{
    if (xLCD .FlagInit == 0) return;

     uint16_t xStart = x;
	
    if (size != 12 && size != 16 && size != 24 && size != 32) // 字体大小控制
        size = 24;

    while (*pFont != 0)               // 连续读取字符串数据，直到'\0'时停止
    {
        if (x > (xLCD.width - size))  // 行位置判断，如果到了行末，就把光标换行
        {
            x = xStart;
            y = y + size;
        }
        if (y > (xLCD.height - size)) // 列位置判断，如果到了列末，就返回，不再输出
            return;

        if (*pFont < 127)             // ASCII字符
        {
            drawAscii(x, y, *pFont, size, bColor, fColor);
            pFont++;
            x += size / 2;
        }
        else                          // 汉字显示
        {
            // 重要: 如果用的不是魔女开发板的字库, 就要修改或注释下面这一行, 这样就不影响ASCII英文字符的输出
            drawGBK(x, y, (uint8_t *)pFont, size, bColor, fColor);
            pFont = pFont + 2;        // 下一个要显示的数据在内存中的位置
            x = x + size;             // 下一个要显示的数据在屏幕上的X位置
        }
    }
}



/******************************************************************
 * 函数名： LCD_Image
 * 功  能： 在指定区域内填充指定图片数据
 *          图片数据在font.h文件中.只适合少量图片保存
 *          Image2Lcd转换：水平扫描，16位真彩色
 * 参  数： uint16_t x,y     左上角起始坐标
 *          uint16_t width   图片宽度
 *          uint16_t height  图片高度
 *          u8* image   数据缓存地址
 *****************************************************************/
void LCD_Image( uint16_t x,  uint16_t y,  uint16_t width,  uint16_t height, const  uint8_t *image)
{
     uint32_t cnt = 0;

    for (uint16_t i = 0; i < height; i++)      // 一行一行地显示
    {
        LCD->LCD_REG = 0X2A;                   // 设置x坐标
        LCD->LCD_RAM = x >> 8;
        LCD->LCD_RAM = x & 0XFF;
        LCD->LCD_REG = 0X2B;                   // 设置y坐标
        LCD->LCD_RAM = (y+i) >> 8;
        LCD->LCD_RAM = (y+i) & 0XFF;
        LCD->LCD_REG = 0X2C;                   // 开始写GRAM
        for (uint16_t j = 0; j < width; j++)   // 一行中，从左到事，逐个像素处理
        {
            LCD->LCD_RAM = (image[cnt * 2 + 1] << 8) | image[cnt * 2];  // 写入16位颜色数据
            cnt++;
        }
    }
}



/******************************************************************
 * 函数名： LCD_ShowChinese
 * 功  能： 显示自行取模的汉字,
 *          字库数据在font文件中，只适合少量汉字固定输出
 *          PCtoLCD2018取模：阴码+列行式+逆向+C51格式
 * 参  数： uint16_t  x         坐标x
 *          uint16_t  y         坐标y
 *          uint8_t   index     字模数据在数组中的序号
 *          uint32_t  bColor    字体背景颜色
 *          uint32_t  fColor    字体颜色
 * 返  回:  无
 *****************************************************************/
void LCD_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint32_t bColor, uint32_t fColor)
{
    uint8_t m, temp;
    uint8_t x0 = x, y0 = y;
    uint16_t size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; // 得到字体一个字符对应点阵集所占的字节数

    for (uint16_t i = 0; i < size3; i++)
    {
        if (size1 == 12)
        {
            temp = aFontChinese12[num][i];   // 调用12*12字体
        }
        else if (size1 == 16)
        {
            temp = aFontChinese16[num][i];   // 调用16*16字体
        }
        else if (size1 == 24)
        {
            temp = aFontChinese24[num][i];   // 调用24*24字体
        }
        else if (size1 == 32)
        {
            temp = aFontChinese32[num][i];   // 调用32*32字体
        }
        else
        {
            temp = aFontChinese12[num][i];   // 如果是非法字形，则调用12*12字体
        }
        for (m = 0; m < 8; m++)
        {
            if (temp & 0x01)
                LCD_DrawPoint(x, y, fColor);
            else
                LCD_DrawPoint(x, y, bColor);
            temp >>= 1;
            y++;
        }
        x++;
        if ((x - x0) == size1)
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}



/******************************************************************
 * 函数名： LCD_Cross
 * 功  能： 在指定点上绘制十字线，用于校准触摸屏
 * 参  数： uint16_t x  　   十字线的中心点坐标x
 *          uint16_t y  　   十字线的中心点坐标x
 *          uint16_t len     十字线的像素长度
 *          uint32_t fColor  颜色
 * 返　回： 无
 * 备  注：
 *****************************************************************/
void LCD_Cross(uint16_t x, uint16_t y, uint16_t len, uint32_t fColor)
{
    uint16_t temp = len / 2;

    LCD_Line(x - temp, y, x + temp, y, fColor);
    LCD_Line(x, y - temp, x, y + temp, fColor);
}



/******************************************************************
 * 函数名： LCD_GUI
 * 功  能： 测试板载设备情况的LCD显示方案
 * 参  数：
 * 返　回：
 * 备  注：
 *****************************************************************/
void LCD_GUI(void)
{
    char strTemp[30];

    // 全屏背景-黑屏
    LCD_Fill(0, 0,  xLCD.width,  xLCD.height, BLACK);

    LCD_String(8,  0, "STM32F407VET6开发板", 24, BLACK, WHITE);
    LCD_String(72, 28, "设备检测监控", 16, BLACK, GREY); 

     // 边框
    LCD_Line(0, 49,  0, 329, GREY);                         // 左竖
    LCD_Line(119, 70, 119, 329, GREY);                      // 中竖
    LCD_Line(239, 49, 239, 329, GREY);                      // 右竖

    LCD_Fill(0, 49, 239, 70, WHITE);
    LCD_String(6, 52, "板载设备", 16, WHITE,  BLACK);
    LCD_String(125, 52, "WiFi无线通信", 16, WHITE, BLACK);

    LCD_Fill(119, 125, 239, 145, WHITE);
    LCD_String(125, 127, "CAN通信", 16, WHITE, BLACK);

    LCD_Fill(119, 205, 239, 225, WHITE);
    LCD_String(125, 207, "RS485通信", 16, WHITE, BLACK);

    // 底部状态栏-背景
    LCD_Fill(0, 287, 239, 329, WHITE);                     // 底白
    LCD_Line(0, 303, 239, 303, BLACK);                     
    LCD_Line(119, 287, 119, 329, BLACK);                   
    LCD_Line(119, 49, 119, 70, BLACK);                     // 中竖
    // 底部状态栏-文字
    LCD_String(6, 290, "内部温度", 12, WHITE, BLACK);      // 内部温度
    LCD_String(6, 306, "启动次数", 12, WHITE, BLACK);      // 启动次数
    LCD_String(125, 290, "触摸坐标", 12, WHITE, BLACK);    // 触摸坐标
    LCD_String(125, 306, "运行时长", 12, WHITE, BLACK);    // 运行时长
    sprintf(strTemp, "第%d次", xW25Q128 .StartupTimes);
    LCD_String(68, 306, strTemp, 12, WHITE, BLUE);

    uint16_t y = 74;
    // UASRT1
    LCD_String(6, y, "UART1配置",  12, BLACK, YELLOW);
    if (xUSART1.InitFlag == 1)
    {
        LCD_String(90, y, "完成", 12, BLACK, GREEN);
    }
    else
    {
        LCD_String(90, y, "失败", 12, BLACK, RED);
    }
    y = y + 15;
    // SystemClock
    LCD_String(6, y, "系统时钟",   12,BLACK, YELLOW);
    sprintf(strTemp, "%d", SystemCoreClock / 1000000);
    LCD_String(84, y, strTemp,       12, BLACK, GREEN);
    LCD_String(96, y, "MHz", 12, BLACK, GREEN);
    y = y + 15;
    // LED指示灯
    LCD_String(6, y, "LED指示灯",  12, BLACK, YELLOW);
    LCD_String(90, y, "完成", 12, BLACK, GREEN);
    y = y + 15;
    // 按键中断
    LCD_String(6, y, "按键中断",   12, BLACK, YELLOW);
    LCD_String(90, y, "完成", 12, BLACK, GREEN);
    y = y + 15;
    // FLASH存储器
    LCD_String(6, y, "FLASH存储",  12, BLACK, YELLOW);
    if (xW25Q128.FlagInit  == 1)
    {
        LCD_String(71, y, xW25Q128.type, 12, BLACK, GREEN);
    }
    else
    {
        LCD_String(90, y, "失败", 12, BLACK, RED);
    }
    y = y + 15;
    // 汉字字库
    LCD_String(6, y, "汉字字库",   12, BLACK, YELLOW);
    if (xW25Q128 .FlagGBKStorage == 1)
    {
        LCD_String(90, y, "正常", 12, BLACK, GREEN);
    }
    else
    {
        LCD_String(90, y, "失败", 12, BLACK, RED);
    }
    y = y + 15;
    // 显示屏
    LCD_String(6, y, "显示屏芯片", 12, BLACK, YELLOW);
    sprintf(strTemp, "%X", xLCD.id);
    if (xLCD.FlagInit  == 1)
    {
        LCD_String(90, y, strTemp, 12, BLACK, GREEN);
    }
    else
    {
        LCD_String(90, y, "失败", 12, BLACK, RED);
    }
    y = y + 15;
}


//在指定区域内填充指定颜色块
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)
//color:要填充的颜色
void LCD_Color_Fill( u16 sx, u16 sy, u16 ex, u16 ey, u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//得到填充的宽度
	height=ey-sy+1;			//高度
 	for(i=0;i<height;i++)
	{
 		setCursor(sx,sy+i);   		//设置光标位置      
		LCD->LCD_REG = 0x2C;		//开始写入GRAM
		for(j=0;j<width;j++)
		{	
			LCD->LCD_RAM=color[i*width+j];	//写入数据 
		}
	}		  
}  


