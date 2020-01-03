#ifndef SYSCLK_H_
#define SYSCLK_H_
#include "PE_Types.h"

uint32_t Clock_GetTicks(void);
void Clock_IncTicks(void);
void Clock_Init(void);
#endif /*SYSCLK_H_*/
