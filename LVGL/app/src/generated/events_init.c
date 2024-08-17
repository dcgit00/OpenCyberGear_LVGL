/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


#include <stdio.h>
float run_ctrl_mode_slide_torque_val = 0;
extern lv_ui guider_ui;
float run_ctrl_mode_slide_speed_val = 0;
extern lv_ui guider_ui;
float run_ctrl_mode_slide_pos_val = 0;
extern lv_ui guider_ui;
float run_ctrl_mode_slide_kp_val = 0;
extern lv_ui guider_ui;
float run_ctrl_mode_slide_kd_val = 0;
extern lv_ui guider_ui;
float pos_mode_slide_pos_val = 0;
extern lv_ui guider_ui;
float pos_mode_slide_speed_val = 0;
extern lv_ui guider_ui;
float current_mode_slide_current = 0;
extern lv_ui guider_ui;
float speed_mode_slider_current_val = 0;
extern lv_ui guider_ui;
float speed_mode_slider_speed_val = 0;
extern lv_ui guider_ui;
static void screen_home_btn_zero_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_zero_mode, guider_ui.screen_zero_mode_del, &guider_ui.screen_home_del, setup_scr_screen_zero_mode, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_ZERO;
		break;
	}
	default:
		break;
	}
}
static void screen_home_btn_speed_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_speed_mode, guider_ui.screen_speed_mode_del, &guider_ui.screen_home_del, setup_scr_screen_speed_mode, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_SPEED;
		break;
	}
	default:
		break;
	}
}
static void screen_home_btn_current_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_current_mode, guider_ui.screen_current_mode_del, &guider_ui.screen_home_del, setup_scr_screen_current_mode, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_CURRENT;
		break;
	}
	default:
		break;
	}
}
static void screen_home_btn_pos_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_pos_mode, guider_ui.screen_pos_mode_del, &guider_ui.screen_home_del, setup_scr_screen_pos_mode, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_POSITION;
		break;
	}
	default:
		break;
	}
}
static void screen_home_btn_run_ctrl_mode_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_run_ctrl_mode, guider_ui.screen_run_ctrl_mode_del, &guider_ui.screen_home_del, setup_scr_screen_run_ctrl_mode, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_CONTROL;
		break;
	}
	default:
		break;
	}
}
void events_init_screen_home(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_home_btn_zero_mode, screen_home_btn_zero_mode_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_home_btn_speed_mode, screen_home_btn_speed_mode_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_home_btn_current_mode, screen_home_btn_current_mode_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_home_btn_pos_mode, screen_home_btn_pos_mode_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_home_btn_run_ctrl_mode, screen_home_btn_run_ctrl_mode_event_handler, LV_EVENT_ALL, ui);
}
static void screen_run_ctrl_mode_btn_run_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Eanble_Run(motor_id, master_id);
		CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
		CyberGear_Control_Mode(motor_id, master_id, run_ctrl_mode_slide_torque_val, run_ctrl_mode_slide_pos_val, run_ctrl_mode_slide_speed_val, run_ctrl_mode_slide_kp_val, run_ctrl_mode_slide_kd_val);
		DBUG_SHOW("run ctrl mode press run\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_run_ctrl_mode_btn_stop_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Stop_Run(motor_id, master_id);
		DBUG_SHOW("run ctrl mode press stop\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_run_ctrl_mode_btn_back_home_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_run_ctrl_mode_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_NULL;
		CyberGear_Stop_Run(motor_id, master_id);
		run_ctrl_mode_slide_torque_val = 0;
		run_ctrl_mode_slide_speed_val = 0;
		run_ctrl_mode_slide_pos_val = 0;
		run_ctrl_mode_slide_kp_val = 0;
		run_ctrl_mode_slide_kd_val = 0;
		DBUG_SHOW("run ctrl mode press back home\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_run_ctrl_mode_slide_torque_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		run_ctrl_mode_slide_torque_val = value / 100.0;
		sprintf(buf,  "Torque : %.2f", run_ctrl_mode_slide_torque_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_run_ctrl_mode_label_torque, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_run_ctrl_mode_slide_speed_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		run_ctrl_mode_slide_speed_val = value / 100.0;
		sprintf(buf,  "Speed : %.2f", run_ctrl_mode_slide_speed_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_run_ctrl_mode_label_speed, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_run_ctrl_mode_slide_pos_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		run_ctrl_mode_slide_pos_val = value / 100.0;
		sprintf(buf,  "Position : %.2f", run_ctrl_mode_slide_pos_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_run_ctrl_mode_label_pos, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_run_ctrl_mode_slide_kp_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		run_ctrl_mode_slide_kp_val = value / 100.0;
		sprintf(buf,  "Kp : %.2f", run_ctrl_mode_slide_kp_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_run_ctrl_mode_label_kp, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_run_ctrl_mode_slide_kd_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		run_ctrl_mode_slide_kd_val = value / 100.0;
		sprintf(buf,  "Kd : %.2f", run_ctrl_mode_slide_kd_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_run_ctrl_mode_label_kd, buf);
		break;
	}
	default:
		break;
	}
}
void events_init_screen_run_ctrl_mode(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_btn_run, screen_run_ctrl_mode_btn_run_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_btn_stop, screen_run_ctrl_mode_btn_stop_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_btn_back_home, screen_run_ctrl_mode_btn_back_home_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_slide_torque, screen_run_ctrl_mode_slide_torque_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_slide_speed, screen_run_ctrl_mode_slide_speed_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_slide_pos, screen_run_ctrl_mode_slide_pos_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_slide_kp, screen_run_ctrl_mode_slide_kp_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_run_ctrl_mode_slide_kd, screen_run_ctrl_mode_slide_kd_event_handler, LV_EVENT_ALL, ui);
}
static void screen_pos_mode_slider_position_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		pos_mode_slide_pos_val = value / 100.0;
		sprintf(buf,  "Position : %.2f", pos_mode_slide_pos_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_pos_mode_label_position, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_pos_mode_slider_speed_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		pos_mode_slide_speed_val = value / 100.0;
		sprintf(buf,  "Speed : %.2f", pos_mode_slide_speed_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_pos_mode_label_speed, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_pos_mode_back_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_pos_mode_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_NULL;
		CyberGear_Stop_Run(motor_id, master_id);
		pos_mode_slide_pos_val = 0;
		pos_mode_slide_speed_val = 0;
		DBUG_SHOW("pos mode press back home\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_pos_mode_stop_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Stop_Run(motor_id, master_id);
		DBUG_SHOW("pos mode press stop\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_pos_mode_run_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	
	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Eanble_Run(motor_id, master_id);
		CyberGear_Change_Mode(motor_id, master_id, POSITION_MODE);
		CyberGear_Position_Control_Mode_Change_Speed(motor_id, master_id, pos_mode_slide_speed_val);
		CyberGear_Position_Control_Mode_Change_Position(motor_id, master_id, pos_mode_slide_pos_val);
		DBUG_SHOW("pos mode press run\r\n");
		break;
	}
	default:
		break;
	}
}
void events_init_screen_pos_mode(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_pos_mode_slider_position, screen_pos_mode_slider_position_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_pos_mode_slider_speed, screen_pos_mode_slider_speed_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_pos_mode_back, screen_pos_mode_back_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_pos_mode_stop, screen_pos_mode_stop_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_pos_mode_run, screen_pos_mode_run_event_handler, LV_EVENT_ALL, ui);
}
static void screen_current_mode_slider_current_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		current_mode_slide_current = value / 100.0;
		sprintf(buf,  "Current : %.2f", current_mode_slide_current);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_current_mode_label_current, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_current_mode_btn_back_home_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_current_mode_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_NULL;
		CyberGear_Stop_Run(motor_id, master_id);
		current_mode_slide_current = 0;
		DBUG_SHOW("current mode press back home\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_current_mode_btn_stop_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Stop_Run(motor_id, master_id);
		DBUG_SHOW("current mode press stop\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_current_mode_btn_run_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Eanble_Run(motor_id, master_id);
		CyberGear_Change_Mode(motor_id, master_id, CURRENT_MODE);
		CyberGear_Current_Control_Mode_Change_current(motor_id, master_id, current_mode_slide_current);
		DBUG_SHOW("current mode press run\r\n");
		break;
	}
	default:
		break;
	}
}
void events_init_screen_current_mode(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_current_mode_slider_current, screen_current_mode_slider_current_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_current_mode_btn_back_home, screen_current_mode_btn_back_home_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_current_mode_btn_stop, screen_current_mode_btn_stop_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_current_mode_btn_run, screen_current_mode_btn_run_event_handler, LV_EVENT_ALL, ui);
}
static void screen_speed_mode_btn_back_home_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_speed_mode_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_NULL;
		CyberGear_Stop_Run(motor_id, master_id);
		speed_mode_slider_current_val = 0;
		speed_mode_slider_speed_val = 0;
		DBUG_SHOW("speed mode press back home\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_speed_mode_btn_stop_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Stop_Run(motor_id, master_id);
		DBUG_SHOW("speed mode press stop\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_speed_mode_btn_run_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		CyberGear_Eanble_Run(motor_id, master_id);
		CyberGear_Change_Mode(motor_id, master_id, SPEED_MODE);
		CyberGear_Speed_Control_Mode_Change_Max_Current(motor_id, master_id, speed_mode_slider_current_val);
		CyberGear_Speed_Control_Mode_Change_speed(motor_id,master_id, speed_mode_slider_speed_val);
		DBUG_SHOW("speed mode press run\r\n");
		break;
	}
	default:
		break;
	}
}
static void screen_speed_mode_slider_current_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		speed_mode_slider_current_val = value / 100.0;
		sprintf(buf,  "Current : %.2f", speed_mode_slider_current_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_speed_mode_label_current, buf);
		break;
	}
	default:
		break;
	}
}
static void screen_speed_mode_slider_speed_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t *target = lv_event_get_target(e);
		int value = lv_slider_get_value(target);
		char buf[64] = {0};
		speed_mode_slider_speed_val = value / 100.0;
		sprintf(buf,  "Speed : %.2f", speed_mode_slider_speed_val);
		DBUG_SHOW("buf:%s\r\n", buf);
		lv_label_set_text(guider_ui.screen_speed_mode_label_speed, buf);
		break;
	}
	default:
		break;
	}
}
void events_init_screen_speed_mode(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_speed_mode_btn_back_home, screen_speed_mode_btn_back_home_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_speed_mode_btn_stop, screen_speed_mode_btn_stop_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_speed_mode_btn_run, screen_speed_mode_btn_run_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_speed_mode_slider_current, screen_speed_mode_slider_current_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_speed_mode_slider_speed, screen_speed_mode_slider_speed_event_handler, LV_EVENT_ALL, ui);
}
static void screen_zero_mode_btn_set_zero_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		DBUG_SHOW("zero mode press set zero\r\n");
		CyberGear_Eanble_Run(motor_id, master_id);
		CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
		CyberGear_Set_Zero_Position(motor_id, master_id);
		break;
	}
	default:
		break;
	}
}
static void screen_zero_mode_btn_run_zero_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		DBUG_SHOW("zero mode press run zero\r\n");
		CyberGear_Eanble_Run(motor_id, master_id);
		CyberGear_Change_Mode(motor_id, master_id, RUN_CNTL_MODE);
		CyberGear_Return_Zero_Position(motor_id, master_id);
		break;
	}
	default:
		break;
	}
}
static void screen_zero_mode_btn_back_home_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_zero_mode_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, false, true);
		g_motor_mode_flag = E_MOTOR_MODE_NULL;
		CyberGear_Stop_Run(motor_id, master_id);
		DBUG_SHOW("zero mode press back home\r\n");
		break;
	}
	default:
		break;
	}
}
void events_init_screen_zero_mode(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_zero_mode_btn_set_zero, screen_zero_mode_btn_set_zero_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_zero_mode_btn_run_zero, screen_zero_mode_btn_run_zero_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_zero_mode_btn_back_home, screen_zero_mode_btn_back_home_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{
	lv_timer_t * timer = lv_timer_create(motor_gui_show_motor_data_timer_cb, 250, NULL); // 每250毫秒触发一次定时器回调函数
    lv_timer_ready(timer); // 启动定时器
}
