/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

motor_mode_t g_motor_mode_flag = E_MOTOR_MODE_NULL;  //电机模式标志位

/**********************
 *      TYPEDEFS
 **********************/


/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

// 定时器回调函数
void motor_gui_show_motor_data_timer_cb(lv_timer_t * timer)
{
	char buf[128] = {0};
	sprintf(buf, "position: %.2f\nspeed: %.2f\ntorque: %.2f\ntemp: %.2f\n", radians_to_degrees(motor_info.angle), motor_info.speed, motor_info.torque, motor_info.temperature);
    if(g_motor_mode_flag == E_MOTOR_MODE_ZERO)
    {
		lv_label_set_text_fmt(guider_ui.screen_zero_mode_motor_data, buf);
		CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
    }else if(g_motor_mode_flag == E_MOTOR_MODE_POSITION)
    {
		lv_label_set_text_fmt(guider_ui.screen_pos_mode_motor_data, buf);
		CyberGear_Change_Mode(motor_id, master_id, POSITION_MODE);
    }else if(g_motor_mode_flag == E_MOTOR_MODE_SPEED)
    {
		lv_label_set_text_fmt(guider_ui.screen_speed_mode_motor_data, buf);
		CyberGear_Change_Mode(motor_id, master_id, SPEED_MODE);
    }else if(g_motor_mode_flag == E_MOTOR_MODE_CURRENT)
    {
		lv_label_set_text_fmt(guider_ui.screen_current_mode_motor_data, buf);
		CyberGear_Change_Mode(motor_id, master_id, CURRENT_MODE);
    }else if(g_motor_mode_flag == E_MOTOR_MODE_CONTROL)
    {
		lv_label_set_text_fmt(guider_ui.screen_run_ctrl_mode_motor_data, buf);
		CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
    }
}

