/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CAN1.h
**     Project     : MechGauge
**     Processor   : MC9S12ZVH128VLL
**     Component   : FreescaleCAN
**     Version     : Component 02.366, Driver 01.31, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2020-05-26, 17:51, # CodeGen: 24
**     Abstract    :
**         This component "FreescaleCAN" implements a CAN serial channel.
**     Settings    :
**         CAN channel                                     : MSCAN0
**
**           Interrupt service/event                       : Disabled
**          Settings                                       : 
**                Rx pin                                   : PS4_RXCAN0_SCL0_KWS4
**                Rx pin signal                            : 
**                Tx pin                                   : PS5_TXCAN0_SDA0_KWS5
**                Tx pin Signal                            : 
**
**
**            Recieve accept. code                         : 0x00
**            Recieve accept. mask                         : 0xFFFFFFFF
**            Loop Mode                                    : no
**            Bus-Off Recovery                             : Auto
**            Listen Only Mode                             : no
**            Wakeup                                       : Disabled
**
**         Protocol
**             Time segment 1                              : 7
**             Time segment 2                              : 2
**             RSJ                                         : 1
**             Samples per bit                             : Three samples
**             Time quanta per bit                         : 12
**             Init baud rate                              : 500 kbit/s
**
**         Initialization
**             Enabled in init. code                       : yes
**             Events enabled in init.                     : yes
**
**         CPU clock/speed selection
**             High speed mode                             : This component enabled
**             Low speed mode                              : This component disabled
**             Slow speed mode                             : This component disabled
**
**     Contents    :
**         SetAcceptanceCode       - byte CAN1_SetAcceptanceCode(dword AccCode1, dword AccCode2);
**         SetAcceptanceMask       - byte CAN1_SetAcceptanceMask(dword AccMask1, dword AccMask2);
**         SetAcceptanceMode       - byte CAN1_SetAcceptanceMode(byte Mode);
**         SendFrame               - byte CAN1_SendFrame(byte BufferNum, dword MessageID, byte FrameType, byte...
**         GetTransmitErrorCounter - byte CAN1_GetTransmitErrorCounter(void);
**         GetReceiverErrorCounter - byte CAN1_GetReceiverErrorCounter(void);
**         ReadFrame               - byte CAN1_ReadFrame(dword *MessageID, byte *FrameType, byte *FrameFormat,...
**         GetStateTX              - byte CAN1_GetStateTX(void);
**         GetStateRX              - bool CAN1_GetStateRX(void);
**         GetError                - byte CAN1_GetError(CAN1_TError *Err);
**         SendFrameExt            - byte CAN1_SendFrameExt(dword MessageID, byte FrameType, byte Length, byte...
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file CAN1.h
** @version 01.31
** @brief
**         This component "FreescaleCAN" implements a CAN serial channel.
*/         
/*!
**  @addtogroup CAN1_module CAN1 module documentation
**  @{
*/         

#ifndef __CAN1
#define __CAN1

#include "Cpu.h"

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE CAN1. */

#ifndef __BWUserType_CAN1_TError
#define __BWUserType_CAN1_TError
/*lint -save  -esym(960,18.4) Disable MISRA rule (18.4) checking. */
  typedef union {
    word err;
    struct {
      /*lint -save  -e46 Disable MISRA rule (6.4) checking. */
      bool OverRun : 1;                /* Overrun error flag */
      bool RxBufOvf : 1;               /* Rx buffer full error flag */
      bool Idle : 1;                   /* Idle character detect */
      bool BusOff : 1;                 /* Bus-off state */
      bool TxPassive : 1;              /* Transmitter error passive */
      bool RxPassive : 1;              /* Reciver error passive */
      bool TxWarning : 1;              /* Transmitter warning */
      bool RxWarning : 1;              /* Receiver warning */
      bool Ack : 1;                    /* Acknowledge error */
      bool Crc : 1;                    /* CRC error */
      bool Form : 1;                   /* Form error */
      bool Stuff : 1;                  /* Stuff bit error */
      bool Bit0 : 1;                   /* Bit 0 error */
      bool Bit1 : 1;                   /* Bit 1 error */
      /*lint -restore Enable MISRA rule (6.4) checking. */
    }errName;
  } CAN1_TError;                       /* Error flags. For languages which don't support bit access is byte access only to error flags possible. */
/*lint -restore  +esym(960,18.4) Enable MISRA rule (18.4) checking. */
#endif

#pragma DATA_SEG CAN1_DATA             /* Select data segment "CAN1_DATA" */
#pragma CODE_SEG CAN1_CODE

/* User constants */

/* Message filterring */
#define TWO_32_FILTERS                  0x00U
#define FOUR_16_FILTERS                 0x01U
#define EIGHT_8_FILTERS                 0x02U
#define FILTER_CLOSED                   0x03U

/* Frame formats */
#define STANDARD_FORMAT                 0x00U
#define EXTENDED_FORMAT                 0x01U

/* Frame types   */
#define DATA_FRAME                      0x00U
#define REMOTE_FRAME                    0x01U

/* Extended message ID identifier.  This constant can be used to specify an extended message ID
 * anywhere the message ID is required.
 */
#define CAN_EXTENDED_FRAME_ID           0x80000000UL       /* Extended message ID identifier */

/* Global variables */

byte CAN1_SendFrameExt(dword MessageID,byte FrameType,byte Length,const byte *Data);
/*
** ===================================================================
**     Method      :  CAN1_SendFrameExt (component FreescaleCAN)
**     Description :
**         Sends a frame. This method automatically selects a free
**         transmit buffer for data transmission. The user cannot
**         specify a transmit buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**         MessageID       - Identification of the message
**                           - ID. Message ID can be specified in the
**                           STANDARD format (default) or the EXTENDED
**                           format. The most significant bit in the ID
**                           is set to specify EXTENDED format.
**                           Predefined macro CAN_EXTENDED_FRAME_ID can
**                           be used (ID "bitwise or"
**                           CAN_EXTENDED_FRAME_ID) to mark ID as
**                           extended. If the most significant bit of ID
**                           is clear, STANDARD format is used.
**         FrameType       - Type of frame
**                           DATA_FRAME - data frame
**                           REMOTE_FRAME - remote frame
**         Length          - The length of the frame in bytes (0..
**                           8)
**       * Data            - Pointer to data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_VALUE - Some parameter is out of
**                           possible range
** ===================================================================
*/

byte CAN1_SetAcceptanceMode(byte Mode);
/*
** ===================================================================
**     Method      :  CAN1_SetAcceptanceMode (component FreescaleCAN)
**     Description :
**         Sets the acceptance mode register.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Mode            - Acceptance mode.
**                           Supported modes: 
**                           TWO_32_FILTERS - Two 32-bit acceptance
**                           filters
**                           FOUR_16_FILTERS - Four 16-bit acceptance
**                           filters
**                           EIGHT_8_FILTERS - Eight 8-bit acceptance
**                           filters
**                           FILTER_CLOSED - Filter closed
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_VALUE - Parameter has incorrect value
** ===================================================================
*/

byte CAN1_GetStateRX(void);
/*
** ===================================================================
**     Method      :  CAN1_GetStateRX (component FreescaleCAN)
**     Description :
**         Returns a value of the reception complete flag.
**     Parameters  : None
**     Returns     :
**         ---             - The value of the receiver complete flag of
**                           the given buffer. Possible values: <false>
**                           - message buffer is empty <true> - message
**                           buffer isn't empty
** ===================================================================
*/

byte CAN1_SetAcceptanceCode(dword AccCode1, dword AccCode2);
/*
** ===================================================================
**     Method      :  CAN1_SetAcceptanceCode (component FreescaleCAN)
**     Description :
**         Sets the acceptance code registers. This method writes a
**         code mask directly to the acceptance code registers.
**     Parameters  :
**         NAME            - DESCRIPTION
**         AccCode1        - Acceptance code for the message
**                           filtering. This acceptance code will be
**                           written to the acceptance code registers
**                           IDAR0-IDAR3. The most significant byte of
**                           the acceptance code will be written to the
**                           IDAR0 register and the least significant
**                           byte of the acceptance code will be written
**                           to the IDAR3 register.
**         AccCode2        - Acceptance code for the message
**                           filtering. This acceptance code will be
**                           written to the acceptance code registers
**                           IDAR4-IDAR7. The most significant byte of
**                           the acceptance code will be written to the
**                           IDAR4 register and the least significant
**                           byte of the acceptance code will be written
**                           to the IDAR7 register.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
** ===================================================================
*/

byte CAN1_GetError(CAN1_TError *Err);
/*
** ===================================================================
**     Method      :  CAN1_GetError (component FreescaleCAN)
**     Description :
**         Returns the content of the receiver flag register.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Err             - Pointer to the returned set of errors
**     Returns     :
**         ---             - Error code (if GetError did not succeed),
**                           possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte CAN1_GetTransmitErrorCounter(void);
/*
** ===================================================================
**     Method      :  CAN1_GetTransmitErrorCounter (component FreescaleCAN)
**     Description :
**         Returns a value of the transmission error counter.
**     Parameters  : None
**     Returns     :
**         ---             - Returns a value of the transmission error
**                           counter
** ===================================================================
*/

byte CAN1_SendFrame(byte BufferNum,dword MessageID,byte FrameType,byte Length,const byte *Data);
/*
** ===================================================================
**     Method      :  CAN1_SendFrame (component FreescaleCAN)
**     Description :
**         Sends the frame via the CAN device. Using this method the
**         user can send own message to the CAN bus. This method allows
**         to specify CAN buffer number, message ID, data to be sent
**         and frame type (DATA_FRAME/REMOTE_FRAME).
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferNum       - Number of the buffer.
**         MessageID       - Identification of the message
**                           - ID. Message ID can be specified in the
**                           STANDARD format (default) or the EXTENDED
**                           format. The most significant bit in the ID
**                           is set to specify EXTENDED format.
**                           Predefined macro CAN_EXTENDED_FRAME_ID can
**                           be used (ID "bitwise or"
**                           CAN_EXTENDED_FRAME_ID) to mark ID as
**                           extended. If the most significant bit of ID
**                           is clear, STANDARD format is used.
**         FrameType       - Type of frame
**                           DATA_FRAME - data frame
**                           REMOTE_FRAME - remote frame
**         Length          - The length of the frame in bytes (0..
**                           8)
**       * Data            - Pointer to data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_VALUE - Some parameter is out of
**                           possible range
**                           ERR_TXFULL - Transmition buffer is full.
** ===================================================================
*/

byte CAN1_ReadFrame(dword *MessageID, byte *FrameType, byte *FrameFormat, byte *Length, byte *Data);
/*
** ===================================================================
**     Method      :  CAN1_ReadFrame (component FreescaleCAN)
**     Description :
**         Reads a frame from the CAN device. The user is informed
**         about CAN reception through OnFullRxBuffer event or
**         GetStateRX method.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * MessageID       - Pointer to a message
**                           indentification
**       * FrameType       - Pointer to a frame type
**                           DATA_FRAME - data frame
**                           REMOTE_FRAME - remote frame
**       * FrameFormat     - Pointer to a frame format
**                           STANDARD_FORMAT - standard frame 11-bits
**                           EXTENDED_FORMAT - extended frame 29-bits.
**                           Note: This parameter is obsolete and will
**                           be removed in future releases.
**       * Length          - Pointer to a length of the frame
**       * Data            - The buffer for received data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_RXEMPTY - The receive buffer is empty
**                           ERR_OVERRUN - The previous (unread) message
**                           in the receive buffer was overwriten by a
**                           new message. Returns only if Interrupt
**                           service is enabled.
** ===================================================================
*/

void CAN1_Init(void);
/*
** ===================================================================
**     Method      :  CAN1_Init (component FreescaleCAN)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#define CAN1_GetStateTX()  (CAN0TFLG & 0x07U)
/*
** ===================================================================
**     Method      :  CAN1_GetStateTX (component FreescaleCAN)
**     Description :
**         Returns a value of the transmission complete flags.
**     Parameters  : None
**     Returns     :
**         ---             - Content of the transmitter complete flag
**                           register.
** ===================================================================
*/

byte CAN1_SetAcceptanceMask(dword AccMask1, dword AccMask2);
/*
** ===================================================================
**     Method      :  CAN1_SetAcceptanceMask (component FreescaleCAN)
**     Description :
**         Sets the acceptance mask registers. This method writes an
**         acceptance mask directly to the acceptance mask registers.
**     Parameters  :
**         NAME            - DESCRIPTION
**         AccMask1        - Acceptance mask for the message
**                           filtering. This acceptance mask will be
**                           written to the acceptance mask registers
**                           IDMR0-IDMR3. The most significant byte of
**                           the acceptance mask will be written to the
**                           IDMR0 register and the least significant
**                           byte of the acceptance mask will be written
**                           to the IDMR3 register.
**         AccMask2        - Acceptance mask for the message
**                           filtering. This acceptance mask will be
**                           written to the acceptance mask registers
**                           IDMR4-IDMR7. The most significant byte of
**                           the acceptance mask will be written to the
**                           IDMR4 register and the least significant
**                           byte of the acceptance mask will be written
**                           to the IDMR7 register.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
** ===================================================================
*/

byte CAN1_GetReceiverErrorCounter(void);
/*
** ===================================================================
**     Method      :  CAN1_GetRecieveErrorCounter (component FreescaleCAN)
**     Description :
**         Gets the value of reception error counter.
**     Parameters  : None
**     Returns     :
**         ---             - Returns value of the reception error
**                           counter
** ===================================================================
*/


#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */
#pragma CODE_SEG DEFAULT

/* END CAN1. */

#endif /* ifndef __CAN1 */
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
