/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "CAN1.h"
#include "PWM_BL.h"
#include "PWM_WL.h"
#include "IEE1.h"
#include "Vrti.h"
#include "Vtim0ch0.h"
#include "Vssd0.h"

#pragma CODE_SEG DEFAULT


void IEE1_OnWriteEnd(void);
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

/* END Events */
#endif /* __Events_H*/

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
