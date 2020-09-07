#ifndef __DISPLAYPRIVATE_H
#define __DISPLAYPRIVATE_H

/*Basic*/
#include "Adafruit_ST7789/Adafruit_ST7789.h"

typedef Adafruit_ST7789 SCREEN_CLASS;

extern SCREEN_CLASS screen;

#define TEXT_HEIGHT_1   8
#define TEXT_WIDTH_1    6
#define TextSetDefault() screen.setTextColor(screen.White,screen.Black),screen.setTextSize(1)
#define TextMid(x,textnum) (screen.width()*(x)-(TEXT_WIDTH_1*(textnum))/2.0f)
#define TextMidPrint(x,y,text) screen.setCursor(TextMid(x,strlen(text)),screen.height()*(y)-TEXT_HEIGHT_1/2.0f),screen.print(text)
#define ScreenMid_W (screen.width()/2)
#define ScreenMid_H (screen.height()/2)

void DisplayError_Init();
void Display_Init();
void Display_Update();

/*Page*/
#include "PageManager/PageManager.h"
typedef enum
{
    /*����*/
    PAGE_NONE,
    /*�û�ҳ��*/
    PAGE_MainMenu,
    PAGE_DialPlate,
    /*����*/
    PAGE_MAX
} Page_Type;

extern PageManager page;
void PageDelay(uint32_t ms);

#define PAGE_EXPORT(name)\
void PageRegister_##name(uint8_t pageID)\
{\
    appWindow = AppWindow_GetCont(pageID);\
    page.PageRegister(pageID, Setup, NULL, Exit, Event);\
}

/*LittleVGL*/
#include "lvgl/lvgl.h"
#include "lv_label_anim_effect.h"

#define LV_ANIM_TIME_DEFAULT 200
#define LV_SYMBOL_DEGREE_SIGN   "\xC2\xB0"

void lv_port_disp_init();
void lv_port_indev_init();
bool lv_obj_del_safe(lv_obj_t** obj);
void lv_obj_set_opa_scale(lv_obj_t* obj, lv_opa_t opa);
lv_opa_t lv_obj_get_opa_scale(lv_obj_t* obj);
void lv_label_set_text_add(lv_obj_t * label, const char * text);
lv_coord_t lv_obj_get_x_center(lv_obj_t * obj);
lv_coord_t lv_obj_get_y_center(lv_obj_t * obj);
void lv_table_set_align(lv_obj_t * table, lv_label_align_t align);
void lv_obj_add_anim(
    lv_obj_t * obj, lv_anim_t * a,
    lv_anim_exec_xcb_t exec_cb, 
    int32_t start, int32_t end,
    uint16_t time = LV_ANIM_TIME_DEFAULT,
    lv_anim_ready_cb_t ready_cb = NULL,
    lv_anim_path_cb_t path_cb = lv_anim_path_ease_in_out
);
#define LV_OBJ_ADD_ANIM(obj,attr,target,time)\
do{\
    lv_obj_add_anim(\
        (obj), NULL,\
        (lv_anim_exec_xcb_t)lv_obj_set_##attr,\
        lv_obj_get_##attr(obj),\
        (target),\
        (time)\
    );\
}while(0)

/*AppWindow*/
void AppWindow_Creat();
lv_obj_t * AppWindow_GetCont(uint8_t pageID);
lv_coord_t AppWindow_GetHeight();
lv_coord_t AppWindow_GetWidth();
#define APP_WIN_HEIGHT AppWindow_GetHeight()
#define APP_WIN_WIDTH  AppWindow_GetWidth()

#endif
