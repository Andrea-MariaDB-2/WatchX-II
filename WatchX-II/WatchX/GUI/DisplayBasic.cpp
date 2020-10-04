#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"

#ifdef ARDUINO

#define USE_FPS_TEST 0

/*ʵ������Ļ����*/
SCREEN_CLASS screen(
    TFT_PORT_Pin, TFT_RES_Pin, TFT_CS_Pin,
    TFT_RS_Pin, TFT_WR_Pin, TFT_RD_Pin
);

#if (USE_FPS_TEST == 1) 
static void Display_FPSTest();
#endif



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
    lv_port_log_init();
    
    /*APP���ڳ�ʼ��*/
    AppWindow_Create();
    
    /*ҳ���ʼ��*/
    DisplayPage_Init();
    
    /*���⽥��*/
    Backlight_SetGradual(Backlight_GetBKP(), 100);
    
    //lv_demo_benchmark();
    //lv_demo_stress();
    //lv_demo_widgets();
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

#else

void Display_Init()
{
    /*APP���ڳ�ʼ��*/
    AppWindow_Create();

    /*ҳ���ʼ��*/
    DisplayPage_Init();
}

#endif
