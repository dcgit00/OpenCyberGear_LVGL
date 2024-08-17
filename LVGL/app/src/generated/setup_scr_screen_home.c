/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_home(lv_ui *ui)
{
	//Write codes screen_home
	ui->screen_home = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_home, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_home, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_cont_1
	ui->screen_home_cont_1 = lv_obj_create(ui->screen_home);
	lv_obj_set_pos(ui->screen_home_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_home_cont_1, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_home_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_home_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_home_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_home_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_home_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_home_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_home_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_home_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_home_cont_1, lv_color_hex(0x95ffef), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_home_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_home_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_home_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_home_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_home_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_home_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_btn_zero_mode
	ui->screen_home_btn_zero_mode = lv_btn_create(ui->screen_home_cont_1);
	ui->screen_home_btn_zero_mode_label = lv_label_create(ui->screen_home_btn_zero_mode);
	lv_label_set_text(ui->screen_home_btn_zero_mode_label, "零点模式");
	lv_label_set_long_mode(ui->screen_home_btn_zero_mode_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_home_btn_zero_mode_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_home_btn_zero_mode, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_home_btn_zero_mode_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_home_btn_zero_mode, 46, 265);
	lv_obj_set_size(ui->screen_home_btn_zero_mode, 145, 40);

	//Write style for screen_home_btn_zero_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_home_btn_zero_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_home_btn_zero_mode, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_zero_mode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_home_btn_zero_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_home_btn_zero_mode, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_home_btn_zero_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_home_btn_zero_mode, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_home_btn_zero_mode, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_home_btn_zero_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_home_btn_zero_mode, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_btn_speed_mode
	ui->screen_home_btn_speed_mode = lv_btn_create(ui->screen_home_cont_1);
	ui->screen_home_btn_speed_mode_label = lv_label_create(ui->screen_home_btn_speed_mode);
	lv_label_set_text(ui->screen_home_btn_speed_mode_label, "速度模式");
	lv_label_set_long_mode(ui->screen_home_btn_speed_mode_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_home_btn_speed_mode_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_home_btn_speed_mode, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_home_btn_speed_mode_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_home_btn_speed_mode, 46, 215);
	lv_obj_set_size(ui->screen_home_btn_speed_mode, 145, 40);

	//Write style for screen_home_btn_speed_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_home_btn_speed_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_home_btn_speed_mode, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_speed_mode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_home_btn_speed_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_home_btn_speed_mode, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_home_btn_speed_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_home_btn_speed_mode, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_home_btn_speed_mode, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_home_btn_speed_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_home_btn_speed_mode, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_btn_current_mode
	ui->screen_home_btn_current_mode = lv_btn_create(ui->screen_home_cont_1);
	ui->screen_home_btn_current_mode_label = lv_label_create(ui->screen_home_btn_current_mode);
	lv_label_set_text(ui->screen_home_btn_current_mode_label, "电流模式");
	lv_label_set_long_mode(ui->screen_home_btn_current_mode_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_home_btn_current_mode_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_home_btn_current_mode, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_home_btn_current_mode_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_home_btn_current_mode, 46, 165);
	lv_obj_set_size(ui->screen_home_btn_current_mode, 145, 40);

	//Write style for screen_home_btn_current_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_home_btn_current_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_home_btn_current_mode, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_current_mode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_home_btn_current_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_home_btn_current_mode, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_home_btn_current_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_home_btn_current_mode, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_home_btn_current_mode, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_home_btn_current_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_home_btn_current_mode, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_btn_pos_mode
	ui->screen_home_btn_pos_mode = lv_btn_create(ui->screen_home_cont_1);
	ui->screen_home_btn_pos_mode_label = lv_label_create(ui->screen_home_btn_pos_mode);
	lv_label_set_text(ui->screen_home_btn_pos_mode_label, "位置模式");
	lv_label_set_long_mode(ui->screen_home_btn_pos_mode_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_home_btn_pos_mode_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_home_btn_pos_mode, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_home_btn_pos_mode_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_home_btn_pos_mode, 46, 115);
	lv_obj_set_size(ui->screen_home_btn_pos_mode, 145, 40);

	//Write style for screen_home_btn_pos_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_home_btn_pos_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_home_btn_pos_mode, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_pos_mode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_home_btn_pos_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_home_btn_pos_mode, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_home_btn_pos_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_home_btn_pos_mode, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_home_btn_pos_mode, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_home_btn_pos_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_home_btn_pos_mode, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_btn_run_ctrl_mode
	ui->screen_home_btn_run_ctrl_mode = lv_btn_create(ui->screen_home_cont_1);
	ui->screen_home_btn_run_ctrl_mode_label = lv_label_create(ui->screen_home_btn_run_ctrl_mode);
	lv_label_set_text(ui->screen_home_btn_run_ctrl_mode_label, "运控模式");
	lv_label_set_long_mode(ui->screen_home_btn_run_ctrl_mode_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_home_btn_run_ctrl_mode_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_home_btn_run_ctrl_mode, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_home_btn_run_ctrl_mode_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_home_btn_run_ctrl_mode, 46, 66);
	lv_obj_set_size(ui->screen_home_btn_run_ctrl_mode, 145, 40);

	//Write style for screen_home_btn_run_ctrl_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_home_btn_run_ctrl_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_home_btn_run_ctrl_mode, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_home_btn_run_ctrl_mode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_home_btn_run_ctrl_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_home_btn_run_ctrl_mode, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_home_btn_run_ctrl_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_home_btn_run_ctrl_mode, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_home_btn_run_ctrl_mode, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_home_btn_run_ctrl_mode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_home_btn_run_ctrl_mode, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_home_device_id
	ui->screen_home_device_id = lv_spangroup_create(ui->screen_home_cont_1);
	lv_spangroup_set_align(ui->screen_home_device_id, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_home_device_id, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_home_device_id, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_home_device_id_span;
	screen_home_device_id_span = lv_spangroup_new_span(ui->screen_home_device_id);
	//lv_span_set_text(screen_home_device_id_span, "CAN ID : 0");
	extern uint8_t motor_id;
	char buf[16] = {0};
	sprintf(buf,"CAN ID : %d", motor_id);
	lv_span_set_text(screen_home_device_id_span, buf);
	lv_style_set_text_color(&screen_home_device_id_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&screen_home_device_id_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_home_device_id_span->style, &lv_font_montserratMedium_12);
	lv_obj_set_pos(ui->screen_home_device_id, 89, 45);
	lv_obj_set_size(ui->screen_home_device_id, 80, 12);
	
	//Write style state: LV_STATE_DEFAULT for &style_screen_home_device_id_main_main_default
	static lv_style_t style_screen_home_device_id_main_main_default;
	ui_init_style(&style_screen_home_device_id_main_main_default);
	
	lv_style_set_border_width(&style_screen_home_device_id_main_main_default, 0);
	lv_style_set_radius(&style_screen_home_device_id_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_home_device_id_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_home_device_id_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_home_device_id_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_home_device_id_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_home_device_id_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_home_device_id_main_main_default, 0);
	lv_obj_add_style(ui->screen_home_device_id, &style_screen_home_device_id_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_home_device_id);

	//Write codes screen_home_lable_sys_name
	ui->screen_home_lable_sys_name = lv_label_create(ui->screen_home_cont_1);
	lv_label_set_text(ui->screen_home_lable_sys_name, "电机控制系统");
	lv_label_set_long_mode(ui->screen_home_lable_sys_name, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_home_lable_sys_name, 45.5, 14);
	lv_obj_set_size(ui->screen_home_lable_sys_name, 150, 23);
	
	//Write style for screen_home_lable_sys_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_home_lable_sys_name, lv_color_hex(0x3d00ff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_home_lable_sys_name, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_home_lable_sys_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_home_lable_sys_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_home_lable_sys_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_home_lable_sys_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen_home.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_home);

	//Init events for screen.
	events_init_screen_home(ui);
}
