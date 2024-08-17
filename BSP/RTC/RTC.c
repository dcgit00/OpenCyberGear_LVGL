#include "RTC.h"
#include "string.h"



xRTC_TypeDef xRTC;






/******************************************************************************
 * 函  数： delay_ms
 * 功  能： 简单的ms延时函数; 减少移植时对外部文件依赖;
 * 参  数： uint32_t ms:  毫秒
 * 返回值： 无
 ******************************************************************************/
static void delay_ms(uint32_t ms)                           // 本函数仅作粗略延时使用，而并非精准延时;
{
    ms = ms * 42001;                                        // 注意：此参考值运行条件：打勾 Options/ c++ / One ELF Section per Function
    for (uint32_t i = 0; i < ms; i++);                      // 注意系统时钟下，大约多少个空循环耗时1ms
}



/******************************************************************************
 * 函  数： writeBackupRegister
 * 功  能： 向指定RTC备份数据寄存器写入数据
 * 参  数： uint32_t registerNum： 要写入数据的寄存器编号, 取值范围：0~19
 *          uint32_t Data       :  将要写入的数据
 * 返回值： 无
 ******************************************************************************/
static void writeBackupRegister(uint32_t registerNum, uint32_t Data)
{
    __IO uint32_t tmp = 0;
    tmp = RTC_BASE + 0x50 + registerNum * 4;
    *(__IO uint32_t *)tmp = (uint32_t)Data;
}



/******************************************************************************
 * 函  数： readBackupRegister
 * 功  能： 读取指定RTC备份数据寄存器的数据
 * 参  数： uint32_t registerNum： 要读取数据的寄存器编号, 取值范围：0~19
 * 返回值： 读取到的数据，类型：uint32_t
 ******************************************************************************/
static uint32_t readBackupRegister(uint32_t registerNum)
{
    __IO uint32_t tmp = 0;
    tmp = RTC_BASE + 0x50 + registerNum * 4;
    return (*(__IO uint32_t *)tmp);
}



/******************************************************************************
 * 函  数： dec2bcd()
 * 功  能： 十进制转换为BCD码
 * 参  数： uint8_t value: 要转换的十进制数
 * 返回值:  BCD码
 ******************************************************************************/
static uint8_t dec2bcd(uint8_t value)
{
    uint8_t bcdHigh = 0;
    while (value >= 10)
    {
        bcdHigh++;
        value -= 10;
    }
    return ((uint8_t)(bcdHigh << 4) | value);
}



/******************************************************************************
 * 函  数： bcd2dec()
 * 功  能： BCD码转换为十进制数据
 * 参  数： uint8_t val  ：要转换的BCD码
 * 返回值:  十进制数据
 ******************************************************************************/
static uint8_t bcd2dec(uint8_t value)
{
    uint8_t temp = 0;
    temp = (value >> 4) * 10;
    return (temp + (value & 0X0F));
}



/******************************************************************************
 * 函  数： setRTCInitMode
 * 功  能： 设置RTC进入初始化模式，方可更新事件、日期和预分频器寄存器
 * 参  数： 无
 * 返回值:  0-成、1-失败;
 ******************************************************************************/
static uint8_t setRTCInitMode(void)
{
    uint16_t timeout = 0XFFFF;             // 超时
    if (RTC->ISR & (1 << 6))               // 判断RTC是否已处于初始化状态
        return 0;                          // 已是初始化模式，直接返回，此时可更新事件、日期和预分频器寄存器。
    RTC->ISR |= 1 << 7;                    // 设置RTC切换初始化模式，注意：计数器从新值开始计数
    while ((RTC->ISR & (1 << 6)) == 0x00)  // 等待RTC切换初始化模式就绪
    {
        if (timeout-- < 3)  return 1;      // RTC切换初始化模式失败，返回:1
        delay_ms(1);
    }
    return 0; 			                   // 切换成功，返回:0
}



/******************************************************************************
 * 函  数： RTC_Config
 * 功  能： 初始化RTC
 *
 * 参  数：
 * 返回值： 0_正常，1_开启LSE时钟超时未就绪，2-切换初始化模式失败
 ******************************************************************************/
uint8_t RTC_Config(void)
{
    uint16_t timeout = 0XFFFF;               // 超时

    xRTC.InitFlag = 0;                       // 标记，未初始化成功

    RCC->APB1ENR |= 1 << 28;                 // 使能PWR, 电源接口时钟
    PWR->CR |= 1 << 8;                       // 访问使能, RTC、RTC备份寄存器和备份SRAM的访问

    if (readBackupRegister(0) != 0X6666)     // 第一次配置
    {
        RCC->BDCR |= 1 << 0;                 // 开启LSE时钟; 使用LSI作RTC时钟源会有误差
        while ((RCC->BDCR & 0X02) == 0)      // 等待LSE时钟就绪
        {
            if (timeout-- < 3)  return 1;    // LSE超时还没就绪，LSE时钟开启失败
            delay_ms(1);
        }
        RCC->BDCR |= 1 << 8;			     // 选择LSE 振荡器时钟用作 RTC 时钟
        RCC->BDCR |= 1 << 15;			     // 使能RTC时钟

        RTC->WPR = 0xCA;                     // 解锁RTC寄存器写保护
        RTC->WPR = 0x53;
        if (setRTCInitMode())  return 2;     // RTC进入初始化模式，方可更新事件、日期和预分频器寄存器
        RTC->PRER = 0XFF;				     // RTC同步分频系数(0~7FFF); 通过两次独立的写访问执行初始化; ck_spre 频率 = ck_apre 频率/(PREDIV_S+1); 原子哥的公式：Frtc=Fclks/((Sprec+1)*(Asprec+1))
        RTC->PRER |= 0X7F << 16;		     // RTC异步分频系数(1~0X7F); ck_apre 频率 = RTCCLK 频率/(PREDIV_A+1);
        RTC->CR &= ~(1 << 6);			     // RTC设置为,24小时格式; 0_24小时模式，1_AM/PM小时格式
        RTC->ISR &= ~(1 << 7);               // 退出RTC初始化模式，即进入自由运行模式
        RTC->WPR = 0xFF;				     // 重新上锁RTC寄存器写保护
        RTC_Set(2023, 1, 6, 5, 17, 19, 00);	 // 设置年、月、日、星期、时、分、秒
        writeBackupRegister(0, 0X6666);	     // 标记
    }
    xRTC.InitFlag = 1;                       // 标记，已初始化成功
    return 0;
}



/******************************************************************************
 * 函  数： RTC_Set()
 * 功  能： 设置RTC日期、时间
 * 参  数： uint8_t year     年,   值范围：2000~2099
 *          uint8_t month    月,   值范围：1~12
 *          uint8_t day      日，  值范围：1~31
 *          uint8_t week     星期，值范围：1~7
 *          uint8_t hour     时_24小时格式
 *          uint8_t minute   分
 *          uint8_t second   秒
 * 返回值： 0_正常，1_未初始化, 2_切换初始化模式失败
 ******************************************************************************/
uint8_t RTC_Set(uint16_t year, uint8_t month, uint8_t day, uint8_t week, uint8_t hour, uint8_t minute, uint8_t second)
{
    year = year - 2000;

    RTC->WPR = 0xCA;                    // 解锁RTC寄存器写保护
    RTC->WPR = 0x53;
    if (setRTCInitMode())  return 2;    // RTC进入初始化模式，方可更新事件、日期和预分频器寄存器;

    RTC->DR = (((u32)week & 0X07) << 13) | ((u32)dec2bcd(year) << 16) | ((u32)dec2bcd(month) << 8) | (dec2bcd(day)); // 设置星期、年、月、日

    RTC->TR = (((u32)0x00) << 22) | ((u32)dec2bcd(hour) << 16) | ((u32)dec2bcd(minute) << 8) | (dec2bcd(second));    // 设置时、分、秒

    RTC->ISR &= ~(1 << 7);              // 退出RTC初始化模式，即进入自由运行模式
    RTC->WPR = 0xFF;			        // 重新上锁RTC寄存器写保护
    return 0;
}



/******************************************************************************
 * 函  数： RTC_Update()
 * 功  能： 更新RTC日期、时间等数据到缓存结构体xRTC的各变量中
 * 备  注： xRTC结构体具体变量为：
 *          uint16_t xRTC.Year        // 年，2000~2099
 *          uint8_t  xRTC.Month       // 月
 *          uint8_t  xRTC.Day         // 日
 *          uint8_t  xRTC.Week        // 星期，1~7
 *          uint8_t  xRTC.WeekChinese // 星期，一~七
 *          uint8_t  xRTC.Hour        // 时，24小时格式
 *          uint8_t  xRTC.Minute      // 分
 *          uint8_t  xRTC.Second      // 秒
 * 参  数： 无
 * 返回值： 0_正常，1_等待同步超时失败
 ******************************************************************************/
uint8_t RTC_Update(void)
{
    static uint32_t regTemp;
    static uint16_t timeout;                                  // 超时
    timeout = 0XFFFF;                                        
                                                             
    RTC->WPR = 0xCA;                                          // 解锁RTC寄存器写保护
    RTC->WPR = 0x53;                                         
                                                             
    RTC->ISR &= ~(1 << 5);		                              // 清0同步标志
    while (timeout && ((RTC->ISR & (1 << 5)) == 0x00))        // 等待寄存器同步，即等待日历寄存器的值复制到影子寄存器（RTC_SSRx、RTC_TRx 和 RTC_DRx）
    {                                                        
        timeout-- ;                                          
    }                                                        
    RTC->WPR = 0xFF;			                              // 重新上锁RTC寄存器写保护
    if (timeout == 0)                                         // 同步超时
    {
        return 1;                                             // 失败，返回：1
    }
    else                                                      // 同步成功
    {
        regTemp     = RTC->DR;                                // 读取日期寄存器
        xRTC.Year   = bcd2dec((regTemp >> 16) & 0XFF) + 2000; // 年
        xRTC.Month  = bcd2dec((regTemp >> 8) & 0X1F);         // 月
        xRTC.Day    = bcd2dec(regTemp & 0X3F);                // 日
        xRTC.Week   = (regTemp >> 13) & 0X07;                 // 星期
        regTemp     = RTC->TR;                                // 读取时间寄存器
        xRTC.Hour   = bcd2dec((regTemp >> 16) & 0X3F);        // 时
        xRTC.Minute = bcd2dec((regTemp >> 8) & 0X7F);         // 分
        xRTC.Second = bcd2dec(regTemp & 0X7F);                // 秒

        if(xRTC.Week ==1)   memcpy(&xRTC.WeekChinese,"一",3); // 星期一
        if(xRTC.Week ==2)   memcpy(&xRTC.WeekChinese,"二",3); // 星期二
        if(xRTC.Week ==3)   memcpy(&xRTC.WeekChinese,"三",3); // 星期三
        if(xRTC.Week ==4)   memcpy(&xRTC.WeekChinese,"四",3); // 星期四
        if(xRTC.Week ==5)   memcpy(&xRTC.WeekChinese,"五",3); // 星期五
        if(xRTC.Week ==6)   memcpy(&xRTC.WeekChinese,"六",3); // 星期六
        if(xRTC.Week ==7)   memcpy(&xRTC.WeekChinese,"日",3); // 星期日
        
        return 0;                                             // 读取成功，返回:0
    }
}

