#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"

/*��ҳ�洰��*/
static lv_obj_t* appWindow;

static lv_obj_t* labelTime;
static lv_task_t* taskTimeUpdate;

static void LabelTime_Update(lv_task_t* task)
{
    RTC_Get();
    lv_label_set_text_fmt(labelTime, "%02d:%02d:%02d", calendar.hour, calendar.min, calendar.sec);
}

static void LabelTime_Creat(lv_obj_t* par)
{
    lv_obj_t* label = lv_label_create(par, NULL);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_auto_realign(label, true);
    
    lv_task_t* task = lv_task_create(LabelTime_Update, 500, LV_TASK_PRIO_MID, NULL);
    
    labelTime = label;
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
    
    LabelTime_Creat(appWindow);
}

/**
  * @brief  ҳ���˳��¼�
  * @param  ��
  * @retval ��
  */
static void Exit()
{
    lv_task_del(taskTimeUpdate);
    
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
