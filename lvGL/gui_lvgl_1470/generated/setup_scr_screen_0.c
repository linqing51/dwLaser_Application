/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

static lv_obj_t * g_kb_screen_0;
static void kb_screen_0_event_cb(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *kb = lv_event_get_target(e);
	if(code == LV_EVENT_READY || code == LV_EVENT_CANCEL){
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}
__attribute__((unused)) static void ta_screen_0_event_cb(lv_event_t *e)
{

	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *ta = lv_event_get_target(e);
	lv_obj_t *kb = lv_event_get_user_data(e);
	if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
	{
		lv_keyboard_set_textarea(kb, ta);
		lv_obj_move_foreground(kb);
		lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
	if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
	{
		lv_keyboard_set_textarea(kb, NULL);
		lv_obj_move_background(kb);
		lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
	}
}

void setup_scr_screen_0(lv_ui *ui){

	//Write codes screen_0
	ui->screen_0 = lv_obj_create(NULL);

	//Create keyboard on screen_0
	g_kb_screen_0 = lv_keyboard_create(ui->screen_0);
	lv_obj_add_event_cb(g_kb_screen_0, kb_screen_0_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(g_kb_screen_0, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(g_kb_screen_0, &lv_font_simsun_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_scrollbar_mode(ui->screen_0, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_0. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_bg_color(ui->screen_0, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_0, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_0, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_0_img_1
	ui->screen_0_img_1 = lv_img_create(ui->screen_0);
	lv_obj_set_pos(ui->screen_0_img_1, 0, 0);
	lv_obj_set_size(ui->screen_0_img_1, 1024, 600);
	lv_obj_set_scrollbar_mode(ui->screen_0_img_1, LV_SCROLLBAR_MODE_OFF);

	//Set style for screen_0_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
	lv_obj_set_style_img_recolor(ui->screen_0_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(ui->screen_0_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_0_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->screen_0_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_0_img_1,&_1_0_GDDC_PAGE_POWERUP_TRI_alpha_1024x600);
	lv_img_set_pivot(ui->screen_0_img_1, 50,50);
	lv_img_set_angle(ui->screen_0_img_1, 0);
}