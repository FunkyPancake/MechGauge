#ifndef APP_GAUGE_H_
#define APP_GAUGE_H_

#include "PE_Types.h"
typedef struct
{
	uint32_t id;
	uint8_t bitmask[8];
	uint8_t offset;
	uint8_t speed;
	uint16_t signal_min;
	uint16_t signal_max;
	uint16_t warning_threshold;
	uint8_t warning_brightness;
	uint8_t backlight_brightness;
} CalData_t;
void CalDataStore(CalData_t *cal, uint8_t update);
void CalDataLoad(CalData_t *cal);
void SetSignalValue(uint8_t *rawData, CalData_t *cal);
uint16_t GetSignalValue(void);
#endif /*APP_GAUGE_H_*/
