#include "FileGroup.h"
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
    Value_Init();
    //I2C_Scan(true);
    I2Cx_Init(I2C2, 100 * 1000);
    IMU_Init();
    //ParticleSensor_Init();
    
    RTC_Init();
    RTC_Set(20, 8, 31, 17, 53, 0);
    //SD_Init();
}
