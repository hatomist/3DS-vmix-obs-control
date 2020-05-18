#include <src/lv_core/lv_style.h>
#include <lvgl.h>
#include "setcontent.h"
#include "../logger/Logger.h"

LV_FONT_DECLARE(fnt)
extern Logger logger;

std::string wifi_str_t[] = {LV_SYMBOL_WIFI_0, LV_SYMBOL_WIFI_1, LV_SYMBOL_WIFI_2, LV_SYMBOL_WIFI_3};
std::string bat_lvl_t[] = {LV_SYMBOL_BATTERY_EMPTY, LV_SYMBOL_BATTERY_1, LV_SYMBOL_BATTERY_1, LV_SYMBOL_BATTERY_2,
                           LV_SYMBOL_BATTERY_3, LV_SYMBOL_BATTERY_FULL};

struct wifi_n_bat {
    lv_obj_t *bat;
    lv_obj_t *wifi;
};

void setcontent(lv_disp_t *disp_bot, lv_disp_t *disp_top)
{
    lv_theme_t *theme = lv_theme_night_init(30, nullptr);
    lv_theme_set_current(theme);

    auto root_top = lv_disp_get_scr_act(disp_top);
    auto root_bottom = lv_disp_get_scr_act(disp_bot);

    lv_obj_set_style(root_bottom, theme->style.scr);
    lv_obj_set_style(root_top, theme->style.scr);

    create_footer_top(root_top);
    create_header_bottom(root_bottom);

}

void create_footer_top(lv_obj_t *root_top) {
    auto footer = lv_cont_create(root_top, nullptr);

    auto default_footer_style = lv_cont_get_style(footer, LV_CONT_STYLE_MAIN);
    auto *padding_style = new lv_style_t;
    lv_style_copy(padding_style, default_footer_style);
    padding_style->body.padding.top = 1;
    lv_cont_set_style(footer, LV_CONT_STYLE_MAIN, padding_style);


    lv_cont_set_fit4(footer, LV_FIT_FLOOD, LV_FIT_FLOOD, LV_FIT_TIGHT, LV_FIT_NONE);
    lv_obj_align(footer, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    lv_obj_t * fade = lv_label_create(footer, nullptr);
    auto default_style = lv_label_get_style(fade, LV_LABEL_STYLE_MAIN);
    auto *fnt_style = new lv_style_t;
    lv_style_copy(fnt_style, default_style);
    fnt_style->text.font = &fnt;
    lv_label_set_style(fade, LV_LABEL_STYLE_MAIN, fnt_style);
    lv_label_set_text(fade, LV_SYMBOL_FADE);
    lv_obj_align(fade, nullptr, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    lv_obj_t * cut = lv_label_create(footer, nullptr);
    lv_label_set_style(cut, LV_LABEL_STYLE_MAIN, fnt_style);
    lv_label_set_text(cut, LV_SYMBOL_CUT);
    lv_obj_align(cut, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);

    lv_obj_t * time = lv_label_create(footer, nullptr);
    lv_label_set_text(time, get_timestamp().c_str());
    lv_obj_align(time, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    lv_cont_set_fit2(footer, LV_FIT_NONE, LV_FIT_TIGHT);

    lv_task_t *task = lv_task_create(update_time, 1000, LV_TASK_PRIO_LOW, time);

}

void create_header_bottom(lv_obj_t *root_bottom) {
    auto header = lv_cont_create(root_bottom, nullptr);
    auto default_header_style = lv_cont_get_style(header, LV_CONT_STYLE_MAIN);
    auto *padding_style = new lv_style_t;
    lv_style_copy(padding_style, default_header_style);
    padding_style->body.padding.bottom = 1;
    lv_cont_set_style(header, LV_CONT_STYLE_MAIN, padding_style);


    lv_cont_set_fit4(header, LV_FIT_FLOOD, LV_FIT_FLOOD, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_obj_align(header, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t * bat = lv_label_create(header, nullptr);

    auto default_style = lv_label_get_style(bat, LV_LABEL_STYLE_MAIN);
    auto *fnt_style = new lv_style_t;
    lv_style_copy(fnt_style, default_style);
    fnt_style->text.font = &fnt;
    lv_label_set_text(bat, LV_SYMBOL_BATTERY_EMPTY);
    lv_obj_align(bat, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    lv_obj_t * wifi = lv_label_create(header, nullptr);
    lv_label_set_style(wifi, LV_LABEL_STYLE_MAIN, fnt_style);
    lv_label_set_text(wifi, LV_SYMBOL_WIFI_0);
    lv_obj_align(wifi, nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

    wifi_n_bat *wnb;
    wnb = (wifi_n_bat *)malloc(sizeof(*wnb));
    wnb->bat = bat;
    wnb->wifi = wifi;


    lv_task_t *task = lv_task_create(update_wifibat, 1000, LV_TASK_PRIO_LOW, wnb);
}

void update_time(lv_task_t *task)
{
    auto time = (lv_obj_t *)task->user_data;
    lv_label_set_text(time, get_timestamp().c_str());
}

void update_wifibat(lv_task_t *task)
{
    auto objs = static_cast<wifi_n_bat *>(task->user_data);
    u8 bat_lvl, wifi_str;
    PTMU_GetBatteryLevel(&bat_lvl);
    wifi_str = osGetWifiStrength();
    if (strcmp(lv_label_get_text(objs->wifi), wifi_str_t[wifi_str].c_str()))
        lv_label_set_text(objs->wifi, wifi_str_t[wifi_str].c_str());
    if (strcmp(lv_label_get_text(objs->bat), bat_lvl_t[bat_lvl].c_str()))
        lv_label_set_text(objs->bat, bat_lvl_t[bat_lvl].c_str());
}
