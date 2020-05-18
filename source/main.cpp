#include "main.h"
#include "graphics/setcontent.h"


Logger logger("192.168.1.108", 8090);

int main(int argc, char **argv) {
    logger.log("startup", "Arg count: " + std::to_string(argc) + "\n");
    for (int i = 0; i < argc; i++)
        logger.log("startup", "Arg №" + std::to_string(i) + ": " + std::string(argv[i]) + "\n");
    gfxInitDefault();
    ptmuInit();


    logger.log("main", "Hello there!\n");
//    logger.disable();
    hidScanInput();

    lv_disp_t *disp_bot, *disp_top;
    lv_indev_t *touchscreen;
    initdisplays(&disp_bot, &disp_top, &touchscreen);

//    lv_test_theme_2();
//    lv_obj_t * btn1 = lv_btn_create(lv_disp_get_scr_act(disp_top), NULL);             /*Add to the active screen*/
//    lv_obj_set_pos(btn1, 0, 0);                                    /*Adjust the position*/

    setcontent(disp_bot, disp_top);


    while(aptMainLoop()) {
        hidScanInput();
//        if(hidKeysDown() & KEY_START) {
//            break;
//        }

        lv_task_handler();
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    ptmuExit();
    gfxExit();
    return 0;
}

//        u8 snd;
//        HIDUSER_GetSoundVolume(&snd);
//        logger.log("sound", std::to_string(snd) + "\n");
//        logger.log("3dslider", std::to_string((*(volatile float*)0x1FF81080)) + "\n");


//    gfxSetDoubleBuffering(GFX_BOTTOM, false);
//    gfxSetDoubleBuffering(GFX_TOP, false);
//    gfxSetScreenFormat(GFX_BOTTOM, GSP_RGBA8_OES);
//    gfxSetScreenFormat(GFX_TOP, GSP_RGBA8_OES);

//    static auto src_buf = (lv_color_t*) linearAlloc(320*240);
//    memset(src_buf, 0xFF, 320*240*32);

//    static auto dest_buf = (lv_color_t*) linearAlloc(320*240*32);
//    memset(dest_buf, 0x00, 320*240*32);

//    logger.ok("nomemfill", std::to_string(((u32*)src_buf)[0]) + "\n");


//    GSPGPU_AcquireRight(0);
//    GSPGPU_SetLcdForceBlack(0);

//
//    //set subscreen to blue
//    u32 regData=0x01FF0000;
//    GSPGPU_WriteHWRegs(0x202A04, &regData, 4);

//    GSPGPU_FlushDataCache(dest_buf, 320*240*32);
//    GX_TextureCopy((u32*)src_buf, 0, (u32*)dest_buf, 0, 320*240,0x8);
//    gspWaitForPPF(); // somehow working (maybe)

//    GX_MemoryFill((u32*)src_buf, 0xFF000000, (u32*)&src_buf[320*240], GX_FILL_32BIT_DEPTH | GX_FILL_TRIGGER, nullptr, 0, nullptr, 0);
//    gspWaitForPSC0();
//    for (int i = 0; i < 320*240; i++)
//    {
//        logger.ok("memfill" + std::to_string(i), std::to_string(((u32*)src_buf)[i]) + "\n");
//    }

//    logger.log("is_double_buf_bot",std::to_string(lv_disp_is_true_double_buf(disp_bot)) + "\n");
//    logger.log("is_double_buf_top",std::to_string(lv_disp_is_true_double_buf(disp_top)) + "\n");
//    auto *arr = (lv_color_t *)(malloc(240 * 320 * 24));
//    memset(arr, 0xFF, 240*320*24);
//
//    lv_area_t area;
//    area.x1 = 0;
//    area.x2 = 320;
//    area.y1 = 0;
//    area.y2 = 240;
//    bool col = false;
//    while (aptMainLoop())
//    {
//        hidScanInput();
//        if(hidKeysDown() & KEY_START) {
//            break;
//        }
//        if (col)
//            memset(arr, 0xFF, 240*320*24);
//        else
//            memset(arr, 0x00, 240*320*24);
//        col = !col;
//
//        auto time = osGetTime();
//        disp_bot->driver.flush_cb(&(disp_bot->driver), &area, arr);
//        logger.log("gfxbench",std::to_string(1000 / (osGetTime() - time)) + "\n");
//        gfxFlushBuffers();
//        gfxSwapBuffers();
//        gspWaitForVBlank();
//    }
