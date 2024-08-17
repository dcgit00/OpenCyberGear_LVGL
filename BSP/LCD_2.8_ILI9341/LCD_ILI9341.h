#ifndef __LCD_ILI9341_H
#define __LCD_ILI9341_H		


#include "stm32f4xx.h" 
#include "stdlib.h" 
#include "W25Q128.h"  // 中文字库
#include "USART.h"    // 输出调试信息到串口软件





/*****************************************************************************
 ** 移植配置
 ** 
****************************************************************************/
#define LCD_BL_GPIO   GPIOA
#define LCD_BL_PIN    GPIO_Pin_15

#define LCD_WIDTH     240
#define LED_HEIGHT    320

#define LCD_DIR       0         // 四种显示方向，0-正竖屏，3-倒竖屏，5-正横屏, 6-倒横屏



/*****************************************************************************
 ** 全局变量
 ** (不用修改)
****************************************************************************/
typedef struct                  // LCD重要参数集
{										    
	uint16_t width;			    // LCD 宽度
	uint16_t height;		    // LCD 高度
	uint16_t id;			    // LCD ID
	uint8_t  dir;               // 横屏还是竖屏控制：0，竖屏；1，横屏。	
    uint8_t  FlagInit;          // 初始化完成标志
}xLCD_TypeDef; 	  
extern volatile xLCD_TypeDef xLCD;	    // 管理LCD重要参数


/******************************* 定义常用颜色值 *****************************/
#define      WHITE               0xFFFF       // 白色
#define      BLACK               0x0000       // 黑色 
#define      GREY                0xF7DE       // 灰色 
#define      GRAY  			     0X8430       // 灰色
#define      RED                 0xF800       // 红 
#define      MAGENTA             0xF81F       // 洋红色 
#define      GRED                0xFFE0       // 深红色
#define      BROWN 			     0XBC40       // 棕色
#define      BRRED 			     0XFC07       // 棕红色
#define      GREEN               0x07E0       // 绿 
#define      CYAN                0x7FFF       // 青色 
#define      YELLOW              0xFFE0       // 黄色 
#define      LIGHTGREEN          0X841F       // 浅绿色 
#define      BLUE                0x001F       // 蓝 
#define      GBLUE               0x07FF       // 浅蓝 1
#define      LIGHTBLUE           0X7D7C       // 浅蓝 2
#define      BLUE2               0x051F       // 浅蓝 3
#define      GRAYBLUE            0X5458       // 灰蓝 
#define      DARKBLUE            0X01CF       // 深蓝
#define      LGRAY               0XC618       // 浅灰色,窗体背景色
#define      LGRAYBLUE           0XA651       // 浅灰蓝色(中间层颜色)
#define      LBBLUE              0X2B12       // 浅棕蓝色(选择条目的反色)
	    	


/*****************************************************************************
 ** 声明全局函数
 ** (不用修改)
****************************************************************************/
void LCD_Init(void);													                                  // 初始化
void LCD_GUI(void);                                                                                       // 简单的显示界面            
void LCD_DisplayOn(void);													                              // 开显示
void LCD_DisplayOff(void);													                              // 关显示
void LCD_DrawPoint( uint16_t  x,  uint16_t  y,  uint16_t _color);                                            // 画点函数
void LCD_Fill( uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t color);		   				      // 填充单色
void LCD_Line( uint16_t x1,  uint16_t y1,  uint16_t x2,  uint16_t y2,  uint16_t color);					      // 画线
void LCD_Circle( uint16_t Xpos,  uint16_t Ypos,  uint16_t Radius,  uint16_t _color);                          // 画圆
void LCD_String( uint16_t x,  uint16_t y,  char *pFont,  uint8_t size,  uint32_t fColor,  uint32_t bColor);     // 显示任意字符串(支持英文、汉字)
void LCD_Image( uint16_t x,  uint16_t y,  uint16_t width,  uint16_t height, const  uint8_t *image);            // 图片
void LCD_ShowChinese( uint8_t x,  uint8_t y,  uint8_t num,  uint8_t size1,  uint32_t bColor,  uint32_t fColor); // 显示自行转模的文本
void LCD_Cross( uint16_t x,  uint16_t y,  uint16_t len,  uint32_t fColor);                                    // 用于触摸校准：画十字线
void LCD_Color_Fill( u16 sx, u16 sy, u16 ex, u16 ey, u16 *color);

#endif  

