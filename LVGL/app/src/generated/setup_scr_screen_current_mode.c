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



void setup_scr_screen_current_mode(lv_ui *ui)
{
	//Write codes screen_current_mode
	ui->screen_current_mode = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_current_mode, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_current_mode, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_current_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_current_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_cont_1
	ui->screen_current_mode_cont_1 = lv_obj_create(ui->screen_current_mode);
	lv_obj_set_pos(ui->screen_current_mode_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_current_mode_cont_1, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_current_mode_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_current_mode_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_current_mode_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_current_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_current_mode_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_current_mode_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_current_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_cont_1, lv_color_hex(0xa6ffd9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_current_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_current_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_current_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_current_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_head_title
	ui->screen_current_mode_head_title = lv_spangroup_create(ui->screen_current_mode_cont_1);
	lv_spangroup_set_align(ui->screen_current_mode_head_title, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_current_mode_head_title, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_current_mode_head_title, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_current_mode_head_title_span;
	screen_current_mode_head_title_span = lv_spangroup_new_span(ui->screen_current_mode_head_title);
	lv_span_set_text(screen_current_mode_head_title_span, "电流模式");
	lv_style_set_text_color(&screen_current_mode_head_title_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_current_mode_head_title_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_current_mode_head_title_span->style, &lv_font_SourceHanSerifSC_Regular_20);
	lv_obj_set_pos(ui->screen_current_mode_head_title, 77.5, 12);
	lv_obj_set_size(ui->screen_current_mode_head_title, 85, 22);

	//Write style state: LV_STATE_DEFAULT for &style_screen_current_mode_head_title_main_main_default
	static lv_style_t style_screen_current_mode_head_title_main_main_default;
	ui_init_style(&style_screen_current_mode_head_title_main_main_default);
	
	lv_style_set_border_width(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_style_set_radius(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_current_mode_head_title_main_main_default, 0);
	lv_obj_add_style(ui->screen_current_mode_head_title, &style_screen_current_mode_head_title_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_current_mode_head_title);

	//Write codes screen_current_mode_show_data_cont
	ui->screen_current_mode_show_data_cont = lv_obj_create(ui->screen_current_mode_cont_1);
	lv_obj_set_pos(ui->screen_current_mode_show_data_cont, 27.5, 42);
	lv_obj_set_size(ui->screen_current_mode_show_data_cont, 185, 95);
	lv_obj_set_scrollbar_mode(ui->screen_current_mode_show_data_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_current_mode_show_data_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_current_mode_show_data_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_current_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_current_mode_show_data_cont, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_current_mode_show_data_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_show_data_cont, 13, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_current_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_show_data_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_show_data_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_current_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_current_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_current_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_current_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_motor_data
	ui->screen_current_mode_motor_data = lv_label_create(ui->screen_current_mode_show_data_cont);
	lv_label_set_text(ui->screen_current_mode_motor_data, "position: 0.00\nspeed: 0.00\ntorque: 0.00\ntemp: 0.00\n");
	lv_label_set_long_mode(ui->screen_current_mode_motor_data, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_current_mode_motor_data, 7, 9);
	lv_obj_set_size(ui->screen_current_mode_motor_data, 168, 74);

	//Write style for screen_current_mode_motor_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_current_mode_motor_data, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_current_mode_motor_data, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_current_mode_motor_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_current_mode_motor_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_current_mode_motor_data, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_slider_current
	ui->screen_current_mode_slider_current = lv_slider_create(ui->screen_current_mode_cont_1);
	lv_slider_set_range(ui->screen_current_mode_slider_current, -2300, 2300);
	lv_slider_set_mode(ui->screen_current_mode_slider_current, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_current_mode_slider_current, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_current_mode_slider_current, 30, 179);
	lv_obj_set_size(ui->screen_current_mode_slider_current, 180, 15);

	//Write style for screen_current_mode_slider_current, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_current_mode_slider_current, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_slider_current, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_slider_current, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_slider_current, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_current_mode_slider_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_slider_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_current_mode_slider_current, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_current_mode_slider_current, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_slider_current, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_slider_current, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_slider_current, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_current_mode_slider_current, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_current_mode_slider_current, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_slider_current, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_slider_current, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_slider_current, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_label_current
	ui->screen_current_mode_label_current = lv_label_create(ui->screen_current_mode_cont_1);
	lv_label_set_text(ui->screen_current_mode_label_current, "Current : 0.00");
	lv_label_set_long_mode(ui->screen_current_mode_label_current, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_current_mode_label_current, 35, 206);
	lv_obj_set_size(ui->screen_current_mode_label_current, 170, 20);

	//Write style for screen_current_mode_label_current, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_current_mode_label_current, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_current_mode_label_current, &lv_font_SourceHanSerifSC_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_current_mode_label_current, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_current_mode_label_current, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_current_mode_label_current, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_btn_back_home
	ui->screen_current_mode_btn_back_home = lv_btn_create(ui->screen_current_mode_cont_1);
	ui->screen_current_mode_btn_back_home_label = lv_label_create(ui->screen_current_mode_btn_back_home);
	lv_label_set_text(ui->screen_current_mode_btn_back_home_label, "返回");
	lv_label_set_long_mode(ui->screen_current_mode_btn_back_home_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_current_mode_btn_back_home_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_current_mode_btn_back_home, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_current_mode_btn_back_home_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_current_mode_btn_back_home, 168, 274);
	lv_obj_set_size(ui->screen_current_mode_btn_back_home, 65, 36);

	//Write style for screen_current_mode_btn_back_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_current_mode_btn_back_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_btn_back_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_btn_back_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_current_mode_btn_back_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_btn_back_home, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_btn_back_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_current_mode_btn_back_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_current_mode_btn_back_home, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_current_mode_btn_back_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_current_mode_btn_back_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_btn_stop
	ui->screen_current_mode_btn_stop = lv_btn_create(ui->screen_current_mode_cont_1);
	ui->screen_current_mode_btn_stop_label = lv_label_create(ui->screen_current_mode_btn_stop);
	lv_label_set_text(ui->screen_current_mode_btn_stop_label, "停止");
	lv_label_set_long_mode(ui->screen_current_mode_btn_stop_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_current_mode_btn_stop_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_current_mode_btn_stop, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_current_mode_btn_stop_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_current_mode_btn_stop, 88, 274);
	lv_obj_set_size(ui->screen_current_mode_btn_stop, 65, 36);

	//Write style for screen_current_mode_btn_stop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_current_mode_btn_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_btn_stop, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_btn_stop, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_current_mode_btn_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_btn_stop, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_btn_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_current_mode_btn_stop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_current_mode_btn_stop, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_current_mode_btn_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_current_mode_btn_stop, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_current_mode_btn_run
	ui->screen_current_mode_btn_run = lv_btn_create(ui->screen_current_mode_cont_1);
	ui->screen_current_mode_btn_run_label = lv_label_create(ui->screen_current_mode_btn_run);
	lv_label_set_text(ui->screen_current_mode_btn_run_label, "运行");
	lv_label_set_long_mode(ui->screen_current_mode_btn_run_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_current_mode_btn_run_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_current_mode_btn_run, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_current_mode_btn_run_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_current_mode_btn_run, 5, 274);
	lv_obj_set_size(ui->screen_current_mode_btn_run, 65, 36);

	//Write style for screen_current_mode_btn_run, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_current_mode_btn_run, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_current_mode_btn_run, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_current_mode_btn_run, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_current_mode_btn_run, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_current_mode_btn_run, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_current_mode_btn_run, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_current_mode_btn_run, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_current_mode_btn_run, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_current_mode_btn_run, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_current_mode_btn_run, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen_current_mode.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_current_mode);

	//Init events for screen.
	events_init_screen_current_mode(ui);
}
