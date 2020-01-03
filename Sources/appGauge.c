
#include "appGauge.h"
#include "IEE1.h"
#include "PWM_BL.h"
#include "PWM_WL.h"
#include "MC.h"

volatile static uint16_t signalValue = 0;

void CalDataLoad(CalData_t *cal)
{
    uint8_t idx;
    uint8_t dataByte;
    for (idx = 0; idx < sizeof(CalData_t); idx++)
    {
        IEE1_GetByte(IEE1_AREA_START + idx, &dataByte);
        *(byte *)(cal + idx) = dataByte;
    }
    cal->id = 0x6a;
    cal->speed = 2;
    cal->bitmask[0] = 0x0f;
    cal->bitmask[1] = 0xf0;
    cal->offset = 12;
    cal->signal_min = 0;
    cal->signal_max = 127;
    cal->warning_threshold = 100;
    cal->warning_brightness = 100;
    cal->backlight_brightness = 100;
}

void CalDataStore(CalData_t *cal, uint8_t update)
{
    static uint8_t writerState = 0;
    static uint8_t idx;
    uint8_t dataByte;
    if (writerState == 0 /*IDLE*/)
    {
        if (update)
        {
            idx = 0;
            writerState = 1;
        }
    }
    else if (writerState == 1)
    {
        if (idx < sizeof(CalData_t))
        {
            if (!IEE1_Busy())
            {
                dataByte = *(byte *)(cal + idx);
                IEE1_SetByte(IEE1_AREA_START + idx, dataByte);
                idx++;
            }
        }
        else
        {
            writerState = 0;
        }
    }
}

uint16_t GetSignalValue(void)
{
    return signalValue;
}
void SetSignalValue(uint8_t *rawData, CalData_t *cal)
{
    uint32_t sum = 0;
    uint8_t i;
    uint8_t len = cal->offset/8;
    for (i = 0; i <= len; i++)
    {
            uint8_t tmp = *(rawData + i) & cal->bitmask[i];
            sum += tmp << ((len-i) * 8);
    }
    signalValue = (uint16_t)sum>>(cal->offset-len*8);
}
