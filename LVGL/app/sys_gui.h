#ifndef __MOTOR_SYSTEM_H
#define __MOTOR_SYSTEM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#include "lvgl.h"

#include "CyberGear.h"


#define LV_EVENT_DATA_REFRESH 0x01 // 自定义事件，用于数据刷新


void motor_control_system_gui(void);
void motor_gui_home_window(void);
void motor_gui_home_mode_operate(void);
void motor_gui_home_event_cb(lv_event_t *param);
void motor_gui_zero_mode_window(void);
void motor_gui_mode_zero_operate(lv_obj_t *screen);
void motor_gui_mode_zero_event_cb(lv_event_t *param);
void motor_gui_position_mode_window(void);
void motor_gui_mode_position_operate(lv_obj_t *screen);
void motor_gui_mode_position_event_cb(lv_event_t *param);
void motor_gui_speed_mode_window(void);
void motor_gui_mode_speed_operate(lv_obj_t *screen);
void motor_gui_mode_speed_event_cb(lv_event_t *param);
void motor_gui_current_mode_window(void);
void motor_gui_mode_current_operate(lv_obj_t *screen);
void motor_gui_mode_current_event_cb(lv_event_t *param);
void motor_gui_control_mode_window(void);
void motor_gui_mode_control_operate(lv_obj_t *screen);
void motor_gui_mode_control_event_cb(lv_event_t *param);
void motor_gui_show_motor_data_event_cb(lv_event_t * param);
void motor_gui_show_motor_data_timer_cb(lv_timer_t * timer);


#endif
