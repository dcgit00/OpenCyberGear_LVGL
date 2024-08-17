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



void setup_scr_screen_run_ctrl_mode(lv_ui *ui)
{
	//Write codes screen_run_ctrl_mode
	ui->screen_run_ctrl_mode = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_run_ctrl_mode, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_run_ctrl_mode, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_run_ctrl_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_cont_1
	ui->screen_run_ctrl_mode_cont_1 = lv_obj_create(ui->screen_run_ctrl_mode);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_run_ctrl_mode_cont_1, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_run_ctrl_mode_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_run_ctrl_mode_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_run_ctrl_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_run_ctrl_mode_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_run_ctrl_mode_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_cont_1, lv_color_hex(0xa6ffd9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_head_title
	ui->screen_run_ctrl_mode_head_title = lv_spangroup_create(ui->screen_run_ctrl_mode_cont_1);
	lv_spangroup_set_align(ui->screen_run_ctrl_mode_head_title, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_run_ctrl_mode_head_title, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_run_ctrl_mode_head_title, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_run_ctrl_mode_head_title_span;
	screen_run_ctrl_mode_head_title_span = lv_spangroup_new_span(ui->screen_run_ctrl_mode_head_title);
	lv_span_set_text(screen_run_ctrl_mode_head_title_span, "运控模式");
	lv_style_set_text_color(&screen_run_ctrl_mode_head_title_span->style, lv_color_hex(0x3d00ff));
	lv_style_set_text_decor(&screen_run_ctrl_mode_head_title_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_run_ctrl_mode_head_title_span->style, &lv_font_SourceHanSerifSC_Regular_20);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_head_title, 78.5, 7);
	lv_obj_set_size(ui->screen_run_ctrl_mode_head_title, 83, 22);

	//Write style state: LV_STATE_DEFAULT for &style_screen_run_ctrl_mode_head_title_main_main_default
	static lv_style_t style_screen_run_ctrl_mode_head_title_main_main_default;
	ui_init_style(&style_screen_run_ctrl_mode_head_title_main_main_default);
	
	lv_style_set_border_width(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_style_set_radius(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_run_ctrl_mode_head_title_main_main_default, 0);
	lv_obj_add_style(ui->screen_run_ctrl_mode_head_title, &style_screen_run_ctrl_mode_head_title_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_run_ctrl_mode_head_title);

	//Write codes screen_run_ctrl_mode_show_data_cont
	ui->screen_run_ctrl_mode_show_data_cont = lv_obj_create(ui->screen_run_ctrl_mode_cont_1);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_show_data_cont, 27.5, 31);
	lv_obj_set_size(ui->screen_run_ctrl_mode_show_data_cont, 185, 80);
	lv_obj_set_scrollbar_mode(ui->screen_run_ctrl_mode_show_data_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_run_ctrl_mode_show_data_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_show_data_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_run_ctrl_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_run_ctrl_mode_show_data_cont, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_run_ctrl_mode_show_data_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_show_data_cont, 13, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_show_data_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_show_data_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_motor_data
	ui->screen_run_ctrl_mode_motor_data = lv_label_create(ui->screen_run_ctrl_mode_show_data_cont);
	lv_label_set_text(ui->screen_run_ctrl_mode_motor_data, "position: 0.00\nspeed: 0.00\ntorque: 0.00\ntemp: 0.00\n");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_motor_data, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_motor_data, 15, 8);
	lv_obj_set_size(ui->screen_run_ctrl_mode_motor_data, 150, 60);
	
	//Write style for screen_run_ctrl_mode_motor_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_motor_data, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_motor_data, &lv_font_SourceHanSerifSC_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_motor_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_run_ctrl_mode_motor_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_motor_data, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_btn_run
	ui->screen_run_ctrl_mode_btn_run = lv_btn_create(ui->screen_run_ctrl_mode_cont_1);
	ui->screen_run_ctrl_mode_btn_run_label = lv_label_create(ui->screen_run_ctrl_mode_btn_run);
	lv_label_set_text(ui->screen_run_ctrl_mode_btn_run_label, "运行");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_btn_run_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_run_ctrl_mode_btn_run_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_run_ctrl_mode_btn_run, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_run_ctrl_mode_btn_run_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_run_ctrl_mode_btn_run, 5, 274);
	lv_obj_set_size(ui->screen_run_ctrl_mode_btn_run, 65, 36);

	//Write style for screen_run_ctrl_mode_btn_run, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_btn_run, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_btn_run, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_btn_run, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_btn_run, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_btn_run, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_btn_run, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_btn_run, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_btn_run, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_btn_run, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_btn_run, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_btn_stop
	ui->screen_run_ctrl_mode_btn_stop = lv_btn_create(ui->screen_run_ctrl_mode_cont_1);
	ui->screen_run_ctrl_mode_btn_stop_label = lv_label_create(ui->screen_run_ctrl_mode_btn_stop);
	lv_label_set_text(ui->screen_run_ctrl_mode_btn_stop_label, "停止");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_btn_stop_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_run_ctrl_mode_btn_stop_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_run_ctrl_mode_btn_stop, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_run_ctrl_mode_btn_stop_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_run_ctrl_mode_btn_stop, 88, 274);
	lv_obj_set_size(ui->screen_run_ctrl_mode_btn_stop, 65, 36);

	//Write style for screen_run_ctrl_mode_btn_stop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_btn_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_btn_stop, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_btn_stop, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_btn_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_btn_stop, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_btn_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_btn_stop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_btn_stop, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_btn_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_btn_stop, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_btn_back_home
	ui->screen_run_ctrl_mode_btn_back_home = lv_btn_create(ui->screen_run_ctrl_mode_cont_1);
	ui->screen_run_ctrl_mode_btn_back_home_label = lv_label_create(ui->screen_run_ctrl_mode_btn_back_home);
	lv_label_set_text(ui->screen_run_ctrl_mode_btn_back_home_label, "返回");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_btn_back_home_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_run_ctrl_mode_btn_back_home_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_run_ctrl_mode_btn_back_home, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_run_ctrl_mode_btn_back_home_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_run_ctrl_mode_btn_back_home, 168, 274);
	lv_obj_set_size(ui->screen_run_ctrl_mode_btn_back_home, 65, 36);

	//Write style for screen_run_ctrl_mode_btn_back_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_btn_back_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_btn_back_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_btn_back_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_btn_back_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_btn_back_home, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_btn_back_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_btn_back_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_btn_back_home, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_btn_back_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_btn_back_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_slide_torque
	ui->screen_run_ctrl_mode_slide_torque = lv_slider_create(ui->screen_run_ctrl_mode_cont_1);
	lv_slider_set_range(ui->screen_run_ctrl_mode_slide_torque, -600, 600);
	lv_slider_set_mode(ui->screen_run_ctrl_mode_slide_torque, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_run_ctrl_mode_slide_torque, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_slide_torque, 25, 135);
	lv_obj_set_size(ui->screen_run_ctrl_mode_slide_torque, 190, 10);

	//Write style for screen_run_ctrl_mode_slide_torque, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_torque, 130, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_torque, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_torque, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_torque, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_run_ctrl_mode_slide_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_slide_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_torque, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_torque, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_torque, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_torque, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_torque, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_torque, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_torque, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_torque, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_torque, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_torque, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_slide_speed
	ui->screen_run_ctrl_mode_slide_speed = lv_slider_create(ui->screen_run_ctrl_mode_cont_1);
	lv_slider_set_range(ui->screen_run_ctrl_mode_slide_speed, -3000, 3000);
	lv_slider_set_mode(ui->screen_run_ctrl_mode_slide_speed, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_run_ctrl_mode_slide_speed, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_slide_speed, 25, 165);
	lv_obj_set_size(ui->screen_run_ctrl_mode_slide_speed, 190, 10);

	//Write style for screen_run_ctrl_mode_slide_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_speed, 130, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_speed, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_speed, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_speed, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_run_ctrl_mode_slide_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_slide_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_speed, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_speed, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_speed, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_speed, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_speed, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_speed, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_speed, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_speed, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_speed, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_speed, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_slide_pos
	ui->screen_run_ctrl_mode_slide_pos = lv_slider_create(ui->screen_run_ctrl_mode_cont_1);
	lv_slider_set_range(ui->screen_run_ctrl_mode_slide_pos, -72000, 72000);
	lv_slider_set_mode(ui->screen_run_ctrl_mode_slide_pos, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_run_ctrl_mode_slide_pos, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_slide_pos, 26, 195);
	lv_obj_set_size(ui->screen_run_ctrl_mode_slide_pos, 190, 10);

	//Write style for screen_run_ctrl_mode_slide_pos, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_pos, 129, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_pos, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_pos, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_pos, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_run_ctrl_mode_slide_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_slide_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_pos, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_pos, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_pos, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_pos, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_pos, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_pos, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_pos, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_pos, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_pos, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_pos, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_slide_kp
	ui->screen_run_ctrl_mode_slide_kp = lv_slider_create(ui->screen_run_ctrl_mode_cont_1);
	lv_slider_set_range(ui->screen_run_ctrl_mode_slide_kp, 0, 5000);
	lv_slider_set_mode(ui->screen_run_ctrl_mode_slide_kp, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_run_ctrl_mode_slide_kp, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_slide_kp, 25, 225);
	lv_obj_set_size(ui->screen_run_ctrl_mode_slide_kp, 190, 10);

	//Write style for screen_run_ctrl_mode_slide_kp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_kp, 130, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_kp, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_kp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_kp, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_run_ctrl_mode_slide_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_slide_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_kp, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_kp, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_kp, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_kp, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_kp, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_kp, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_kp, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_kp, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_kp, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_kp, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_slide_kd
	ui->screen_run_ctrl_mode_slide_kd = lv_slider_create(ui->screen_run_ctrl_mode_cont_1);
	lv_slider_set_range(ui->screen_run_ctrl_mode_slide_kd, 0, 500);
	lv_slider_set_mode(ui->screen_run_ctrl_mode_slide_kd, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_run_ctrl_mode_slide_kd, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_slide_kd, 25, 255);
	lv_obj_set_size(ui->screen_run_ctrl_mode_slide_kd, 190, 10);

	//Write style for screen_run_ctrl_mode_slide_kd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_kd, 128, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_kd, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_kd, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_kd, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_run_ctrl_mode_slide_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_slide_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_kd, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_kd, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_kd, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_kd, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_kd, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_run_ctrl_mode_slide_kd, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_slide_kd, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_run_ctrl_mode_slide_kd, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_run_ctrl_mode_slide_kd, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_slide_kd, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_label_torque
	ui->screen_run_ctrl_mode_label_torque = lv_label_create(ui->screen_run_ctrl_mode_cont_1);
	lv_label_set_text(ui->screen_run_ctrl_mode_label_torque, "Torque : 0.00");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_label_torque, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_label_torque, 40, 113);
	lv_obj_set_size(ui->screen_run_ctrl_mode_label_torque, 160, 15);

	//Write style for screen_run_ctrl_mode_label_torque, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_label_torque, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_label_torque, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_label_torque, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_run_ctrl_mode_label_torque, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_label_torque, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_label_torque, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_label_speed
	ui->screen_run_ctrl_mode_label_speed = lv_label_create(ui->screen_run_ctrl_mode_cont_1);
	lv_label_set_text(ui->screen_run_ctrl_mode_label_speed, "Speed : 0.00");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_label_speed, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_label_speed, 45, 148);
	lv_obj_set_size(ui->screen_run_ctrl_mode_label_speed, 150, 15);

	//Write style for screen_run_ctrl_mode_label_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_label_speed, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_label_speed, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_label_speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_run_ctrl_mode_label_speed, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_label_speed, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_label_pos
	ui->screen_run_ctrl_mode_label_pos = lv_label_create(ui->screen_run_ctrl_mode_cont_1);
	lv_label_set_text(ui->screen_run_ctrl_mode_label_pos, "Position : 0.00");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_label_pos, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_label_pos, 45, 179);
	lv_obj_set_size(ui->screen_run_ctrl_mode_label_pos, 150, 15);

	//Write style for screen_run_ctrl_mode_label_pos, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_label_pos, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_label_pos, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_label_pos, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_run_ctrl_mode_label_pos, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_label_pos, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_label_pos, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_label_kp
	ui->screen_run_ctrl_mode_label_kp = lv_label_create(ui->screen_run_ctrl_mode_cont_1);
	lv_label_set_text(ui->screen_run_ctrl_mode_label_kp, "Kp : 0.00");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_label_kp, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_label_kp, 45, 208);
	lv_obj_set_size(ui->screen_run_ctrl_mode_label_kp, 150, 15);

	//Write style for screen_run_ctrl_mode_label_kp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_label_kp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_label_kp, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_label_kp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_run_ctrl_mode_label_kp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_label_kp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_label_kp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_run_ctrl_mode_label_kd
	ui->screen_run_ctrl_mode_label_kd = lv_label_create(ui->screen_run_ctrl_mode_cont_1);
	lv_label_set_text(ui->screen_run_ctrl_mode_label_kd, "Kd : 0.00");
	lv_label_set_long_mode(ui->screen_run_ctrl_mode_label_kd, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_run_ctrl_mode_label_kd, 45, 240);
	lv_obj_set_size(ui->screen_run_ctrl_mode_label_kd, 150, 15);

	//Write style for screen_run_ctrl_mode_label_kd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_run_ctrl_mode_label_kd, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_run_ctrl_mode_label_kd, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_run_ctrl_mode_label_kd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_run_ctrl_mode_label_kd, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_run_ctrl_mode_label_kd, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_run_ctrl_mode_label_kd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen_run_ctrl_mode.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_run_ctrl_mode);

	//Init events for screen.
	events_init_screen_run_ctrl_mode(ui);
}
