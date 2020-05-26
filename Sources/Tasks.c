#include "PE_Types.h"
#include "PE_Error.h"
#include "Tasks.h"
#include "CAN1.h"
#include "PWM_WL.h"
#include "PWM_BL.h"
#include "MC.h"
#include "appGauge.h"
#include "stdio.h"
#include "SSD.h"
#define MAX_POS 57500U
#define CAL_ID 0x7AAU
#define CAL_PAYLOAD 7
#define MAX_CAL_IDX (uint8_t)(sizeof(CalData_t) / CAL_PAYLOAD + 1)

CalData_t calData;
CalData_t calDataUp;
uint16_t stepperPosMax = MAX_POS;

void DataMgnrTask(void)
{
    dword messageId;
    byte frameType, frameFormat, length;
    byte data[8];
    uint8_t update = 0;
    if (CAN1_ReadFrame(&messageId, &frameType, &frameFormat, &length, data) == ERR_OK)
    {
        if (messageId == calData.id)
        {
            SetSignalValue(data, &calData);
        }
        else if (messageId == CAL_ID)
        {
            uint8_t idx = data[0];
            uint8_t len = sizeof(CalData_t) - idx * CAL_PAYLOAD >= CAL_PAYLOAD ? CAL_PAYLOAD : sizeof(CalData_t) - idx * CAL_PAYLOAD;
            memcpy((void *)(&calDataUp + CAL_PAYLOAD * idx), (void *)(&data[1]), len);
            if (idx == MAX_CAL_IDX)
            {
                update = 1;
            }
        }
    }
    CalDataStore(&calDataUp, update);
}

void IluCtrlTask(void)
{
    uint8_t duty;
    uint16_t signalValue = GetSignalValue();
    if (signalValue > calData.warning_threshold)
    {
        duty = calData.warning_brightness;
    }
    else
    {
        duty = 0;
    }
    PWM_WL_SetRatio8(duty);
}

void StepperTask(void)
{
    uint8_t trg_spd;
    uint16_t deltaDestPos;
    if(MC_StepperStopped(0)){
		uint16_t curPos = MC_GetMotorPosition(0);
		uint16_t signalValue = GetSignalValue();
		uint32_t tmp = (uint32_t)stepperPosMax * (uint32_t)(signalValue - calData.signal_min);
		uint16_t dest = tmp / (calData.signal_max - calData.signal_min);
	
		if (dest > curPos)
		{
			deltaDestPos = dest - curPos;
		}
		else
		{
			deltaDestPos = curPos - dest;
		}
		if (deltaDestPos < (MAX_POS / 100))
		{
			trg_spd = 4 * calData.speed;
		}
		else if (deltaDestPos < (MAX_POS / 32))
		{
			trg_spd = 2 * calData.speed;
		}
		else
		{
			trg_spd = calData.speed;
		}
		MC_SetMotorSpeed(0, trg_spd);
		MC_SetMotorPosition(0, dest);
    }
}

void InitTask(void)
{
	AppInit(&calData);
    PWM_BL_SetRatio8(calData.backlight_brightness);

}
