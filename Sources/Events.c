/* ###################################################################
**     Filename    : Events.c
**     Project     : MechGauge
**     Processor   : MC9S12ZVH128VLL
**     Component   : Events
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2019-12-14, 21:51, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "SysClk.h"
#include "MC.h"
#pragma CODE_SEG DEFAULT

/*
** ===================================================================
**     Event       :  IEE1_OnWriteEnd (module Events)
**
**     Component   :  IEE1 [IntEEPROM]
**     Description :
**         Event is called when a write to EEPROM is finished.
**         The event is available only if the <Interrupt service/event>
**         property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void IEE1_OnWriteEnd(void)
{
  /* Write your code here ... */
}

/* END Events */

#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(RtiIsr)
{
	Clock_IncTicks();
}
#pragma CODE_SEG DEFAULT
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(Tim0Ch0Isr)
{
	TIM0TFLG1_C0F = 1;
	TIM0TC0 = TIM0TC0 + 1200;	
	Move_Stepper();
}
#pragma CODE_SEG DEFAULT
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS12Z series of microcontrollers.
**
** ###################################################################
*/
