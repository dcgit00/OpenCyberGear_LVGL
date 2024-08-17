#include "stm32f4xx.h"
#include "led.h"
#include "USART.h"
#include "Timer.h"
#include "LCD_ILI9341.h"
#include "XPT2046.h"
#include "CyberGear.h"
#include "RTC.h"
#include "stdlib.h"

//LVGL
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_conf.h"
//GUI GUIDER
#include "gui_guider.h"
#include "events_init.h"

//作者邮箱：fanghui20220@163.com
//CSDN:奔跑的蜗牛！	https://blog.csdn.net/weixin_49337111?type=blog

lv_ui guider_ui;

int main(void)                                         
{   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RTC_Config();
    USART1_Init(115200); 
	printf("\r\n---------------Program Starting---------------\r\n");
    TIM2_Init();                                               
    Led_Init();                                          
	LED_RED_OFF;											
    LED_BLUE_OFF;
	W25Q128_Init ();                                     // 外部Flash 初始化，其内部存储有汉字字模数据
	RTC_Set(2024, 5, 30, 4, 16, 18, 00);
    LCD_Init();                                          
    XPT2046_Init(xLCD.width , xLCD.height, xLCD.dir);   
    XPT2046_Cmd(ENABLE);                                 
	
	LCD_Fill (0, 0, 240, 320, BLACK); 
	LCD_String(0, 160, " System Starting...", 24, BLACK, WHITE);
	
	CyberGear_Init();
	lv_init();			  // lvgl系统初始化
	lv_port_disp_init();  // lvgl显示接口初始化,放在lv_init()的后面
	lv_port_indev_init(); // lvgl输入接口初始化,放在lv_init()的后面
	
	setup_ui(&guider_ui);
   	events_init(&guider_ui);
	
	
	while (1)                                            // while函数死循环，不能让main函数运行结束，否则会产生硬件错误
    {                                                  
		lv_task_handler(); // lvgl的事务处理
    }
}
