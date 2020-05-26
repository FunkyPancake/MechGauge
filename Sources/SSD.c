/*
 * Stepper.c
 *
 *  Created on: Mar 6, 2012
 *      Author: 
 */

#include "SSD.h"
#include "IO_Map.h"
#include "MC.h"
#include "PE_Types.h"
#include "Vssd0.h"
/******************************************************************************
* External objects
******************************************************************************/
extern MOTOR Motor[MAX_MOTOR_NUM];

/******************************************************************************
* Global variables
******************************************************************************/
uint8_t All_Motors_Stalled = 0; /* Used to register Motors Condition for SSD logic */

/******************************************************************************
* Local types
******************************************************************************/
typedef struct
{
	uint8_t u8_SSD_on;			   /* Signifies whether SSD should be on or off.        */
	int8_t i8_result;			   /* Holds result of stall detection function.         */
	int8_t i8_SSD_stage;		   /* 0==init,1==step/blank,2==intgration,3==evaluation.*/
	int8_t i8_clockwise;		   /* Indicate motor's relative rotational direction.   */
	int8_t i8_step_state;		   /* Tracks the 4 possible step states.                */
	uint16_t u16_blanking_count;   /* Specifies blanking duration.                      */
	uint16_t u16_integration_time; /* Specifies integration duration.                   */
	int16_t i16_integrated_value;  /* Stores back EMF integrated value.                 */
	int16_t i16_stall_level;	   /* Stores the stall threshold level.                 */
	int16_t i16_step_position;	   /* Tracks step position.                             */
	int16_t i16_last_stall;		   /* Stores the last detected stall value.             */
} TypeSSD;

/******************************************************************************
* Local variables
******************************************************************************/
TypeSSD SSD[MAX_MOTOR_NUM];

/******************************************************************************
* Global functions
******************************************************************************/

void SSD_Init(void)
{
	uint8_t i = 0;

	for (i = 0; i < MAX_MOTOR_NUM; i++)
	{
		SSD[i].i8_SSD_stage = 0;
		SSD[i].u16_integration_time = 1000;
		SSD[i].i16_stall_level = 1000;
		SSD[i].u16_blanking_count = 150;
		SSD[i].i8_step_state = 0;
		SSD[i].i8_clockwise = 0; //All RTZ CCW
		SSD[i].i16_step_position = 0;
		SSD[i].u8_SSD_on = 1;
	}

	/*Motor 0*/
	SSD0FLG_MCZIF = 1; //Clear modulus counter unterflow flag
	MDC0CTL_MCZIE = 1; //Enable modulus counter underflow interrupt
	MDC0CTL_MODMC = 0; //Modulus counter counts down to zero and stops
	SSD0FLG_AOVIF = 0; //Clear Accumulator overflow interrupt flag
	MDC0CTL_MCEN = 1;  //Modulus down counter enable
	MDC0CNT = 31000;
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(SSD0Isr)
{

	uint8_t M0_Int_Loop_Active = 1;

	/* Disable SSDx interrupt */
	MDC0CTL_MCZIE = 0;

	while (M0_Int_Loop_Active)
	{
		/* STOP SSD */
		if (SSD[0].u8_SSD_on == 0)
		{
			MDC0CTL_MCEN = 0;		 /* Disable modulus down-counter.              */
			RTZ0CTL_ITG = 0;		 /* Ensure integration disabled.               */
			RTZ0CTL_DCOIL = 0;		 /* Ensure Dcoils disabled.                    */
			RTZ0CTL_RCIR = 0;		 /* Disable recirculation.                     */
			SSD0CTL_SDCPU = 0;		 /* Power down the SSD sigma delta converter.  */
			SSD0CTL_RTZE = 0;		 /* Disable the SSD module. This also releases */
									 /* control of the associated port pins.       */
			SSD[0].i8_SSD_stage = 0; /* Set the stage var to 0.                    */
			return;					 /* Exit SSDx interrupt routine.               */
		}

		/* Since this CPU interrupt function may need a few requests in        */
		/* order to complete the process of performing a step with integration */
		/* and detecting a stall, the process is divided into stages.          */
		if (SSD[0].i8_SSD_stage == 0)
		{
			/***************INIT THE SDD MODULE SETTINGS**************/
			RTZ0CTL_RCIR = 0;		 /* Set recirculation to occur on low-side.                */
			RTZ0CTL_POL = 0;		 /* Set polarity.                                          */
			MDC0CTL_PRE = 0;		 /* Clear or set the SSD prescaler as desired              */
			SSD0CTL_ACLKS = 0;		 /* Setup SSD accumulator sample frequency. Recommended    */
									 /* sample frequencies are between 500Khz and 2Mhz.        */
			SSD0CTL_RTZE = 1;		 /* Enable SSD module. This also transfers control of the  */
									 /* associated port pins to the SSD module.                */
			SSD0CTL_SDCPU = 1;		 /* Power up the SSD sigma delta converter.                */
			SSD[0].i8_SSD_stage = 1; /* Since init complete, proceed to the next stage,        */
									 /* which is blanking/integration of the SSD step.         */
		}

		if (SSD[0].i8_SSD_stage == 1)
		{
			RTZ0CTL_STEP = SSD[0].i8_step_state; /* Write step state before performing a step. */
			SSD[0].i8_SSD_stage = 2;			 /* Set the next stage.                        */

			/******************IF BLANKING IS USED********************/
			/* In some cases, an application may work even when blanking is s*/
			/* not used. To skip blanking and go straight to integration,   */
			/* set the variable u16_blanking_count to 0.                        */
			if (SSD[0].u16_blanking_count > 0)
			{
				/*******************BEGIN TAKING A STEP***************************************/
				SSD0FLG_MCZIF = 1;					 /* Clear the modulus down counter zero flag.            */
				RTZ0CTL_ITG = 0;					 /* Ensure integration disabled before blanking.         */
				MDC0CTL_MCZIE = 1;					 /* Enable zero flag interrupt. When triggered, blanking */
													 /* is complete and the request proceeds to integration. */
				MDC0CTL_MODMC = 0;					 /* Set the modulus mode to 0.                           */
				MDC0CTL_MCEN = 1;					 /* Enable modulus down-counter.                         */
				MDC0CNT = SSD[0].u16_blanking_count; /* Load the blanking count.            */
				RTZ0CTL_DCOIL = 1;					 /* Turn on the SSD channel coil drivers.                */
				return;								 /* Exit SSDx interrupt routine.                         */
			}
		}

		if (SSD[0].i8_SSD_stage == 2)
		{
			/********************START INTEGRATION***********************/
			SSD0FLG_MCZIF = 1;					   /* Clear modulus down counter zero flag.                    */
			MDC0CTL_MCZIE = 1;					   /* Enable interrupts for zero flag.                         */
			MDC0CTL_MODMC = 0;					   /* Set mode to 0 to count down and stop at zero.            */
			SSD0FLG_AOVIF = 1;					   /* Clear the accumulator overflow flag.                     */
			MDC0CTL_MCEN = 1;					   /* Enable modulus counter. Count value is loaded next.      */
			MDC0CNT = SSD[0].u16_integration_time; /* Load the integration count.                 */

			/* NOTE: If integration is enabled before the modulus counter is set up,       */
			/* the SSD module may not perform offset cancelation. This increases           */
			/* the possibility of large offset errors corrupting the integration value.    */
			/* It is recommended to enable integration AFTER the modulus counter has       */
			/* been setup and enabled.                                                     */

			RTZ0CTL_ITG = 1;		 /* Begin integration.                                     */
			RTZ0CTL_DCOIL = 1;		 /* Turn on the SSD channel coil drivers.                  */
			SSD[0].i8_SSD_stage = 3; /* Set next stage to evaluate integration result.         */
			return;					 /* Exit interrupt. Integration complete at next request.  */
		}

		if (SSD[0].i8_SSD_stage == 3)
		{
			/*************READ ITGACC & DISABLE INTEGRATION**************/
			SSD[0].i16_integrated_value = ITG0ACC; /* Immediately get the integration result                */
			RTZ0CTL_ITG = 0;					   /* Accumulator still active. Clear ITG to disable.                     */
			SSD0FLG_MCZIF = 1;					   /* Clear MCZIF flag.                                                   */
			RTZ0CTL_DCOIL = 0;					   /* Disable Dcoil. To leave Dcoil enabled, comment out this instruction.*/
			MDC0CTL_MCEN = 0;					   /*  Disable modulus down-counter.                                      */

			/* NOW THAT INTEGRATION HAS COMPLETED, EVALUATE THE RESULT  */
			/************1ST, CHECK FOR ACCUMULATOR OVERFLOW*************/
			if (SSD0FLG_AOVIF == 1)
			{
				/* If an overlow occurs, the routine must determine what to do.    */
				/* In this instance, the routine flags a variable for SSDx disable.*/
				SSD[0].i8_result = 2; /* Overflow detected. Write result variable.      */
				SSD[0].u8_SSD_on = 0; /* Disable the SSDx module                        */
			}
			/*********CHECK IF INTEGRATION VALUE IN STALL RANGE**********/
			else if (((SSD[0].i16_integrated_value <= SSD[0].i16_stall_level) && (SSD[0].i16_integrated_value >= 0)) ||
					 ((SSD[0].i16_integrated_value >= (-SSD[0].i16_stall_level)) && (SSD[0].i16_integrated_value <= 0)))
			{
				SSD[0].i8_result = 1;								 /* Write result code to indicate stall detected.          */
				SSD[0].i16_last_stall = SSD[0].i16_integrated_value; /* Save integration stall value   */
				/*******SINCE STALL DETECTED, REVERSE MOTOR DIRECTION*******/
				All_Motors_Stalled |= 1; /* Register Motor Stall to module interface */
				Motor[0].rtz = 1;

				/* Disable RTZ */
				SSD0CTL_RTZE = 0;
				return; /* Exit interrupt routine. */
			}
			else
			{
				SSD[0].i8_result = 0; /* No stall detected. Write result code. */
				/******************MOVE TO NEXT STEP STATE******************/
				if (SSD[0].i8_clockwise)
				{
					SSD[0].i16_step_position++;
					SSD[0].i8_step_state++; /* Update to rotate(CCW) through future steps. Direction */
											/* dependent upon MCU pin connections to the motor.      */
					if (SSD[0].i8_step_state > 3)
						SSD[0].i8_step_state = 0;
				}
				else
				{
					SSD[0].i16_step_position--;
					SSD[0].i8_step_state--; /* Update to rotate(CCW) through future steps. Direction */
											/* dependent upon MCU pin connections to the motor.      */
					if (SSD[0].i8_step_state < 0)
					{
						SSD[0].i8_step_state = 3;
					}
				}
				SSD[0].i8_SSD_stage = 1; /* Set stage for blanking/intgrtn. Routine does not exit.*/
			}
		}
		else
		{
			SSD[0].u8_SSD_on = 0; /* Stage was an unexpected value, flag SSDx for disable. */
		}
	}
}
#pragma CODE_SEG DEFAULT
