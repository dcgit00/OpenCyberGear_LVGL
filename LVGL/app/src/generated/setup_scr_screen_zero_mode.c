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



void setup_scr_screen_zero_mode(lv_ui *ui)
{
	//Write codes screen_zero_mode
	ui->screen_zero_mode = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_zero_mode, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_zero_mode, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_zero_mode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_zero_mode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_zero_mode_cont_1
	ui->screen_zero_mode_cont_1 = lv_obj_create(ui->screen_zero_mode);
	lv_obj_set_pos(ui->screen_zero_mode_cont_1, 0, 0);
	lv_obj_set_size(ui->screen_zero_mode_cont_1, 240, 320);
	lv_obj_set_scrollbar_mode(ui->screen_zero_mode_cont_1, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_zero_mode_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_zero_mode_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_zero_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_zero_mode_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_zero_mode_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_zero_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_zero_mode_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_zero_mode_cont_1, lv_color_hex(0xa6ffd9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_zero_mode_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_zero_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_zero_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_zero_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_zero_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_zero_mode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_zero_mode_head_title
	ui->screen_zero_mode_head_title = lv_spangroup_create(ui->screen_zero_mode_cont_1);
	lv_spangroup_set_align(ui->screen_zero_mode_head_title, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_zero_mode_head_title, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_zero_mode_head_title, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_zero_mode_head_title_span;
	screen_zero_mode_head_title_span = lv_spangroup_new_span(ui->screen_zero_mode_head_title);
	lv_span_set_text(screen_zero_mode_head_title_span, "零点模式");
	lv_style_set_text_color(&screen_zero_mode_head_title_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_zero_mode_head_title_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_zero_mode_head_title_span->style, &lv_font_SourceHanSerifSC_Regular_20);
	lv_obj_set_pos(ui->screen_zero_mode_head_title, 77.5, 12);
	lv_obj_set_size(ui->screen_zero_mode_head_title, 85, 22);

	//Write style state: LV_STATE_DEFAULT for &style_screen_zero_mode_head_title_main_main_default
	static lv_style_t style_screen_zero_mode_head_title_main_main_default;
	ui_init_style(&style_screen_zero_mode_head_title_main_main_default);
	
	lv_style_set_border_width(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_style_set_radius(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_zero_mode_head_title_main_main_default, 0);
	lv_obj_add_style(ui->screen_zero_mode_head_title, &style_screen_zero_mode_head_title_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_zero_mode_head_title);

	//Write codes screen_zero_mode_show_data_cont
	ui->screen_zero_mode_show_data_cont = lv_obj_create(ui->screen_zero_mode_cont_1);
	lv_obj_set_pos(ui->screen_zero_mode_show_data_cont, 27.5, 42);
	lv_obj_set_size(ui->screen_zero_mode_show_data_cont, 185, 95);
	lv_obj_set_scrollbar_mode(ui->screen_zero_mode_show_data_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_zero_mode_show_data_cont, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_zero_mode_show_data_cont, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_zero_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_zero_mode_show_data_cont, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_zero_mode_show_data_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_zero_mode_show_data_cont, 13, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_zero_mode_show_data_cont, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_zero_mode_show_data_cont, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_zero_mode_show_data_cont, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_zero_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_zero_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_zero_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_zero_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_zero_mode_show_data_cont, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	
	//Write codes screen_zero_mode_motor_data
	ui->screen_zero_mode_motor_data = lv_label_create(ui->screen_zero_mode_show_data_cont);
	lv_label_set_text(ui->screen_zero_mode_motor_data, "position: 0.00\nspeed: 0.00\ntorque: 0.00\ntemp: 0.00\n");
	lv_label_set_long_mode(ui->screen_zero_mode_motor_data, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_zero_mode_motor_data, 7, 9);
	lv_obj_set_size(ui->screen_zero_mode_motor_data, 168, 74);
	
	//Write style for screen_zero_mode_motor_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_zero_mode_motor_data, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_zero_mode_motor_data, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_zero_mode_motor_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_zero_mode_motor_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_zero_mode_motor_data, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_zero_mode_motor_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_zero_mode_btn_set_zero
	ui->screen_zero_mode_btn_set_zero = lv_btn_create(ui->screen_zero_mode_cont_1);
	ui->screen_zero_mode_btn_set_zero_label = lv_label_create(ui->screen_zero_mode_btn_set_zero);
	lv_label_set_text(ui->screen_zero_mode_btn_set_zero_label, "设置零点");
	lv_label_set_long_mode(ui->screen_zero_mode_btn_set_zero_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_zero_mode_btn_set_zero_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_zero_mode_btn_set_zero, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_zero_mode_btn_set_zero_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_zero_mode_btn_set_zero, 70, 152);
	lv_obj_set_size(ui->screen_zero_mode_btn_set_zero, 100, 40);
	
	//Write style for screen_zero_mode_btn_set_zero, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_zero_mode_btn_set_zero, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_zero_mode_btn_set_zero, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_zero_mode_btn_set_zero, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_zero_mode_btn_set_zero, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_zero_mode_btn_set_zero, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_zero_mode_btn_set_zero, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_zero_mode_btn_set_zero, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_zero_mode_btn_set_zero, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_zero_mode_btn_set_zero, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_zero_mode_btn_set_zero, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_zero_mode_btn_run_zero
	ui->screen_zero_mode_btn_run_zero = lv_btn_create(ui->screen_zero_mode_cont_1);
	ui->screen_zero_mode_btn_run_zero_label = lv_label_create(ui->screen_zero_mode_btn_run_zero);
	lv_label_set_text(ui->screen_zero_mode_btn_run_zero_label, "运转归零");
	lv_label_set_long_mode(ui->screen_zero_mode_btn_run_zero_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_zero_mode_btn_run_zero_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_zero_mode_btn_run_zero, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_zero_mode_btn_run_zero_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_zero_mode_btn_run_zero, 70, 209);
	lv_obj_set_size(ui->screen_zero_mode_btn_run_zero, 100, 40);

	//Write style for screen_zero_mode_btn_run_zero, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_zero_mode_btn_run_zero, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_zero_mode_btn_run_zero, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_zero_mode_btn_run_zero, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_zero_mode_btn_run_zero, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_zero_mode_btn_run_zero, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_zero_mode_btn_run_zero, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_zero_mode_btn_run_zero, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_zero_mode_btn_run_zero, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_zero_mode_btn_run_zero, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_zero_mode_btn_run_zero, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_zero_mode_btn_back_home
	ui->screen_zero_mode_btn_back_home = lv_btn_create(ui->screen_zero_mode_cont_1);
	ui->screen_zero_mode_btn_back_home_label = lv_label_create(ui->screen_zero_mode_btn_back_home);
	lv_label_set_text(ui->screen_zero_mode_btn_back_home_label, "主页面");
	lv_label_set_long_mode(ui->screen_zero_mode_btn_back_home_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_zero_mode_btn_back_home_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_zero_mode_btn_back_home, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_zero_mode_btn_back_home_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_zero_mode_btn_back_home, 70, 265);
	lv_obj_set_size(ui->screen_zero_mode_btn_back_home, 100, 40);

	//Write style for screen_zero_mode_btn_back_home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_zero_mode_btn_back_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_zero_mode_btn_back_home, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_zero_mode_btn_back_home, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_zero_mode_btn_back_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_zero_mode_btn_back_home, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_zero_mode_btn_back_home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_zero_mode_btn_back_home, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_zero_mode_btn_back_home, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_zero_mode_btn_back_home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_zero_mode_btn_back_home, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen_zero_mode.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_zero_mode);

	//Init events for screen.
	events_init_screen_zero_mode(ui);
}