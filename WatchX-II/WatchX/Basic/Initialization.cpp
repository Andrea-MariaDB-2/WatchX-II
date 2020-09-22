#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"

/**
  * @brief  ������ʼ��
  * @param  ��
  * @retval true�ɹ� falseʧ��
  */
static bool Value_Init()
{
    return true;
}


/**
  * @brief  �ֱ��ʼ��
  * @param  ��
  * @retval ��
  */
void WatchX_Init()
{
    Serial.begin(115200);
    Serial.println("\r\n"WX_NAME" Hardware:"WX_HARDWARE_VERSION" Software:"WX_SOFTWARE_VERSION" "__DATE__" Build");
    Value_Init();
    //I2C_Scan(true);
    I2Cx_Init(I2C2, 100 * 1000);
    IMU_Init();
    //ParticleSensor_Init();
    
    RTC_Init();
    RTC_Set(2020, 9, 20, 0, 15, 55);
    //SD_Init();
}
