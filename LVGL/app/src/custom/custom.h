/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CyberGear.h"
#include "gui_guider.h"

#define LV_EVENT_DATA_REFRESH 0x01 // 自定义事件，用于数据刷新
 
extern CyberGear_FeedBack_t motor_info;
typedef enum E_MOTOR_RUN_MODE{
    E_MOTOR_MODE_ZERO = 0x00,
    E_MOTOR_MODE_POSITION = 0x01,
    E_MOTOR_MODE_SPEED = 0x02,
    E_MOTOR_MODE_CURRENT = 0x03,
    E_MOTOR_MODE_CONTROL = 0x04,
    E_MOTOR_MODE_NULL = 0x05
}motor_mode_t;

extern motor_mode_t g_motor_mode_flag;
void motor_gui_show_motor_data_timer_cb(lv_timer_t * timer);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
