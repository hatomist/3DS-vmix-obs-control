#include <3ds.h>
#include "initdisplays.h"
#include "../logger/Logger.h"
#include <citro3d.h>

extern Logger logger;

void simple_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    u16 x, y;


    for (y = area->y1; y <= area->y2; y++) {
        for (x = area->x1; x <= area->x2; x++) {
            ((u32*)(disp_drv->user_data))[x*disp_drv->ver_res+(disp_drv->ver_res - 1 - y)] = (color_p++->full << 8);
        }
    }

    lv_disp_flush_ready(disp_drv);
}

bool simple_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data)
{

    touchPosition touch;
    hidTouchRead(&touch);

    data->point.x = touch.px;
    data->point.y = touch.py;
    data->state = (LV_INDEV_STATE_PR && data->point.x && data->point.y);
    return false; /*No buffering now so no more data read*/
}

void lv_log (lv_log_level_t level, const char * path, uint32_t line, const char * msg)
{
    if (level == LV_LOG_LEVEL_ERROR)
        logger.error("lvgl", msg);
    else if (level == LV_LOG_LEVEL_WARN)
        logger.warning("lvgl", msg);
    else if (level == LV_LOG_LEVEL_INFO)
        logger.ok("lvgl", msg);
    else logger.log("lvgl", msg);
    logger.log("\n");
};

void monitor_cb(lv_disp_drv_t *disp_drv, u32 time, u32 px)
{
    logger.log("gfx", "Redrawed " + std::to_string(px) + "px in " + std::to_string(time) + "ms\n");
    logger.log("time", get_timestamp() + "\n");
}

void initdisplays(lv_disp_t **bot, lv_disp_t **top, lv_indev_t **touchscreen)
{
    gfxSetDoubleBuffering(GFX_BOTTOM, false);
    gfxSetDoubleBuffering(GFX_TOP, false);
    gfxSetScreenFormat(GFX_BOTTOM, GSP_RGBA8_OES);
    gfxSetScreenFormat(GFX_TOP, GSP_RGBA8_OES);
    u16 w, h;

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);


    lv_init();

    lv_log_register_print_cb(lv_log);

    lv_disp_drv_t disp_bot_drv, disp_top_drv;
    lv_disp_drv_init(&disp_bot_drv);
    lv_disp_drv_init(&disp_top_drv);

    static lv_disp_buf_t disp_bot_buf, disp_top_buf;

    auto fb_bot = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, &w, &h);
    const auto bot_h = h;
    const auto bot_w = w;
    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t *buf_bot_1 = (lv_color_t *)linearAlloc(320*240*4);
    static lv_color_t *buf_bot_2 = (lv_color_t *)linearAlloc(320*240*4);
    lv_disp_buf_init(&disp_bot_buf, buf_bot_1, buf_bot_2, bot_h * bot_w);
    disp_bot_drv.hor_res = h;
    disp_bot_drv.ver_res = w;
    disp_bot_drv.rotated = 0;
    disp_bot_drv.user_data = fb_bot;
    disp_bot_drv.monitor_cb = monitor_cb;
    disp_bot_drv.buffer = &disp_bot_buf;
    disp_bot_drv.flush_cb = simple_flush_cb;
//    disp_bot_drv.gpu_fill_cb = gpu_fill;
    *bot = lv_disp_drv_register(&disp_bot_drv);

    auto fb_top = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, &w, &h);
    static lv_color_t *buf_top_1 = (lv_color_t *)linearAlloc(400*240*4);
    static lv_color_t *buf_top_2 = (lv_color_t *)linearAlloc(400*240*4);
    lv_disp_buf_init(&disp_top_buf, buf_top_1, buf_top_2, 400 * 240);
    disp_top_drv.hor_res = h;
    disp_top_drv.ver_res = w;
    disp_top_drv.rotated = 0;
    disp_top_drv.user_data = fb_top;
    disp_top_drv.monitor_cb = monitor_cb;
    disp_top_drv.buffer = &disp_top_buf;
    disp_top_drv.flush_cb = simple_flush_cb;
    *top = lv_disp_drv_register(&disp_top_drv);
//    logger.log("IsDB" , std::to_string(lv_disp_is_true_double_buf(*top)) + "\n");

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = simple_input_read;
    *touchscreen = lv_indev_drv_register(&indev_drv);
}



//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                     const lv_area_t * fill_area, lv_color_t color)
//{
//    int32_t y;
//    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/
//
////    GX_MemoryFill((u32*)dest_buf, 0xFFFFFF00, (u32*)dest_buf+1, GX_FILL_TRIGGER | GX_FILL_32BIT_DEPTH, NULL, 0, NULL, 0);
//
//    GSPGPU_FlushDataCache(dest_buf, disp_drv->ver_res*disp_drv->hor_res*4);
//
//    for(y = fill_area->y1; y <= fill_area->y2; y++) {
//        GX_MemoryFill((u32*)&dest_buf[fill_area->x1], color.full, (u32*)&dest_buf[fill_area->x2], GX_FILL_32BIT_DEPTH | GX_FILL_TRIGGER, nullptr, 0, nullptr, 0);
//        gspWaitForPSC0();
//        dest_buf+=dest_width;    /*Go to the next line*/
//    }
//
//}
//
//
//static void gpu_fill_example(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//                     const lv_area_t * fill_area, lv_color_t color)
//{
//    /*It's an example code which should be done by your GPU*/
//    int32_t x, y;
//    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/
//
//    for(y = fill_area->y1; y <= fill_area->y2; y++) {
//        GX_MemoryFill((u32*)&dest_buf[fill_area->x1], 0, (u32*)&dest_buf[fill_area->x1], GX_FILL_TRIGGER | GX_FILL_32BIT_DEPTH, nullptr, 0, nullptr, 0);
////        for(x = fill_area->x1; x <= fill_area->x2; x++) {
////            dest_buf[x] = color;
////        }
//        dest_buf+=dest_width;    /*Go to the next line*/
//        gspWaitForPSC0();
//    }
//}
