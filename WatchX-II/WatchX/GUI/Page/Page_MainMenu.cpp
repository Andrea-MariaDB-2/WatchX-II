#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"

/*��ҳ�洰��*/
static lv_obj_t* appWindow;

static lv_task_t* taskTimeUpdate;
static lv_task_t* taskLabelsUpdate;

static lv_obj_t* contGrp[3];

static lv_obj_t* labelTimeHour;
static lv_obj_t* labelTimeMinute;

static lv_obj_t* labelTemp;
static lv_obj_t* labelSteps;
static lv_obj_t* labelBatt;
static lv_obj_t* labelDate;

static void ContGrp_Creat(lv_obj_t* par)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_shadow_width(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_shadow_ofs_x(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_shadow_ofs_y(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_shadow_blend_mode(&style, LV_STATE_DEFAULT, LV_BLEND_MODE_SUBTRACTIVE);
    //lv_style_set_shadow_spread(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_shadow_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_border_width(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 30);
    
    lv_obj_t* cont = lv_cont_create(par, NULL);
    lv_obj_set_size(cont, 212, 215);
    lv_obj_align(cont, NULL, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_set_style_local_border_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_obj_set_style_local_shadow_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_obj_add_style(cont, LV_CONT_PART_MAIN, &style);
    contGrp[2] = cont;
    
    cont = lv_cont_create(contGrp[2], NULL);
    lv_obj_set_size(cont, 167, 182);
    lv_obj_align(cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    
    lv_obj_set_style_local_border_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
    lv_obj_set_style_local_shadow_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
    lv_obj_add_style(cont, LV_CONT_PART_MAIN, &style);
    contGrp[1] = cont;
    
    cont = lv_cont_create(contGrp[1], NULL);
    lv_obj_set_size(cont, 131, 155);
    lv_obj_align(cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    
    lv_obj_set_style_local_border_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_obj_set_style_local_shadow_color(cont, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_obj_add_style(cont, LV_CONT_PART_MAIN, &style);
    contGrp[0] = cont;
}

static void Labels_Update(lv_task_t* task)
{
    IMU_Update();
    lv_label_set_text_fmt(labelSteps, "%d", IMU_GetSteps());
}

static void Labels_Creat(lv_obj_t* par1, lv_obj_t* par2)
{
    LV_FONT_DECLARE(FONT_ERASDEMI_25);
    
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, LV_STATE_DEFAULT, &FONT_ERASDEMI_25);
    
    lv_obj_t* label = lv_label_create(par1, NULL);
    lv_label_set_text(label, "24C");
    lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_set_auto_realign(label, true);
    labelTemp = label;
    
    label = lv_label_create(par2, NULL);
    lv_label_set_text(label, "-");
    lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_set_auto_realign(label, true);
    labelSteps = label;
    
    lv_task_t* task = lv_task_create(Labels_Update, 1000, LV_TASK_PRIO_MID, NULL);
    Labels_Update(task);
    taskLabelsUpdate = task;
}

static void LabelTime_Update(lv_task_t* task)
{
    RTC_Get();
    lv_label_set_text_fmt(labelTimeHour, "%02d", calendar.min);
    lv_label_set_text_fmt(labelTimeMinute, "%02d", calendar.sec);
}

static void LabelTime_Creat(lv_obj_t* par)
{
    LV_FONT_DECLARE(FONT_ERASBD_64);
    
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, LV_STATE_DEFAULT, &FONT_ERASBD_64);
    
    lv_obj_t* label = lv_label_create(par, NULL);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);
    lv_obj_set_auto_realign(label, true);
    lv_obj_add_style(label, LV_CONT_PART_MAIN, &style);
    labelTimeHour = label;
    
    label = lv_label_create(par, NULL);
    lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
    lv_obj_set_auto_realign(label, true);
    lv_obj_add_style(label, LV_CONT_PART_MAIN, &style);
    labelTimeMinute = label;
    
    lv_task_t* task = lv_task_create(LabelTime_Update, 500, LV_TASK_PRIO_MID, NULL);
    LabelTime_Update(task);
    taskTimeUpdate = task;
}

/**
  * @brief  ҳ���ʼ���¼�
  * @param  ��
  * @retval ��
  */
static void Setup()
{
    /*����ҳ���Ƶ�ǰ̨*/
    lv_obj_move_foreground(appWindow);
    
    ContGrp_Creat(appWindow);
    
    LabelTime_Creat(contGrp[0]);
    
    Labels_Creat(contGrp[1], contGrp[2]);
}

/**
  * @brief  ҳ���˳��¼�
  * @param  ��
  * @retval ��
  */
static void Exit()
{
    lv_task_del(taskTimeUpdate);
    lv_task_del(taskLabelsUpdate);
    
    lv_obj_clean(appWindow);
}

/**
  * @brief  ҳ���¼�
  * @param  btn:�����¼��İ���
  * @param  event:�¼����
  * @retval ��
  */
static void Event(void* btn, int event)
{
}

/**
  * @brief  ҳ��ע��
  * @param  pageID:Ϊ��ҳ������ID��
  * @retval ��
  */
void PageRegister_MainMenu(uint8_t pageID)
{
    /*��ȡ�������ҳ��Ĵ���*/
    appWindow = AppWindow_GetCont(pageID);
    
    /*ע����ҳ�������*/
    page.PageRegister(pageID, Setup, NULL, Exit, Event);
}
