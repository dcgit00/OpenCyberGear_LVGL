/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "custom.h"

typedef struct
{
  
	lv_obj_t *screen_home;
	bool screen_home_del;
	lv_obj_t *screen_home_cont_1;
	lv_obj_t *screen_home_btn_zero_mode;
	lv_obj_t *screen_home_btn_zero_mode_label;
	lv_obj_t *screen_home_btn_speed_mode;
	lv_obj_t *screen_home_btn_speed_mode_label;
	lv_obj_t *screen_home_btn_current_mode;
	lv_obj_t *screen_home_btn_current_mode_label;
	lv_obj_t *screen_home_btn_pos_mode;
	lv_obj_t *screen_home_btn_pos_mode_label;
	lv_obj_t *screen_home_btn_run_ctrl_mode;
	lv_obj_t *screen_home_btn_run_ctrl_mode_label;
	lv_obj_t *screen_home_device_id;
	lv_obj_t *screen_home_lable_sys_name;
	lv_obj_t *screen_run_ctrl_mode;
	bool screen_run_ctrl_mode_del;
	lv_obj_t *screen_run_ctrl_mode_cont_1;
	lv_obj_t *screen_run_ctrl_mode_head_title;
	lv_obj_t *screen_run_ctrl_mode_show_data_cont;
	lv_obj_t *screen_run_ctrl_mode_motor_data;
	lv_obj_t *screen_run_ctrl_mode_btn_run;
	lv_obj_t *screen_run_ctrl_mode_btn_run_label;
	lv_obj_t *screen_run_ctrl_mode_btn_stop;
	lv_obj_t *screen_run_ctrl_mode_btn_stop_label;
	lv_obj_t *screen_run_ctrl_mode_btn_back_home;
	lv_obj_t *screen_run_ctrl_mode_btn_back_home_label;
	lv_obj_t *screen_run_ctrl_mode_slide_torque;
	lv_obj_t *screen_run_ctrl_mode_slide_speed;
	lv_obj_t *screen_run_ctrl_mode_slide_pos;
	lv_obj_t *screen_run_ctrl_mode_slide_kp;
	lv_obj_t *screen_run_ctrl_mode_slide_kd;
	lv_obj_t *screen_run_ctrl_mode_label_torque;
	lv_obj_t *screen_run_ctrl_mode_label_speed;
	lv_obj_t *screen_run_ctrl_mode_label_pos;
	lv_obj_t *screen_run_ctrl_mode_label_kp;
	lv_obj_t *screen_run_ctrl_mode_label_kd;
	lv_obj_t *screen_pos_mode;
	bool screen_pos_mode_del;
	lv_obj_t *screen_pos_mode_cont_1;
	lv_obj_t *screen_pos_mode_head_title;
	lv_obj_t *screen_pos_mode_show_data_cont;
	lv_obj_t *screen_pos_mode_motor_data;
	lv_obj_t *screen_pos_mode_slider_position;
	lv_obj_t *screen_pos_mode_slider_speed;
	lv_obj_t *screen_pos_mode_back;
	lv_obj_t *screen_pos_mode_back_label;
	lv_obj_t *screen_pos_mode_stop;
	lv_obj_t *screen_pos_mode_stop_label;
	lv_obj_t *screen_pos_mode_run;
	lv_obj_t *screen_pos_mode_run_label;
	lv_obj_t *screen_pos_mode_label_position;
	lv_obj_t *screen_pos_mode_label_speed;
	lv_obj_t *screen_current_mode;
	bool screen_current_mode_del;
	lv_obj_t *screen_current_mode_cont_1;
	lv_obj_t *screen_current_mode_head_title;
	lv_obj_t *screen_current_mode_show_data_cont;
	lv_obj_t *screen_current_mode_motor_data;
	lv_obj_t *screen_current_mode_slider_current;
	lv_obj_t *screen_current_mode_label_current;
	lv_obj_t *screen_current_mode_btn_back_home;
	lv_obj_t *screen_current_mode_btn_back_home_label;
	lv_obj_t *screen_current_mode_btn_stop;
	lv_obj_t *screen_current_mode_btn_stop_label;
	lv_obj_t *screen_current_mode_btn_run;
	lv_obj_t *screen_current_mode_btn_run_label;
	lv_obj_t *screen_speed_mode;
	bool screen_speed_mode_del;
	lv_obj_t *screen_speed_mode_cont_1;
	lv_obj_t *screen_speed_mode_head_title;
	lv_obj_t *screen_speed_mode_show_data_cont;
	lv_obj_t *screen_speed_mode_motor_data;
	lv_obj_t *screen_speed_mode_btn_back_home;
	lv_obj_t *screen_speed_mode_btn_back_home_label;
	lv_obj_t *screen_speed_mode_btn_stop;
	lv_obj_t *screen_speed_mode_btn_stop_label;
	lv_obj_t *screen_speed_mode_btn_run;
	lv_obj_t *screen_speed_mode_btn_run_label;
	lv_obj_t *screen_speed_mode_label_current;
	lv_obj_t *screen_speed_mode_slider_current;
	lv_obj_t *screen_speed_mode_label_speed;
	lv_obj_t *screen_speed_mode_slider_speed;
	lv_obj_t *screen_zero_mode;
	bool screen_zero_mode_del;
	lv_obj_t *screen_zero_mode_cont_1;
	lv_obj_t *screen_zero_mode_head_title;
	lv_obj_t *screen_zero_mode_show_data_cont;
	lv_obj_t *screen_zero_mode_motor_data;
	lv_obj_t *screen_zero_mode_btn_set_zero;
	lv_obj_t *screen_zero_mode_btn_set_zero_label;
	lv_obj_t *screen_zero_mode_btn_run_zero;
	lv_obj_t *screen_zero_mode_btn_run_zero_label;
	lv_obj_t *screen_zero_mode_btn_back_home;
	lv_obj_t *screen_zero_mode_btn_back_home_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_move_animation(void * var, int32_t duration, int32_t delay, int32_t x_end, int32_t y_end, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_scale_animation(void * var, int32_t duration, int32_t delay, int32_t width, int32_t height, lv_anim_path_cb_t path_cb,
                        uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                        lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_zoom_animation(void * var, int32_t duration, int32_t delay, int32_t zoom, lv_anim_path_cb_t path_cb,
                           uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                           lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_rotate_animation(void * var, int32_t duration, int32_t delay, lv_coord_t x, lv_coord_t y, int32_t rotate,
                   lv_anim_path_cb_t path_cb, uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time,
                   uint32_t playback_delay, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_screen_home(lv_ui *ui);
void setup_scr_screen_run_ctrl_mode(lv_ui *ui);
void setup_scr_screen_pos_mode(lv_ui *ui);
void setup_scr_screen_current_mode(lv_ui *ui);
void setup_scr_screen_speed_mode(lv_ui *ui);
void setup_scr_screen_zero_mode(lv_ui *ui);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_12)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_20)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_14)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_15)


#ifdef __cplusplus
}
#endif
#endif
