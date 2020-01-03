/*
 * Stepper.h
 *
 *  Created on: Mar 6, 2012
 *      Author: B40150
 */

#ifndef MC_H_
#define MC_H_

/*******************************************************************************
* Includes
********************************************************************************/
#include "PE_Types.h"
#define MAX_MOTOR_NUM 1
/*******************************************************************************
* Types
********************************************************************************/

typedef struct
{
	uint32_t dummy;
	uint16_t pos;
	uint16_t desPos;
	uint8_t dir;
	uint8_t stopped;
	uint8_t speed;
	uint16_t ptrA;
	uint16_t ptrB;
	uint8_t rtz;
} MOTOR;

/*******************************************************************************
* Global Functions
********************************************************************************/
void MC_Init(void);
void Move_Stepper(void);
uint8_t MC_StepperStopped(uint8_t idx);
uint16_t MC_GetMotorPosition(uint8_t idx);
void MC_SetMotorPosition(uint8_t idx, uint16_t dp);
void MC_SetMotorSpeed(uint8_t idx, uint8_t s);

#endif /* MC_H_ */
