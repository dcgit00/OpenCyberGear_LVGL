#include "sys_gui.h"


static lv_coord_t width_scr;
static lv_coord_t height_scr;
static const lv_font_t *font_headline;
static const lv_font_t *font_text;

static lv_obj_t *label_device_id;   //显示设备ID

static lv_obj_t *label_home_headline;
static lv_obj_t *label_zero_headline;
static lv_obj_t *label_position_headline;
static lv_obj_t *label_speed_headline;
static lv_obj_t *label_current_headline;
static lv_obj_t *label_control_headline;

static lv_obj_t *button_mode_zero;     //零点模式
static lv_obj_t *button_mode_position; //位置模式
static lv_obj_t *button_mode_speed;    //速度模式
static lv_obj_t *button_mode_current;  //电流模式
static lv_obj_t *button_mode_control;  //运控模式

typedef enum E_MOTOR_RUN_MODE{
    E_MOTOR_MODE_ZERO = 0x00,
    E_MOTOR_MODE_POSITION = 0x01,
    E_MOTOR_MODE_SPEED = 0x02,
    E_MOTOR_MODE_CURRENT = 0x03,
    E_MOTOR_MODE_CONTROL = 0x04,
    E_MOTOR_MODE_NULL = 0x05
}motor_mode_t;

motor_mode_t g_motor_mode_flag = E_MOTOR_MODE_NULL;  //电机模式标志位

lv_obj_t *screen_home;          //GUI主界面
lv_obj_t *screen_mode_zero;     //零点模式界面
lv_obj_t *screen_mode_position; //位置模式界面
lv_obj_t *screen_mode_speed;    //速度模式界面
lv_obj_t *screen_mode_current;  //电流模式界面
lv_obj_t *screen_mode_control;  //运控模式界面

//实时数据刷新标签
lv_obj_t *label_mode_zero_data;     
lv_obj_t *label_mode_position_data;
lv_obj_t *label_mode_speed_data;   
lv_obj_t *label_mode_current_data;
lv_obj_t *label_mode_control_data; 


void motor_control_system_gui(void)
{
    motor_gui_home_window();
    motor_gui_zero_mode_window();
    motor_gui_position_mode_window();
    motor_gui_speed_mode_window();
    motor_gui_current_mode_window();
    motor_gui_control_mode_window();
    lv_timer_t * timer = lv_timer_create(motor_gui_show_motor_data_timer_cb, 250, NULL); // 每250毫秒触发一次定时器回调函数
    lv_timer_ready(timer); // 启动定时器
}

void motor_gui_home_window(void)
{
    //根据屏幕大小适配不同的字体大小
    //lv_obj_t *screen = lv_scr_act();
    screen_home = lv_scr_act();
    width_scr = lv_obj_get_width(screen_home);
    height_scr = lv_obj_get_height(screen_home);
    //创建样式
    static lv_style_t style_headline;
    //样式初始化
    lv_style_init(&style_headline);
    lv_color_t show_color = lv_color_hex(0xcce8ff);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_headline, LV_OPA_90);
    lv_style_set_bg_color(&style_headline, show_color);
    //设置对象的样式
    lv_obj_add_style(screen_home, &style_headline, LV_STATE_DEFAULT); 

    if(width_scr <= 320)    //屏幕尺寸<=320
    {
        // font_headline = &lv_font_montserrat_18;
        // font_text =  &lv_font_montserrat_14;
        LV_FONT_DECLARE(lv_font_source_han_serif_bold_14);
        LV_FONT_DECLARE(lv_font_source_han_serif_bold_18);
        font_headline = &lv_font_source_han_serif_bold_18;
        font_text = &lv_font_source_han_serif_bold_14;
    }else if(width_scr <= 480)  //屏幕尺寸<=480
    {
        font_headline = &lv_font_montserrat_22;
        font_text =  &lv_font_montserrat_18;
    }else{  //屏幕尺寸  >480
        font_headline = &lv_font_montserrat_26;
        font_text =  &lv_font_montserrat_22;
    }
    
    label_home_headline = lv_label_create(screen_home);
    lv_obj_set_style_text_font(label_home_headline, font_headline, LV_PART_MAIN);
    //lv_label_set_text(label_home_headline, "Motor Control System");
    lv_label_set_text(label_home_headline, "电机控制系统"); 
    lv_style_set_text_color(&style_headline, lv_color_hex(0x007abb));
    lv_obj_align(label_home_headline, LV_ALIGN_TOP_MID, 0, 10);

    label_device_id = lv_label_create(screen_home);
    lv_obj_set_style_text_font(label_device_id, font_text, LV_PART_MAIN);
    lv_label_set_text_fmt(label_device_id, "Device ID : %d", motor_read_id);
	
    lv_obj_align_to(label_device_id ,label_home_headline, LV_ALIGN_CENTER, 0, 20);
    
    motor_gui_home_mode_operate();
}


void motor_gui_home_mode_operate(void)
{
    //创建样式
    static lv_style_t style_mode_button;
    //样式初始化
    lv_style_init(&style_mode_button);
    lv_color_t show_color = lv_color_hex(0xffe14d);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_mode_button, LV_OPA_90);
    lv_style_set_bg_color(&style_mode_button, show_color);
    
    //---------------------零点模式---------------------      
    button_mode_zero = lv_btn_create(lv_scr_act());
    //lv_obj_set_pos(button_mode_zero, width_scr/2, height_scr/2);
    lv_obj_set_size(button_mode_zero, width_scr/2+20, height_scr/8);
    lv_obj_align(button_mode_zero, LV_ALIGN_TOP_MID, 0, 50);
    lv_obj_t *label_zero = lv_label_create(button_mode_zero);
    lv_obj_set_style_text_font(label_zero, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_zero, "Zero Mode");
    lv_label_set_text(label_zero, "零点模式");
    lv_obj_set_align(label_zero, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_zero, &style_mode_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_zero, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_zero, motor_gui_home_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------位置模式---------------------
    button_mode_position = lv_btn_create(lv_scr_act());
    //lv_obj_set_pos(button_mode_position, width_scr/2, height_scr/2);
    lv_obj_set_size(button_mode_position, width_scr/2+20, height_scr/8);
    lv_obj_align(button_mode_position, LV_ALIGN_TOP_MID, 0, 100);    
    lv_obj_t *label_pos = lv_label_create(button_mode_position);
    lv_obj_set_style_text_font(label_pos, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_pos, "Position Mode");
    lv_label_set_text(label_pos, "位置模式");
    lv_obj_set_align(label_pos, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_position, &style_mode_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_position, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_position, motor_gui_home_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------速度模式---------------------
    button_mode_speed = lv_btn_create(lv_scr_act());
    //lv_obj_set_pos(button_mode_speed, width_scr/2, height_scr/2);
    lv_obj_set_size(button_mode_speed, width_scr/2+20, height_scr/8);
    lv_obj_align(button_mode_speed, LV_ALIGN_TOP_MID, 0, 150);    
    lv_obj_t *label_speed = lv_label_create(button_mode_speed);
    lv_obj_set_style_text_font(label_speed, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_speed, "Speed Mode");
    lv_label_set_text(label_speed, "速度模式");
    lv_obj_set_align(label_speed, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_speed, &style_mode_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_speed, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_speed, motor_gui_home_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------电流模式---------------------
    button_mode_current = lv_btn_create(lv_scr_act());
    //lv_obj_set_pos(button_mode_current, width_scr/2, height_scr/2);
    lv_obj_set_size(button_mode_current, width_scr/2+20, height_scr/8);
    lv_obj_align(button_mode_current, LV_ALIGN_TOP_MID, 0, 200);    
    lv_obj_t *label_current = lv_label_create(button_mode_current);
    lv_obj_set_style_text_font(label_current, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_current, "Current Mode");
    lv_label_set_text(label_current, "电流模式");
    lv_obj_set_align(label_current, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_current, &style_mode_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_current, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_current, motor_gui_home_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------运控模式---------------------
    button_mode_control = lv_btn_create(lv_scr_act());
    //lv_obj_set_pos(mode_position, width_scr/2, height_scr/2);
    lv_obj_set_size(button_mode_control, width_scr/2+20, height_scr/8);
    lv_obj_align(button_mode_control, LV_ALIGN_TOP_MID, 0, 250);    
    lv_obj_t *label_control = lv_label_create(button_mode_control);
    lv_obj_set_style_text_font(label_control, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_control, "Control Mode");
    lv_label_set_text(label_control, "运控模式");
    lv_obj_set_align(label_control, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_control, &style_mode_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_control, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_control, motor_gui_home_event_cb, LV_EVENT_CLICKED, NULL);
    
}

void motor_gui_home_event_cb(lv_event_t *param)
{
    lv_obj_t *target = lv_event_get_target(param);
    if (lv_obj_get_screen(target) == screen_home)
    {
        if(target == button_mode_zero)             //零点模式  
        {   
            g_motor_mode_flag = E_MOTOR_MODE_ZERO;
            lv_scr_load_anim(screen_mode_zero, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 0, false);
            lv_scr_load(screen_mode_zero);
			CyberGear_Stop_Run(motor_id, master_id);
			CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
        }else if(target == button_mode_position)   //位置模式
        {
            g_motor_mode_flag = E_MOTOR_MODE_POSITION;
            lv_scr_load_anim(screen_mode_position, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 0, false);
            lv_scr_load(screen_mode_position);
			CyberGear_Stop_Run(motor_id, master_id);
			CyberGear_Change_Mode(motor_id, master_id, POSITION_MODE);
        }else if(target == button_mode_speed)      //速度模式
        {
            g_motor_mode_flag = E_MOTOR_MODE_SPEED;
            lv_scr_load_anim(screen_mode_speed, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 0, false);
            lv_scr_load(screen_mode_speed);
			CyberGear_Stop_Run(motor_id, master_id);
			CyberGear_Change_Mode(motor_id, master_id, SPEED_MODE);
        }else if(target == button_mode_current)    //电流模式
        {
            g_motor_mode_flag = E_MOTOR_MODE_CURRENT;
            lv_scr_load_anim(screen_mode_current, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 0, false);
            lv_scr_load(screen_mode_current);
			CyberGear_Stop_Run(motor_id, master_id);
			CyberGear_Change_Mode(motor_id, master_id, CURRENT_MODE);
        }else if(target == button_mode_control)    //运控模式
        {
            g_motor_mode_flag = E_MOTOR_MODE_CONTROL;
            lv_scr_load_anim(screen_mode_control, LV_SCR_LOAD_ANIM_OVER_LEFT, 300, 0, false);
            lv_scr_load(screen_mode_control);
			CyberGear_Stop_Run(motor_id, master_id);
			CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
        }
    }
}

void motor_gui_zero_mode_window(void)
{
    // 创建 screen_mode_zero
    screen_mode_zero = lv_obj_create(NULL);

    // 添加一个标签到 screen_mode_zero
    label_zero_headline = lv_label_create(screen_mode_zero);
    lv_obj_set_style_text_font(label_zero_headline, font_headline, LV_PART_MAIN);
    //lv_label_set_text(label_zero_headline, "Motor Zero Mode");
    lv_label_set_text(label_zero_headline, "零点模式");
    lv_obj_align(label_zero_headline, LV_ALIGN_TOP_MID, 0, 10);

    //创建样式
    static lv_style_t style_headline;
    //样式初始化
    lv_style_init(&style_headline);
    lv_color_t show_color = lv_color_hex(0xa1ca0e);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_headline, LV_OPA_30);
    lv_style_set_bg_color(&style_headline, show_color);
    //设置对象的样式
    lv_obj_add_style(screen_mode_zero, &style_headline, LV_STATE_DEFAULT); 
    lv_style_set_text_color(&style_headline, lv_color_hex(0xdd4c35));
    //motor_gui_show_motor_data(screen_mode_zero, label_zero_headline, label_mode_zero_data);
    
    // 创建一个容器作为圆角矩形方框
    lv_obj_t *cont = lv_obj_create(screen_mode_zero);
    lv_obj_set_size(cont, 200, 100); // 设置容器大小
    lv_obj_set_style_radius(cont, 10, 0); // 设置圆角半径
    lv_obj_set_style_border_width(cont, 1, 0); // 设置边框宽度为1像素
    lv_obj_set_style_border_color(cont, lv_color_black(), 0); // 设置边框颜色
    lv_obj_set_style_pad_all(cont, 2, 0); // 设置内边距为5像素
    
    lv_obj_set_size(cont, width_scr / 2 + 60, height_scr / 3-30);
    lv_obj_align_to(cont, label_zero_headline, LV_ALIGN_CENTER, 0, 50);
    label_mode_zero_data = lv_label_create(cont);
    lv_obj_set_size(label_mode_zero_data, width_scr / 2 + 15, height_scr / 3-40);
    lv_obj_center(label_mode_zero_data); // 标签居中对齐
    
    char buf[64] = {0};
    sprintf(buf, "Position: %.2f\r\nSpeed: %.2f\r\nTorque: %.2f\r\nTemp: %.2f", 0.0, 0.0, 0.0, 0.0);
    lv_label_set_text(label_mode_zero_data, buf);
    lv_obj_add_event_cb(label_mode_zero_data, motor_gui_show_motor_data_event_cb, LV_EVENT_ALL, NULL);
    
    motor_gui_mode_zero_operate(screen_mode_zero);
}



lv_obj_t *button_mode_zero_home;    //回到主界面按键
lv_obj_t *button_run_to_zero;       //运行到零点按键
lv_obj_t *button_set_zero_pos;      //设置零点按键

void motor_gui_mode_zero_operate(lv_obj_t *screen)
{
    //创建样式
    static lv_style_t style_opt_button;
    //样式初始化
    lv_style_init(&style_opt_button);
    lv_color_t show_color = lv_color_hex(0x1050e7);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_opt_button, LV_OPA_90);
    lv_style_set_bg_color(&style_opt_button, show_color);
    
    //---------------------回到主界面---------------------      
    button_mode_zero_home = lv_btn_create(screen);
    lv_obj_set_size(button_mode_zero_home, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_zero_home, LV_ALIGN_BOTTOM_LEFT, 10, -50);
    lv_obj_t *label_home = lv_label_create(button_mode_zero_home);
    lv_obj_set_style_text_font(label_home, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_home, "Home");
    lv_label_set_text(label_home, "退出");
    lv_obj_set_align(label_home, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_zero_home, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_zero_home, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_zero_home, motor_gui_mode_zero_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------运行到零点---------------------      
    button_run_to_zero = lv_btn_create(screen);
    lv_obj_set_size(button_run_to_zero, width_scr/3-15, height_scr/8);
    lv_obj_align(button_run_to_zero, LV_ALIGN_BOTTOM_MID, 0, -50);
    lv_obj_t *label_run_to_zero = lv_label_create(button_run_to_zero);
    lv_obj_set_style_text_font(label_run_to_zero, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_run_to_zero, "Run Zero");
    lv_label_set_text(label_run_to_zero, "转零");
    lv_obj_set_align(label_run_to_zero, LV_ALIGN_CENTER);
    lv_obj_add_style(button_run_to_zero, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_run_to_zero, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_run_to_zero, motor_gui_mode_zero_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------设置零点---------------------      
    button_set_zero_pos = lv_btn_create(screen);
    lv_obj_set_size(button_set_zero_pos, width_scr/3-15, height_scr/8);
    lv_obj_align(button_set_zero_pos, LV_ALIGN_BOTTOM_RIGHT, -10, -50);
    lv_obj_t *label_set_zero = lv_label_create(button_set_zero_pos);
    lv_obj_set_style_text_font(label_set_zero, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_set_zero, "Set Zero");
    lv_label_set_text(label_set_zero, "置零");
    lv_obj_set_align(label_set_zero, LV_ALIGN_CENTER);
    lv_obj_add_style(button_set_zero_pos, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_set_zero_pos, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_set_zero_pos, motor_gui_mode_zero_event_cb, LV_EVENT_CLICKED, NULL);
}

void motor_gui_mode_zero_event_cb(lv_event_t *param)
{
    lv_obj_t *target = lv_event_get_target(param);
    if (lv_obj_get_screen(target) == screen_mode_zero)
    {
        if(target == button_mode_zero_home)     //回到主界面
        {
            lv_scr_load_anim(screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 300, 0, false);
            lv_scr_load(screen_home);
            g_motor_mode_flag = E_MOTOR_MODE_NULL;
        }else if(target == button_run_to_zero)  //运行到零点
        {
            DBUG_SHOW("Run Zero\r\n");
			CyberGear_Eanble_Run(motor_id, master_id);
			CyberGear_Return_Zero_Position(motor_id, master_id);

        }else if(target == button_set_zero_pos)  //设置零点
        {
            DBUG_SHOW("Set Zero\r\n");
			CyberGear_Eanble_Run(motor_id, master_id);
			CyberGear_Set_Zero_Position(motor_id, master_id);
        }
    }
}

// 全局变量，用于存储滑块的值
static float mode_position_slider_speed_value = 0;
static float mode_position_slider_position_value = 0;

static lv_obj_t * mode_position_slider_speed;
static lv_obj_t * mode_position_slider_position;

static lv_obj_t * mode_position_label_speed;
static lv_obj_t * mode_position_label_position;


void motor_gui_position_mode_window(void)
{
    // 创建 screen_mode_position
    screen_mode_position = lv_obj_create(NULL);

    // 添加一个标签到 screen_mode_position
    label_position_headline = lv_label_create(screen_mode_position);
    lv_obj_set_style_text_font(label_position_headline, font_headline, LV_PART_MAIN);
    //lv_label_set_text(label_position_headline, "Motor Position Mode");
    lv_label_set_text(label_position_headline, "位置模式");
    lv_obj_align(label_position_headline, LV_ALIGN_TOP_MID, 0, 10);

    //创建样式
    static lv_style_t style_headline;
    //样式初始化
    lv_style_init(&style_headline);
    lv_color_t show_color = lv_color_hex(0xa1ca0e);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_headline, LV_OPA_30);
    lv_style_set_bg_color(&style_headline, show_color);
    //设置对象的样式
    lv_obj_add_style(screen_mode_position, &style_headline, LV_STATE_DEFAULT); 
    lv_style_set_text_color(&style_headline, lv_color_hex(0xdd4c35));
    //motor_gui_show_motor_data(screen_mode_position, label_position_headline, label_motor_data[1]);
    
    // 创建一个容器作为圆角矩形方框
    lv_obj_t *cont = lv_obj_create(screen_mode_position);
    lv_obj_set_size(cont, 200, 100); // 设置容器大小
    lv_obj_set_style_radius(cont, 10, 0); // 设置圆角半径
    lv_obj_set_style_border_width(cont, 1, 0); // 设置边框宽度为1像素
    lv_obj_set_style_border_color(cont, lv_color_black(), 0); // 设置边框颜色
    lv_obj_set_style_pad_all(cont, 2, 0); // 设置内边距为5像素
    
    lv_obj_set_size(cont, width_scr / 2 + 60, height_scr / 3-30);
    lv_obj_align_to(cont, label_position_headline, LV_ALIGN_CENTER, 0, 50);
    label_mode_position_data = lv_label_create(cont);
    lv_obj_set_size(label_mode_position_data, width_scr / 2 + 15, height_scr / 3-40);
    lv_obj_center(label_mode_position_data); // 标签居中对齐
    
    char buf[64] = {0};
    sprintf(buf, "Position: %.2f\r\nSpeed: %.2f\r\nTorque: %.2f\r\nTemp: %.2f", 0.0, 0.0, 0.0, 0.0);
    
    lv_label_set_text(label_mode_position_data, buf);
    lv_obj_add_event_cb(label_mode_position_data, motor_gui_show_motor_data_event_cb, LV_EVENT_ALL, NULL);

    motor_gui_mode_position_operate(screen_mode_position);
}


lv_obj_t *button_mode_position_home;    //回到主界面
lv_obj_t *button_mode_position_run;     //运行
lv_obj_t *button_mode_position_stop;    //停止


void motor_gui_mode_position_operate(lv_obj_t *screen)
{
    //创建样式
    static lv_style_t style_opt_button;
    //样式初始化
    lv_style_init(&style_opt_button);
    lv_color_t show_color = lv_color_hex(0x1050e7);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_opt_button, LV_OPA_90);
    lv_style_set_bg_color(&style_opt_button, show_color);
    
    //---------------------回到主界面---------------------      
    button_mode_position_home = lv_btn_create(screen);
    lv_obj_set_size(button_mode_position_home, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_position_home, LV_ALIGN_BOTTOM_LEFT, 10, -50);
    lv_obj_t *label_home = lv_label_create(button_mode_position_home);
    lv_obj_set_style_text_font(label_home, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_home, "Home");
    lv_label_set_text(label_home, "退出");
    lv_obj_set_align(label_home, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_position_home, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_position_home, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_position_home, motor_gui_mode_position_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------运行---------------------      
    button_mode_position_run = lv_btn_create(screen);
    lv_obj_set_size(button_mode_position_run, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_position_run, LV_ALIGN_BOTTOM_MID, 0, -50);
    lv_obj_t *label_run = lv_label_create(button_mode_position_run);
    lv_obj_set_style_text_font(label_run, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_run, "Run");
    lv_label_set_text(label_run, "运行");
    lv_obj_set_align(label_run, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_position_run, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_position_run, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_position_run, motor_gui_mode_position_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------停止---------------------      
    button_mode_position_stop = lv_btn_create(screen);
    lv_obj_set_size(button_mode_position_stop, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_position_stop, LV_ALIGN_BOTTOM_RIGHT, -10, -50);
    lv_obj_t *label_stop = lv_label_create(button_mode_position_stop);
    lv_obj_set_style_text_font(label_stop, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_stop, "Stop");
    lv_label_set_text(label_stop, "停止");
    lv_obj_set_align(label_stop, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_position_stop, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_position_stop, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_position_stop, motor_gui_mode_position_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------速度滑块---------------------  
    mode_position_slider_speed = lv_slider_create(screen);
    lv_obj_set_size(mode_position_slider_speed, 150, 20); // 设置滑块大小
    lv_obj_align(mode_position_slider_speed, LV_ALIGN_CENTER, 0, -30); // 居中对齐
    lv_obj_add_event_cb(mode_position_slider_speed, motor_gui_mode_position_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_position_slider_speed, 0, 3000);   //0/100.0, 3000/100.0
    lv_slider_set_value(mode_position_slider_speed, 0, LV_ANIM_OFF);
    //设置滑块颜色
    lv_obj_set_style_bg_color(mode_position_slider_speed, lv_color_hex(0x0fd6eb), LV_STATE_DEFAULT|LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(mode_position_slider_speed, lv_color_hex(0x0fd6eb), LV_STATE_DEFAULT|LV_PART_KNOB);

    mode_position_label_speed = lv_label_create(screen);
    lv_label_set_text(mode_position_label_speed, "Speed : 0.00"); // 设置标签文本
    lv_obj_align_to(mode_position_label_speed, mode_position_slider_speed, LV_ALIGN_CENTER, 0, 20);
    // 设置滑块的值范围为-30到30，默认值为0
    // 设置标签文本颜色为紫色
    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_style_set_text_color(&label_style, lv_color_hex(0x732bf5));
    lv_obj_add_style(mode_position_label_speed, &label_style, LV_STATE_DEFAULT);
    //--------------------位置滑块---------------------  
    mode_position_slider_position = lv_slider_create(screen);
    lv_obj_set_size(mode_position_slider_position, 150, 20); // 设置滑块大小
    lv_obj_add_event_cb(mode_position_slider_position, motor_gui_mode_position_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_position_slider_position, -72000, 72000);
    lv_slider_set_value(mode_position_slider_position, 0, LV_ANIM_OFF);
    lv_obj_align_to(mode_position_slider_position, mode_position_label_speed, LV_ALIGN_CENTER, 0, 30);

    mode_position_label_position = lv_label_create(screen);
    lv_label_set_text(mode_position_label_position, "Position : 0.00"); // 设置标签文本
    // 设置滑块的值范围为-30到30，默认值为0
    lv_obj_align_to(mode_position_label_position, mode_position_slider_position, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_style(mode_position_label_position, &label_style, LV_STATE_DEFAULT);
}

void motor_gui_mode_position_event_cb(lv_event_t *param)
{
    lv_obj_t *target = lv_event_get_target(param);
    lv_event_code_t code = lv_event_get_code(param);
    if ((lv_obj_get_screen(target) == screen_mode_position) && (code == LV_EVENT_VALUE_CHANGED||code == LV_EVENT_CLICKED))
    {
        if(target == button_mode_position_home)     //回到主界面
        {
			mode_position_slider_speed_value = 0;
			mode_position_slider_position_value = 0;
			lv_label_set_text(mode_position_label_speed, "Speed : 0.00");
			lv_label_set_text(mode_position_label_position, "Position : 0.00");
			lv_slider_set_value(mode_position_slider_speed, 0, LV_ANIM_OFF);
			lv_slider_set_value(mode_position_slider_position, 0, LV_ANIM_OFF);
			g_motor_mode_flag = E_MOTOR_MODE_NULL;
			
			lv_scr_load_anim(screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 300, 0, false);
            lv_scr_load(screen_home);
        }else if(target == button_mode_position_run)      //运行
        {
            DBUG_SHOW("Run\r\n");
			CyberGear_Eanble_Run(motor_id, master_id);
			CyberGear_Position_Control_Mode_Change_Speed(motor_id, master_id, mode_position_slider_speed_value);
			CyberGear_Position_Control_Mode_Change_Position(motor_id, master_id, mode_position_slider_position_value);

        }else if(target == button_mode_position_stop)     //停止
        {
            DBUG_SHOW("Stop\r\n");
			CyberGear_Stop_Run(motor_id, master_id);
        }else if(target == mode_position_slider_speed)
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_position_slider_speed_value = value / 100.0;
            sprintf(buf,  "Speed : %.2f", mode_position_slider_speed_value);
            lv_label_set_text_fmt(mode_position_label_speed, buf);
        }else if(target == mode_position_slider_position)
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_position_slider_position_value = value / 100.0;
            sprintf(buf,  "Position : %.2f", mode_position_slider_position_value);
            lv_label_set_text_fmt(mode_position_label_position,buf);
        }
    }
}

void motor_gui_speed_mode_window(void)
{
    // 创建 screen_mode_speed
    screen_mode_speed = lv_obj_create(NULL);

    // 添加一个标签到 screen_mode_speed
    label_speed_headline = lv_label_create(screen_mode_speed);
    lv_obj_set_style_text_font(label_speed_headline, font_headline, LV_PART_MAIN);
    //lv_label_set_text(label_speed_headline, "Motor Speed Mode");
    lv_label_set_text(label_speed_headline, "速度模式");
    lv_obj_align(label_speed_headline, LV_ALIGN_TOP_MID, 0, 10);

    //创建样式
    static lv_style_t style_headline;
    //样式初始化
    lv_style_init(&style_headline);
    lv_color_t show_color = lv_color_hex(0xa1ca0e);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_headline, LV_OPA_30);
    lv_style_set_bg_color(&style_headline, show_color);
    //设置对象的样式
    lv_obj_add_style(screen_mode_speed, &style_headline, LV_STATE_DEFAULT); 
    lv_style_set_text_color(&style_headline, lv_color_hex(0xdd4c35));
    //motor_gui_show_motor_data(screen_mode_speed, label_speed_headline, label_motor_data[2]);

    // 创建一个容器作为圆角矩形方框
    lv_obj_t *cont = lv_obj_create(screen_mode_speed);
    lv_obj_set_size(cont, 200, 100); // 设置容器大小
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0); // 居中对齐
    lv_obj_set_style_radius(cont, 10, 0); // 设置圆角半径
    lv_obj_set_style_border_width(cont, 1, 0); // 设置边框宽度为1像素
    lv_obj_set_style_border_color(cont, lv_color_black(), 0); // 设置边框颜色
    lv_obj_set_style_pad_all(cont, 2, 0); // 设置内边距为5像素
    
    lv_obj_set_size(cont, width_scr / 2 + 60, height_scr / 3-30);
    lv_obj_align_to(cont, label_speed_headline, LV_ALIGN_CENTER, 0, 50);
    label_mode_speed_data = lv_label_create(cont);
    lv_obj_set_size(label_mode_speed_data, width_scr / 2 + 15, height_scr / 3-40);
    lv_obj_center(label_mode_speed_data); // 标签居中对齐
    
    char buf[64] = {0};
    sprintf(buf, "Position: %.2f\r\nSpeed: %.2f\r\nTorque: %.2f\r\nTemp: %.2f", 0.0, 0.0, 0.0, 0.0);
    
    lv_label_set_text(label_mode_speed_data, buf);
    lv_obj_add_event_cb(label_mode_speed_data, motor_gui_show_motor_data_event_cb, LV_EVENT_ALL, NULL);
    motor_gui_mode_speed_operate(screen_mode_speed);

}

// 全局变量，用于存储滑块的值
static float mode_speed_slider_speed_value = 0;
static float mode_speed_slider_current_value = 0;
static lv_obj_t * mode_speed_slider_speed;
static lv_obj_t * mode_speed_slider_current;
static lv_obj_t * mode_speed_label_speed;
static lv_obj_t * mode_speed_label_current;

lv_obj_t *button_mode_speed_home;    //回到主界面
lv_obj_t *button_mode_speed_run;     //运行
lv_obj_t *button_mode_speed_stop;    //停止

void motor_gui_mode_speed_operate(lv_obj_t *screen)
{
    //创建样式
    static lv_style_t style_opt_button;
    //样式初始化
    lv_style_init(&style_opt_button);
    lv_color_t show_color = lv_color_hex(0x1050e7);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_opt_button, LV_OPA_90);
    lv_style_set_bg_color(&style_opt_button, show_color);
    
    //---------------------回到主界面---------------------      
    button_mode_speed_home = lv_btn_create(screen);
    lv_obj_set_size(button_mode_speed_home, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_speed_home, LV_ALIGN_BOTTOM_LEFT, 10, -50);
    lv_obj_t *label_home = lv_label_create(button_mode_speed_home);
    lv_obj_set_style_text_font(label_home, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_home, "Home");
    lv_label_set_text(label_home, "退出");
    lv_obj_set_align(label_home, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_speed_home, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_speed_home, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_speed_home, motor_gui_mode_speed_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------运行---------------------      
    button_mode_speed_run = lv_btn_create(screen);
    lv_obj_set_size(button_mode_speed_run, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_speed_run, LV_ALIGN_BOTTOM_MID, 0, -50);
    lv_obj_t *label_run = lv_label_create(button_mode_speed_run);
    lv_obj_set_style_text_font(label_run, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_run, "Run");
    lv_label_set_text(label_run, "运行");
    lv_obj_set_align(label_run, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_speed_run, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_speed_run, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_speed_run, motor_gui_mode_speed_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------停止---------------------      
    button_mode_speed_stop = lv_btn_create(screen);
    lv_obj_set_size(button_mode_speed_stop, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_speed_stop, LV_ALIGN_BOTTOM_RIGHT, -10, -50);
    lv_obj_t *label_stop = lv_label_create(button_mode_speed_stop);
    lv_obj_set_style_text_font(label_stop, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_stop, "Stop");
    lv_label_set_text(label_stop, "停止");
    lv_obj_set_align(label_stop, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_speed_stop, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_speed_stop, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_speed_stop, motor_gui_mode_speed_event_cb, LV_EVENT_CLICKED, NULL);

    //--------------------速度滑块---------------------  
    mode_speed_slider_speed = lv_slider_create(screen);
    lv_obj_set_size(mode_speed_slider_speed, 150, 20); // 设置滑块大小
    lv_obj_align(mode_speed_slider_speed, LV_ALIGN_CENTER, 0, -30); // 居中对齐
    lv_obj_add_event_cb(mode_speed_slider_speed, motor_gui_mode_speed_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_speed_slider_speed, -3000, 3000);
    lv_slider_set_value(mode_speed_slider_speed, 0, LV_ANIM_OFF);
    //设置滑块颜色
    lv_obj_set_style_bg_color(mode_speed_slider_speed, lv_color_hex(0x0fd6eb), LV_STATE_DEFAULT|LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(mode_speed_slider_speed, lv_color_hex(0x0fd6eb), LV_STATE_DEFAULT|LV_PART_KNOB);

    mode_speed_label_speed = lv_label_create(screen);
    lv_label_set_text(mode_speed_label_speed, "Speed : 0.00"); // 设置标签文本
    lv_obj_align_to(mode_speed_label_speed, mode_speed_slider_speed, LV_ALIGN_CENTER, 0, 20);
    // 设置滑块的值范围为-30到30，默认值为0
    // 设置标签文本颜色为紫色
    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_style_set_text_color(&label_style, lv_color_hex(0x732bf5));
    lv_obj_add_style(mode_speed_label_speed, &label_style, LV_STATE_DEFAULT);

    
    //--------------------电流滑块---------------------  
    mode_speed_slider_current = lv_slider_create(screen);
    lv_obj_set_size(mode_speed_slider_current, 150, 20); // 设置滑块大小
    lv_obj_add_event_cb(mode_speed_slider_current, motor_gui_mode_speed_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_speed_slider_current, -2300, 2300);
    lv_slider_set_value(mode_speed_slider_current, 0, LV_ANIM_OFF);
    lv_obj_align_to(mode_speed_slider_current, mode_speed_label_speed, LV_ALIGN_CENTER, 0, 30);

    mode_speed_label_current = lv_label_create(screen);
    lv_label_set_text(mode_speed_label_current, "Current : 0.00"); // 设置标签文本
    // 设置滑块的值范围为-30到30，默认值为0
    lv_obj_align_to(mode_speed_label_current, mode_speed_slider_current, LV_ALIGN_CENTER, 0, 20);
    lv_obj_add_style(mode_speed_label_current, &label_style, LV_STATE_DEFAULT);
}

void motor_gui_mode_speed_event_cb(lv_event_t *param)
{
    lv_obj_t *target = lv_event_get_target(param);
    lv_event_code_t code = lv_event_get_code(param);
    if (lv_obj_get_screen(target) == screen_mode_speed && (code == LV_EVENT_VALUE_CHANGED||code==LV_EVENT_CLICKED))
    {
        if(target == button_mode_speed_home)     //回到主界面
        {
			mode_speed_slider_speed_value = 0;
			mode_speed_slider_current_value = 0;
			lv_label_set_text(mode_speed_label_speed, "Speed : 0.00");
			lv_label_set_text(mode_speed_label_current, "Current : 0.00");
			lv_slider_set_value(mode_speed_slider_speed, 0, LV_ANIM_OFF);
			lv_slider_set_value(mode_speed_slider_current, 0, LV_ANIM_OFF);
            
			lv_scr_load_anim(screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 300, 0, false);
            lv_scr_load(screen_home);
			g_motor_mode_flag = E_MOTOR_MODE_NULL;
        }else if(target == button_mode_speed_run)      //运行
        {
            DBUG_SHOW("Run\r\n");
			CyberGear_Eanble_Run(motor_id, master_id);
			CyberGear_Speed_Control_Mode_Change_Max_Current(motor_id, master_id, mode_speed_slider_current_value);
			CyberGear_Speed_Control_Mode_Change_speed(motor_id,master_id, mode_speed_slider_speed_value);

        }else if(target == button_mode_speed_stop)     //停止
        {
            DBUG_SHOW("Stop\r\n");
			CyberGear_Stop_Run(motor_id, master_id);
        }else if(target == mode_speed_slider_speed)
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_speed_slider_speed_value = value / 100.0;
            sprintf(buf, "Speed : %.2f", mode_speed_slider_speed_value);
            lv_label_set_text_fmt(mode_speed_label_speed, buf);
        }else if(target == mode_speed_slider_current)
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_speed_slider_current_value = value / 100.0;
            sprintf(buf, "Current : %.2f", mode_speed_slider_current_value);
            lv_label_set_text_fmt(mode_speed_label_current, buf);
        }
    }
}

// 全局变量，用于存储滑块的值
static float mode_current_slider_current_value = 0;
static lv_obj_t * mode_current_slider_current;
static lv_obj_t * mode_current_label_current;

void motor_gui_current_mode_window(void)
{
    // 创建 screen_mode_current
    screen_mode_current = lv_obj_create(NULL);

    // 添加一个标签到 screen_mode_current
    label_current_headline = lv_label_create(screen_mode_current);
    lv_obj_set_style_text_font(label_current_headline, font_headline, LV_PART_MAIN);
    //lv_label_set_text(label_current_headline, "Motor Current Mode");
    lv_label_set_text(label_current_headline, "电流模式");
    lv_obj_align(label_current_headline, LV_ALIGN_TOP_MID, 0, 10);

    //创建样式
    static lv_style_t style_headline;
    //样式初始化
    lv_style_init(&style_headline);
    lv_color_t show_color = lv_color_hex(0xa1ca0e);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_headline, LV_OPA_30);
    lv_style_set_bg_color(&style_headline, show_color);
    //设置对象的样式
    lv_obj_add_style(screen_mode_current, &style_headline, LV_STATE_DEFAULT); 
    lv_style_set_text_color(&style_headline, lv_color_hex(0xdd4c35));
    //motor_gui_show_motor_data(screen_mode_current, label_current_headline, label_motor_data[3]);

    // 创建一个容器作为圆角矩形方框
    lv_obj_t *cont = lv_obj_create(screen_mode_current);
    lv_obj_set_size(cont, 200, 100); // 设置容器大小
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0); // 居中对齐
    lv_obj_set_style_radius(cont, 10, 0); // 设置圆角半径
    lv_obj_set_style_border_width(cont, 1, 0); // 设置边框宽度为1像素
    lv_obj_set_style_border_color(cont, lv_color_black(), 0); // 设置边框颜色
    lv_obj_set_style_pad_all(cont, 2, 0); // 设置内边距为5像素
    
    lv_obj_set_size(cont, width_scr / 2 + 60, height_scr / 3-30);
    lv_obj_align_to(cont, label_current_headline, LV_ALIGN_CENTER, 0, 50);
    label_mode_current_data = lv_label_create(cont);
    lv_obj_set_size(label_mode_current_data, width_scr / 2 + 15, height_scr / 3-40);
    lv_obj_center(label_mode_current_data); // 标签居中对齐
    
    char buf[64] = {0};
    sprintf(buf, "Position: %.2f\r\nSpeed: %.2f\r\nTorque: %.2f\r\nTemp: %.2f", 0.0, 0.0, 0.0, 0.0);
    
    lv_label_set_text(label_mode_current_data, buf);
    lv_obj_add_event_cb(label_mode_current_data, motor_gui_show_motor_data_event_cb, LV_EVENT_ALL, NULL);

    motor_gui_mode_current_operate(screen_mode_current);
}

lv_obj_t *button_mode_current_home;    //回到主界面
lv_obj_t *button_mode_current_run;     //运行
lv_obj_t *button_mode_current_stop;    //停止

void motor_gui_mode_current_operate(lv_obj_t *screen)
{
    //创建样式
    static lv_style_t style_opt_button;
    //样式初始化
    lv_style_init(&style_opt_button);
    lv_color_t show_color = lv_color_hex(0x1050e7);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_opt_button, LV_OPA_90);
    lv_style_set_bg_color(&style_opt_button, show_color);
    
    //---------------------回到主界面---------------------      
    button_mode_current_home = lv_btn_create(screen);
    lv_obj_set_size(button_mode_current_home, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_current_home, LV_ALIGN_BOTTOM_LEFT, 10, -50);
    lv_obj_t *label_home = lv_label_create(button_mode_current_home);
    lv_obj_set_style_text_font(label_home, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_home, "Home");
    lv_label_set_text(label_home, "退出");
    lv_obj_set_align(label_home, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_current_home, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_current_home, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_current_home, motor_gui_mode_current_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------运行---------------------      
    button_mode_current_run = lv_btn_create(screen);
    lv_obj_set_size(button_mode_current_run, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_current_run, LV_ALIGN_BOTTOM_MID, 0, -50);
    lv_obj_t *label_run = lv_label_create(button_mode_current_run);
    lv_obj_set_style_text_font(label_run, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_run, "Run");
    lv_label_set_text(label_run, "运行");
    lv_obj_set_align(label_run, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_current_run, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_current_run, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_current_run, motor_gui_mode_current_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------停止---------------------      
    button_mode_current_stop = lv_btn_create(screen);
    lv_obj_set_size(button_mode_current_stop, width_scr/3-15, height_scr/8);
    lv_obj_align(button_mode_current_stop, LV_ALIGN_BOTTOM_RIGHT, -10, -50);
    lv_obj_t *label_stop = lv_label_create(button_mode_current_stop);
    lv_obj_set_style_text_font(label_stop, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_stop, "Stop");
    lv_label_set_text(label_stop, "停止");
    lv_obj_set_align(label_stop, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_current_stop, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_current_stop, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_current_stop, motor_gui_mode_current_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------电流滑块---------------------  
    mode_current_slider_current = lv_slider_create(screen);
    lv_obj_set_size(mode_current_slider_current, 150, 20); // 设置滑块大小
    lv_obj_add_event_cb(mode_current_slider_current, motor_gui_mode_current_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_current_slider_current, -2300, 2300);
    lv_slider_set_value(mode_current_slider_current, 0, LV_ANIM_OFF);
    lv_obj_align(mode_current_slider_current, LV_ALIGN_CENTER, 0, -10); // 居中对齐

    mode_current_label_current = lv_label_create(screen);
    lv_label_set_text(mode_current_label_current, "Current : 0.00"); // 设置标签文本
    // 设置滑块的值范围为-30到30，默认值为0
    lv_obj_align_to(mode_current_label_current, mode_current_slider_current, LV_ALIGN_CENTER, 0, 20);
    
    // 设置标签文本颜色为紫色
    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_obj_add_style(mode_current_label_current, &label_style, LV_STATE_DEFAULT);
    lv_style_set_text_color(&label_style, lv_color_hex(0x732bf5));

}

void motor_gui_mode_current_event_cb(lv_event_t *param)
{
    lv_obj_t *target = lv_event_get_target(param);
    lv_event_code_t code = lv_event_get_code(param);
    if (lv_obj_get_screen(target) == screen_mode_current && (code == LV_EVENT_VALUE_CHANGED|| code== LV_EVENT_CLICKED))
    {
        if(target == button_mode_current_home)     //回到主界面
        {
			mode_current_slider_current_value = 0;
			lv_label_set_text(mode_current_label_current, "Current : 0.00");
			lv_slider_set_value(mode_current_slider_current, 0, LV_ANIM_OFF);
			g_motor_mode_flag = E_MOTOR_MODE_NULL;
            lv_scr_load_anim(screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 300, 0, false);
            lv_scr_load(screen_home);
        }else if(target == button_mode_current_run)      //运行
        {
            DBUG_SHOW("Run\r\n");
			CyberGear_Eanble_Run(motor_id, master_id);
			CyberGear_Current_Control_Mode_Change_current(motor_id, master_id, mode_current_slider_current_value);
        }else if(target == button_mode_current_stop)     //停止
        {
            DBUG_SHOW("Stop\r\n");
			CyberGear_Stop_Run(motor_id, master_id);
        }else if(target == mode_current_slider_current)  //电流
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_current_slider_current_value = value / 100.0;
            sprintf(buf, "Current : %.2f", mode_current_slider_current_value);
            lv_label_set_text_fmt(mode_current_label_current, buf);
        }
    }
}

void motor_gui_control_mode_window(void)
{
    // 创建 screen_mode_control
    screen_mode_control = lv_obj_create(NULL);

    // 添加一个标签到 screen_mode_control
    label_control_headline = lv_label_create(screen_mode_control);
    lv_obj_set_style_text_font(label_control_headline, font_headline, LV_PART_MAIN);
    //lv_label_set_text(label_control_headline, "Motor Control Mode");
    lv_label_set_text(label_control_headline, "运控模式");
    lv_obj_align(label_control_headline, LV_ALIGN_TOP_MID, 0, 10);

    //创建样式
    static lv_style_t style_headline;
    //样式初始化
    lv_style_init(&style_headline);
    lv_color_t show_color = lv_color_hex(0xa1ca0e);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_headline, LV_OPA_30);
    lv_style_set_bg_color(&style_headline, show_color);
    //设置对象的样式
    lv_obj_add_style(screen_mode_control, &style_headline, LV_STATE_DEFAULT); 
    lv_style_set_text_color(&style_headline, lv_color_hex(0xdd4c35));
    //motor_gui_show_motor_data(screen_mode_control, label_control_headline,label_motor_data[4]);

    // 创建一个容器作为圆角矩形方框
    lv_obj_t *cont = lv_obj_create(screen_mode_control);
    lv_obj_set_size(cont, 200, 100); // 设置容器大小
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, 0); // 居中对齐
    lv_obj_set_style_radius(cont, 10, 0); // 设置圆角半径
    lv_obj_set_style_border_width(cont, 1, 0); // 设置边框宽度为1像素
    lv_obj_set_style_border_color(cont, lv_color_black(), 0); // 设置边框颜色
    lv_obj_set_style_pad_all(cont, 2, 0); // 设置内边距为5像素
    
    lv_obj_set_size(cont, width_scr / 2 + 60, height_scr / 3-30);
    lv_obj_align_to(cont, label_control_headline, LV_ALIGN_CENTER, 0, 50);
    label_mode_control_data = lv_label_create(cont);
    lv_obj_set_size(label_mode_control_data, width_scr / 2 + 15, height_scr / 3-40);
    lv_obj_center(label_mode_control_data); // 标签居中对齐
    
    char buf[64] = {0};
    sprintf(buf, "Position: %.2f\r\nSpeed: %.2f\r\nTorque: %.2f\r\nTemp: %.2f", 0.0, 0.0, 0.0, 0.0);
    lv_label_set_text(label_mode_control_data, buf);
    lv_obj_add_event_cb(label_mode_control_data, motor_gui_show_motor_data_event_cb, LV_EVENT_ALL, NULL);


    motor_gui_mode_control_operate(screen_mode_control);
}

// 全局变量，用于存储滑块的值
static float mode_control_slider_torque_value = 0;
static float mode_control_slider_speed_value = 0;
static float mode_control_slider_position_value = 0;
static float mode_control_slider_kp_value = 0;
static float mode_control_slider_kd_value = 0;

static lv_obj_t * mode_control_slider_torque;
static lv_obj_t * mode_control_slider_speed;
static lv_obj_t * mode_control_slider_position;
static lv_obj_t * mode_control_slider_kp;
static lv_obj_t * mode_control_slider_kd;

static lv_obj_t * mode_control_label_torque;
static lv_obj_t * mode_control_label_speed;
static lv_obj_t * mode_control_label_position;
static lv_obj_t * mode_control_label_kp;
static lv_obj_t * mode_control_label_kd;

lv_obj_t *button_mode_control_home;    //回到主界面
lv_obj_t *button_mode_control_run;     //运行
lv_obj_t *button_mode_control_stop;    //停止

void motor_gui_mode_control_operate(lv_obj_t *screen)
{
    //创建样式
    static lv_style_t style_opt_button;
    //样式初始化
    lv_style_init(&style_opt_button);
    lv_color_t show_color = lv_color_hex(0x1050e7);
    //设置样式的背景颜色
    lv_style_set_bg_opa( &style_opt_button, LV_OPA_90);
    lv_style_set_bg_color(&style_opt_button, show_color);
    
    //---------------------回到主界面---------------------      
    button_mode_control_home = lv_btn_create(screen);
    lv_obj_set_size(button_mode_control_home, width_scr/3-30, height_scr/8-15);
    lv_obj_align(button_mode_control_home, LV_ALIGN_BOTTOM_LEFT, 10, -5);
    lv_obj_t *label_home = lv_label_create(button_mode_control_home);
    lv_obj_set_style_text_font(label_home, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_home, "Home");
    lv_label_set_text(label_home, "退出");
    lv_obj_set_align(label_home, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_control_home, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_control_home, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_control_home, motor_gui_mode_control_event_cb, LV_EVENT_CLICKED, NULL);
    //---------------------运行---------------------      
    button_mode_control_run = lv_btn_create(screen);
    lv_obj_set_size(button_mode_control_run, width_scr/3-30, height_scr/8-15);
    lv_obj_align(button_mode_control_run, LV_ALIGN_BOTTOM_MID, 0, -5);
    lv_obj_t *label_run = lv_label_create(button_mode_control_run);
    lv_obj_set_style_text_font(label_run, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_run, "Run");
    lv_label_set_text(label_run, "运行");
    lv_obj_set_align(label_run, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_control_run, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_control_run, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_control_run, motor_gui_mode_control_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------停止---------------------      
    button_mode_control_stop = lv_btn_create(screen);
    lv_obj_set_size(button_mode_control_stop, width_scr/3-30, height_scr/8-15);
    lv_obj_align(button_mode_control_stop, LV_ALIGN_BOTTOM_RIGHT, -10, -5);
    lv_obj_t *label_stop = lv_label_create(button_mode_control_stop);
    lv_obj_set_style_text_font(label_stop, font_text, LV_PART_MAIN);
    //lv_label_set_text(label_stop, "Stop");
    lv_label_set_text(label_stop, "停止");
    lv_obj_set_align(label_stop, LV_ALIGN_CENTER);
    lv_obj_add_style(button_mode_control_stop, &style_opt_button, LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(button_mode_control_stop, lv_color_hex(0x7dcb3d), LV_STATE_PRESSED);
    lv_obj_add_event_cb(button_mode_control_stop, motor_gui_mode_control_event_cb, LV_EVENT_CLICKED, NULL);
    //--------------------扭矩滑块---------------------      
    mode_control_slider_torque = lv_slider_create(screen);
    lv_obj_set_size(mode_control_slider_torque, 150, 10); // 设置滑块大小
    lv_obj_add_event_cb(mode_control_slider_torque, motor_gui_mode_control_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_control_slider_torque, -1200, 1200);
    lv_slider_set_value(mode_control_slider_torque, 0, LV_ANIM_OFF);
    lv_obj_align(mode_control_slider_torque, LV_ALIGN_CENTER, 0, -40); // 居中对齐

    mode_control_label_torque = lv_label_create(screen);
    lv_label_set_text(mode_control_label_torque, "Torque : 0.00"); // 设置标签文本
    // 设置滑块的值范围为-30到30，默认值为0
    lv_obj_align_to(mode_control_label_torque, mode_control_slider_torque, LV_ALIGN_CENTER, 0, 18);
    
    // 设置标签文本颜色为紫色
    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_obj_add_style(mode_control_label_torque, &label_style, LV_STATE_DEFAULT);
    lv_style_set_text_color(&label_style, lv_color_hex(0x732bf5));
    //--------------------速度滑块---------------------  
    mode_control_slider_speed = lv_slider_create(screen);
    lv_obj_set_size(mode_control_slider_speed, 150, 10); // 设置滑块大小
    lv_obj_align_to(mode_control_slider_speed, mode_control_label_torque, LV_ALIGN_CENTER, 0, 18);
    lv_obj_add_event_cb(mode_control_slider_speed, motor_gui_mode_control_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_control_slider_speed, -3000, 3000);   //-3000/100.0, 3000/100.0
    lv_slider_set_value(mode_control_slider_speed, 0, LV_ANIM_OFF);
    
    mode_control_label_speed = lv_label_create(screen);
    lv_label_set_text(mode_control_label_speed, "Speed : 0.00"); // 设置标签文本
    lv_obj_align_to(mode_control_label_speed, mode_control_slider_speed, LV_ALIGN_CENTER, 0, 18);
    lv_obj_add_style(mode_control_label_speed, &label_style, LV_STATE_DEFAULT);
    //--------------------位置滑块---------------------  
    mode_control_slider_position = lv_slider_create(screen);
    lv_obj_set_size(mode_control_slider_position, 150, 10); // 设置滑块大小
    lv_obj_add_event_cb(mode_control_slider_position, motor_gui_mode_control_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_control_slider_position, -72000, 72000);
    lv_slider_set_value(mode_control_slider_position, 0, LV_ANIM_OFF);
    lv_obj_align_to(mode_control_slider_position, mode_control_label_speed, LV_ALIGN_CENTER, 0, 18);

    mode_control_label_position = lv_label_create(screen);
    lv_label_set_text(mode_control_label_position, "Position : 0.00"); // 设置标签文本
    // 设置滑块的值范围为-30到30，默认值为0
    lv_obj_align_to(mode_control_label_position, mode_control_slider_position, LV_ALIGN_CENTER, 0, 18);
    lv_obj_add_style(mode_control_label_position, &label_style, LV_STATE_DEFAULT);
    //--------------------Kp滑块---------------------  
    mode_control_slider_kp = lv_slider_create(screen);
    lv_obj_set_size(mode_control_slider_kp, 150, 10); // 设置滑块大小
    lv_obj_add_event_cb(mode_control_slider_kp, motor_gui_mode_control_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_control_slider_kp, 0, 5000);
    lv_slider_set_value(mode_control_slider_kp, 0, LV_ANIM_OFF);
    lv_obj_align_to(mode_control_slider_kp, mode_control_label_position, LV_ALIGN_CENTER, 0, 18);

    mode_control_label_kp = lv_label_create(screen);
    lv_label_set_text(mode_control_label_kp, "Kp : 0.00"); // 设置标签文本
    // 设置滑块的值范围为-30到30，默认值为0
    lv_obj_align_to(mode_control_label_kp, mode_control_slider_kp, LV_ALIGN_CENTER, 0, 18);
    lv_obj_add_style(mode_control_label_kp, &label_style, LV_STATE_DEFAULT);
    //--------------------Kd滑块---------------------  
    mode_control_slider_kd = lv_slider_create(screen);
    lv_obj_set_size(mode_control_slider_kd, 150, 10); // 设置滑块大小
    lv_obj_add_event_cb(mode_control_slider_kd, motor_gui_mode_control_event_cb, LV_EVENT_VALUE_CHANGED, NULL); // 为滑块添加事件处理函数
    lv_slider_set_range(mode_control_slider_kd, 0, 500);
    lv_slider_set_value(mode_control_slider_kd, 0, LV_ANIM_OFF);
    lv_obj_align_to(mode_control_slider_kd, mode_control_label_kp, LV_ALIGN_CENTER, 0, 18);

    mode_control_label_kd = lv_label_create(screen);
    lv_label_set_text(mode_control_label_kd, "Kd : 0.00"); // 设置标签文本
    // 设置滑块的值范围为-30到30，默认值为0
    lv_obj_align_to(mode_control_label_kd, mode_control_slider_kd, LV_ALIGN_CENTER, 0, 18);
    lv_obj_add_style(mode_control_label_kd, &label_style, LV_STATE_DEFAULT);
}

void motor_gui_mode_control_event_cb(lv_event_t *param)
{
    lv_obj_t *target = lv_event_get_target(param);
    lv_event_code_t code = lv_event_get_code(param);
    if (lv_obj_get_screen(target) == screen_mode_control && (code == LV_EVENT_VALUE_CHANGED || code == LV_EVENT_CLICKED))
    {
        if(target == button_mode_control_home)          //回到主界面
        {
			mode_control_slider_torque_value = 0;
			mode_control_slider_position_value = 0;
			mode_control_slider_speed_value = 0;
			mode_control_slider_kp_value = 0;
			mode_control_slider_kd_value = 0;
            lv_label_set_text(mode_control_label_torque, "Torque : 0.00"); // 设置标签文本
			lv_label_set_text(mode_control_label_speed, "Speed : 0.00");
			lv_label_set_text(mode_control_label_position, "Position : 0.00");
			lv_label_set_text(mode_control_label_kp, "Kp : 0.00");
			lv_label_set_text(mode_control_label_kd, "Kd : 0.00");
			lv_slider_set_value(mode_control_slider_torque, 0, LV_ANIM_OFF);
			lv_slider_set_value(mode_control_slider_speed, 0, LV_ANIM_OFF);
			lv_slider_set_value(mode_control_slider_position, 0, LV_ANIM_OFF);
			lv_slider_set_value(mode_control_slider_kp, 0, LV_ANIM_OFF);
			lv_slider_set_value(mode_control_slider_kd, 0, LV_ANIM_OFF);
			g_motor_mode_flag = E_MOTOR_MODE_NULL;
			lv_scr_load_anim(screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 300, 0, false);
            lv_scr_load(screen_home);
        }else if(target == button_mode_control_run)      //运行
        {
            DBUG_SHOW("Run\r\n");
			CyberGear_Eanble_Run(motor_id, master_id);
			CyberGear_Control_Mode(motor_id, master_id, mode_control_slider_torque_value, mode_control_slider_position_value, mode_control_slider_speed_value, mode_control_slider_kp_value, mode_control_slider_kd_value);
        }else if(target == button_mode_control_stop)     //停止
        {
            DBUG_SHOW("Stop\r\n");
			CyberGear_Stop_Run(motor_id, master_id);

        }else if(target == mode_control_slider_torque)  //扭矩
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_control_slider_torque_value = value / 100.00;
            sprintf(buf, "Torque : %.2f", mode_control_slider_torque_value);
            lv_label_set_text_fmt(mode_control_label_torque, buf);
        }else if(target == mode_control_slider_speed)  //速度
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_control_slider_speed_value = value / 100.00;
            sprintf(buf, "Speed : %.2f", mode_control_slider_speed_value);
            lv_label_set_text_fmt(mode_control_label_speed, buf);
        }else if(target == mode_control_slider_position)  //位置
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_control_slider_position_value = value / 100.00;
            sprintf(buf, "Position : %.2f", mode_control_slider_position_value);
            lv_label_set_text_fmt(mode_control_label_position, buf);
        }else if(target == mode_control_slider_kp)  //kp
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_control_slider_kp_value = value / 100.00;
            sprintf(buf, "Kp : %.2f", mode_control_slider_kp_value);
            lv_label_set_text_fmt(mode_control_label_kp, buf);
        }else if(target == mode_control_slider_kd)  //kd
        {
            int32_t value = lv_slider_get_value(target);
            char buf[32] = {0};
            mode_control_slider_kd_value = value / 100.00;
            sprintf(buf, "Kd : %.2f", mode_control_slider_kd_value);
            lv_label_set_text_fmt(mode_control_label_kd, buf);        
        }
    }
}

void motor_gui_show_motor_data_event_cb(lv_event_t * param)
{
    lv_event_code_t code = lv_event_get_code(param);
    if (code == LV_EVENT_DATA_REFRESH) 
    {
        // 更新标签文本内容(电机数据)
        char buf[64] = {0};
        //sprintf(buf, "Position: %.2f\nSpeed: %.2f\nTorque: %.2f\nTemp: %.2f", rand() % 100+1.1, rand() % 255+1.1, rand() % 2+1.1, rand() % 10+1.1);
		sprintf(buf, "Position: %.2f\nSpeed: %.2f\nTorque: %.2f\nTemp: %.2f", radians_to_degrees(motor_info.angle), motor_info.speed, motor_info.torque, motor_info.temperature);
        if(g_motor_mode_flag == E_MOTOR_MODE_ZERO)
        {
            lv_label_set_text_fmt(label_mode_zero_data, buf);
        }else if(g_motor_mode_flag == E_MOTOR_MODE_POSITION)
        {
            lv_label_set_text_fmt(label_mode_position_data, buf);
        }else if(g_motor_mode_flag == E_MOTOR_MODE_SPEED)
        {
            lv_label_set_text_fmt(label_mode_speed_data, buf);
        }else if(g_motor_mode_flag == E_MOTOR_MODE_CURRENT)
        {
            lv_label_set_text_fmt(label_mode_current_data, buf);
        }else if(g_motor_mode_flag == E_MOTOR_MODE_CONTROL)
        {
            lv_label_set_text_fmt(label_mode_control_data, buf);
        }
    }
}

// 定时器回调函数
void motor_gui_show_motor_data_timer_cb(lv_timer_t * timer)
{
    if(g_motor_mode_flag == E_MOTOR_MODE_ZERO)
    {
         // 触发自定义事件
        lv_event_send(label_mode_zero_data, LV_EVENT_DATA_REFRESH, NULL);
        //DBUG_SHOW("E_MOTOR_MODE_ZERO\r\n");
		CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
    }else if(g_motor_mode_flag == E_MOTOR_MODE_POSITION)
    {
        lv_event_send(label_mode_position_data, LV_EVENT_DATA_REFRESH, NULL);
        //DBUG_SHOW("E_MOTOR_MODE_POSITION\r\n");
		CyberGear_Change_Mode(motor_id, master_id, POSITION_MODE);
    }else if(g_motor_mode_flag == E_MOTOR_MODE_SPEED)
    {
        lv_event_send(label_mode_speed_data, LV_EVENT_DATA_REFRESH, NULL);
		CyberGear_Change_Mode(motor_id, master_id, SPEED_MODE);
        //DBUG_SHOW("E_MOTOR_MODE_SPEED\r\n");
    }else if(g_motor_mode_flag == E_MOTOR_MODE_CURRENT)
    {
        lv_event_send(label_mode_current_data, LV_EVENT_DATA_REFRESH, NULL);
        //DBUG_SHOW("E_MOTOR_MODE_CURRENT\r\n");
		CyberGear_Change_Mode(motor_id, master_id, CURRENT_MODE);
    }else if(g_motor_mode_flag == E_MOTOR_MODE_CONTROL)
    {
        lv_event_send(label_mode_control_data, LV_EVENT_DATA_REFRESH, NULL);
        //DBUG_SHOW("E_MOTOR_MODE_CONTROL\r\n");
		CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
    }
}


