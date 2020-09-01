#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "BSP/BSP.h"

#define USE_FPS_TEST 0

/*ʵ������Ļ����*/
SCREEN_CLASS screen(
    TFT_PORT_Pin, TFT_RES_Pin, TFT_CS_Pin,
    TFT_RS_Pin, TFT_WR_Pin, TFT_RD_Pin
);

/*ʵ����ҳ�������*/
PageManager page(PAGE_MAX);

/*ҳ��ע����*/
#define PAGE_REG(name)\
do{\
    extern void PageRegister_##name(uint8_t pageID);\
    PageRegister_##name(PAGE_##name);\
}while(0)

#if (USE_FPS_TEST == 1) 
static void Display_FPSTest();
#endif

/**
  * @brief  ҳ���ʼ��
  * @param  ��
  * @retval ��
  */
static void Pages_Init()
{
    PAGE_REG(MainMenu);          //���˵�
    
    page.PagePush(PAGE_MainMenu);//�򿪱���
}

extern "C" {
    void lv_demo_benchmark(void);
    void lv_demo_widgets(void);
    void lv_demo_stress(void);
}

/**
  * @brief  ��ʾ��ʼ��
  * @param  ��
  * @retval ��
  */
void Display_Init()
{
    /*����ر�*/
    Backlight_Init();
    Backlight_SetValue(0);
    
    /*��Ļ��ʼ��*/
    screen.begin();
    screen.setRotation(0);
    screen.fillScreen(screen.Black);
    
#if (USE_FPS_TEST == 1)
    Display_FPSTest();
#endif
    
    /*�Զ������ʼ��*/
    DisplayError_Init();
    
    /*lvgl��ʼ��*/
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    
    /*APP���ڳ�ʼ��*/
    AppWindow_Creat();
    
    /*ҳ���ʼ��*/
    Pages_Init();
    
    /*���⽥��*/
    Backlight_SetGradual(Backlight_GetBKP(), 1000);
    
    //lv_demo_benchmark();
    //lv_demo_stress();
    //lv_demo_widgets();
}

/**
  * @brief  ��ʾ����
  * @param  ��
  * @retval ��
  */
void Display_Update()
{
    lv_task_handler();
    page.Running();
}

/**
  * @brief  ҳ��������ʱ������lvgl����
  * @param  ��
  * @retval ��
  */
void PageDelay(uint32_t ms)
{
    uint32_t lastTime = millis();
    while(millis() - lastTime <= ms)
    {
        lv_task_handler();
    }
}

#if (USE_FPS_TEST == 1) 
static void Display_FPSTest()
{
    float Ftime, Ltime;
    float FPS;
    Ftime = millis();
    int i;
    for(i = 100; i > 0; i--)
    {
        screen.fillScreen(screen.Black);
        screen.fillScreen(screen.White);
    }
    Ltime = millis() - Ftime;
    FPS = 100.0f / (Ltime / 1000.0f) * 2.0f;
    screen.fillScreen(screen.Blue);
    screen.setTextSize(1);
    screen.setTextColor(screen.White);
    screen.setCursor(0, 0);
    screen.print(Ltime);
    screen.setCursor(45, 0);
    screen.print("ms");
    screen.setCursor(0, 9);
    screen.print("FPS:");
    screen.setCursor(25, 9);
    screen.print(FPS);
    while(1);
}
#endif
