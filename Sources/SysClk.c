#include "SysClk.h"
#include "IO_Map.h"

volatile static uint32_t u32_clock_ticks = 0x00000000;

uint32_t Clock_GetTicks(void)
{
    return u32_clock_ticks;
}

void Clock_IncTicks(void)
{
    u32_clock_ticks++;
    CPMUIFLG_RTIF = 1;
}

void Clock_Init(void)
{
  /* CPMUINT: RTIE=0 */
  clrReg8Bits(CPMUINT, 0x80U);          
  /* CPMUIFLG: RTIF=1,??=0,??=0,LOCKIF=0,LOCK=0,??=0,OSCIF=0,UPOSC=0 */
  setReg8(CPMUIFLG, 0x80U);             
  /* CPMUPROT: ??=0,??=0,??=1,??=0,??=0,??=1,??=1,PROT=0 */
  setReg8(CPMUPROT, 0x26U);            /* Disable protection of clock-source register */ 
  /* CPMUCLKS: PRE=0,RTIOSCSEL=0 */
  clrReg8Bits(CPMUCLKS, 0x0AU);         
  /* CPMUCLKS: RTIOSCSEL=1 */
  setReg8Bits(CPMUCLKS, 0x02U);         
  /* CPMUPROT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,PROT=0 */
  setReg8(CPMUPROT, 0x00U);            /* Re-Enable protection of clock-source register */ 
  /* CPMURTI: RTDEC=1,RTR6=0,RTR5=0,RTR4=0,RTR3=1,RTR2=0,RTR1=1,RTR0=1 */
  setReg8(CPMURTI, 0x8BU);    
    CPMUINT_RTIE = 1;
}
