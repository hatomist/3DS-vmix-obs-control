#ifndef INC_3DSBUILDTEMPLATE_SETCONTENT_H
#define INC_3DSBUILDTEMPLATE_SETCONTENT_H

#define LV_SYMBOL_WIFI_0 "\xEF\x9A\xAC"
#define LV_SYMBOL_WIFI_1 "\xEF\x9A\xAA"
#define LV_SYMBOL_WIFI_2 "\xEF\x9A\xAB"
#define LV_SYMBOL_WIFI_3 "\xEF\x87\xAB"
#define LV_SYMBOL_CAMCORDER "\xEF\x80\xBD"
#define LV_SYMBOL_CAMMOVIE "\xEF\xA2\xA9"
#define LV_SYMBOL_CAMWEB "\xEF\xA3\xBE"
#define LV_SYMBOL_CAMCCTV "\xEF\xA2\xAC"
#define LV_SYMBOL_HEADSET "\xEF\x96\x90"
#define LV_SYMBOL_CUT "\xEF\x83\x84"
#define LV_SYMBOL_FADE "\xEF\x80\x97"
#define LV_SYMBOL_VOLUME0 "\xEF\x80\xA6"
#define LV_SYMBOL_VOLUME1 "\xEF\x80\xA7"
#define LV_SYMBOL_VOLUME2 "\xEF\x9A\xA8"
#define LV_SYMBOL_VOLUME3 "\xEF\x80\xA8"





#include <lvgl.h>

void setcontent(lv_disp_t *disp_bot, lv_disp_t *disp_top);
void create_footer_top(lv_obj_t *root_top);
void create_header_bottom(lv_obj_t *root_bottom);
void update_time(lv_task_t *task);
void update_wifibat(lv_task_t *task);

#endif //INC_3DSBUILDTEMPLATE_SETCONTENT_H
