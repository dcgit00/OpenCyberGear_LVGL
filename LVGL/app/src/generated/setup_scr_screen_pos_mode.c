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



void setup_scr_screen_pos_mode(lv_ui *ui)
{
	//Write codes screen_pos_mode
	ui->screen_pos_mode = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_pos_mode, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_pos_mode, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_pos_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_cont_1
	ui->screen_pos_mode_cont_1 = lv_obj_create(ui->screen_pos_mode);
	lv_obj_set_pos(ui->screen_pos_mode_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_pos_mode_cont_1, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_pos_mode_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_pos_mode_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pos_mode_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_pos_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_pos_mode_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_pos_mode_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_cont_1, lv_color_hex(0xa6ffd9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pos_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pos_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pos_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pos_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_head_title
	ui->screen_pos_mode_head_title = lv_spangroup_create(ui->screen_pos_mode_cont_1);
	lv_spangroup_set_align(ui->screen_pos_mode_head_title, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_pos_mode_head_title, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_pos_mode_head_title, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_pos_mode_head_title_span;
	screen_pos_mode_head_title_span = lv_spangroup_new_span(ui->screen_pos_mode_head_title);
	lv_span_set_text(screen_pos_mode_head_title_span, "位置模式");
	lv_style_set_text_color(&screen_pos_mode_head_title_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_pos_mode_head_title_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_pos_mode_head_title_span->style, &lv_font_SourceHanSerifSC_Regular_20);
	lv_obj_set_pos(ui->screen_pos_mode_head_title, 77.5, 12);
	lv_obj_set_size(ui->screen_pos_mode_head_title, 85, 22);

	//Write style state: LV_STATE_DEFAULT for &style_screen_pos_mode_head_title_main_main_default
	static lv_style_t style_screen_pos_mode_head_title_main_main_default;
	ui_init_style(&style_screen_pos_mode_head_title_main_main_default);
	
	lv_style_set_border_width(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_style_set_radius(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_pos_mode_head_title_main_main_default, 0);
	lv_obj_add_style(ui->screen_pos_mode_head_title, &style_screen_pos_mode_head_title_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_pos_mode_head_title);

	//Write codes screen_pos_mode_show_data_cont
	ui->screen_pos_mode_show_data_cont = lv_obj_create(ui->screen_pos_mode_cont_1);
	lv_obj_set_pos(ui->screen_pos_mode_show_data_cont, 27.5, 42);
	lv_obj_set_size(ui->screen_pos_mode_show_data_cont, 185, 95);
	lv_obj_set_scrollbar_mode(ui->screen_pos_mode_show_data_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_pos_mode_show_data_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pos_mode_show_data_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_pos_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_pos_mode_show_data_cont, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_pos_mode_show_data_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_show_data_cont, 13, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_show_data_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_show_data_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pos_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pos_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pos_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pos_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_motor_data
	ui->screen_pos_mode_motor_data = lv_label_create(ui->screen_pos_mode_show_data_cont);
	lv_label_set_text(ui->screen_pos_mode_motor_data, "position: 0.00\nspeed: 0.00\ntorque: 0.00\ntemp: 0.00\n");
	lv_label_set_long_mode(ui->screen_pos_mode_motor_data, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_pos_mode_motor_data, 7, 9);
	lv_obj_set_size(ui->screen_pos_mode_motor_data, 168, 74);

	//Write style for screen_pos_mode_motor_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pos_mode_motor_data, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pos_mode_motor_data, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_pos_mode_motor_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_pos_mode_motor_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pos_mode_motor_data, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_slider_position
	ui->screen_pos_mode_slider_position = lv_slider_create(ui->screen_pos_mode_cont_1);
	lv_slider_set_range(ui->screen_pos_mode_slider_position, -72000, 72000);
	lv_slider_set_mode(ui->screen_pos_mode_slider_position, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_pos_mode_slider_position, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_pos_mode_slider_position, 30, 214);
	lv_obj_set_size(ui->screen_pos_mode_slider_position, 180, 15);

	//Write style for screen_pos_mode_slider_position, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_slider_position, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_slider_position, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_slider_position, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_slider_position, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_pos_mode_slider_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_slider_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_pos_mode_slider_position, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_slider_position, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_slider_position, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_slider_position, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_slider_position, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_pos_mode_slider_position, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_slider_position, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_slider_position, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_slider_position, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_slider_position, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_slider_speed
	ui->screen_pos_mode_slider_speed = lv_slider_create(ui->screen_pos_mode_cont_1);
	lv_slider_set_range(ui->screen_pos_mode_slider_speed, 0, 3000);
	lv_slider_set_mode(ui->screen_pos_mode_slider_speed, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_pos_mode_slider_speed, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_pos_mode_slider_speed, 30, 156);
	lv_obj_set_size(ui->screen_pos_mode_slider_speed, 180, 15);

	//Write style for screen_pos_mode_slider_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_slider_speed, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_slider_speed, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_slider_speed, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_slider_speed, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_pos_mode_slider_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_slider_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_pos_mode_slider_speed, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_slider_speed, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_slider_speed, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_slider_speed, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_slider_speed, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_pos_mode_slider_speed, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_slider_speed, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_slider_speed, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_slider_speed, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_slider_speed, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_back
	ui->screen_pos_mode_back = lv_btn_create(ui->screen_pos_mode_cont_1);
	ui->screen_pos_mode_back_label = lv_label_create(ui->screen_pos_mode_back);
	lv_label_set_text(ui->screen_pos_mode_back_label, "返回");
	lv_label_set_long_mode(ui->screen_pos_mode_back_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_pos_mode_back_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_pos_mode_back, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_pos_mode_back_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_pos_mode_back, 168, 274);
	lv_obj_set_size(ui->screen_pos_mode_back, 65, 36);

	//Write style for screen_pos_mode_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_back, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_back, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_pos_mode_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_back, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pos_mode_back, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pos_mode_back, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_pos_mode_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pos_mode_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_stop
	ui->screen_pos_mode_stop = lv_btn_create(ui->screen_pos_mode_cont_1);
	ui->screen_pos_mode_stop_label = lv_label_create(ui->screen_pos_mode_stop);
	lv_label_set_text(ui->screen_pos_mode_stop_label, "停止");
	lv_label_set_long_mode(ui->screen_pos_mode_stop_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_pos_mode_stop_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_pos_mode_stop, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_pos_mode_stop_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_pos_mode_stop, 88, 274);
	lv_obj_set_size(ui->screen_pos_mode_stop, 65, 36);

	//Write style for screen_pos_mode_stop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_stop, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_stop, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_pos_mode_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_stop, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pos_mode_stop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pos_mode_stop, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_pos_mode_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pos_mode_stop, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_run
	ui->screen_pos_mode_run = lv_btn_create(ui->screen_pos_mode_cont_1);
	ui->screen_pos_mode_run_label = lv_label_create(ui->screen_pos_mode_run);
	lv_label_set_text(ui->screen_pos_mode_run_label, "运行");
	lv_label_set_long_mode(ui->screen_pos_mode_run_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_pos_mode_run_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_pos_mode_run, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_pos_mode_run_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_pos_mode_run, 5, 274);
	lv_obj_set_size(ui->screen_pos_mode_run, 65, 36);

	//Write style for screen_pos_mode_run, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_run, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_pos_mode_run, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_pos_mode_run, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_pos_mode_run, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_run, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_run, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pos_mode_run, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pos_mode_run, &lv_font_SourceHanSerifSC_Regular_15, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_pos_mode_run, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pos_mode_run, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_label_position
	ui->screen_pos_mode_label_position = lv_label_create(ui->screen_pos_mode_cont_1);
	lv_label_set_text(ui->screen_pos_mode_label_position, "Position : 0.00");
	lv_label_set_long_mode(ui->screen_pos_mode_label_position, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_pos_mode_label_position, 35, 240);
	lv_obj_set_size(ui->screen_pos_mode_label_position, 170, 20);
	
	//Write style for screen_pos_mode_label_position, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pos_mode_label_position, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pos_mode_label_position, &lv_font_SourceHanSerifSC_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_pos_mode_label_position, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_pos_mode_label_position, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pos_mode_label_position, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_label_position, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_pos_mode_label_speed
	ui->screen_pos_mode_label_speed = lv_label_create(ui->screen_pos_mode_cont_1);
	lv_label_set_text(ui->screen_pos_mode_label_speed, "Speed : 0.00");
	lv_label_set_long_mode(ui->screen_pos_mode_label_speed, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_pos_mode_label_speed, 35, 181);
	lv_obj_set_size(ui->screen_pos_mode_label_speed, 170, 20);
	
	//Write style for screen_pos_mode_label_speed, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_pos_mode_label_speed, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_pos_mode_label_speed, &lv_font_SourceHanSerifSC_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_pos_mode_label_speed, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_pos_mode_label_speed, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_pos_mode_label_speed, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_pos_mode_label_speed, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen_pos_mode.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_pos_mode);

	//Init events for screen.
	events_init_screen_pos_mode(ui);
}
