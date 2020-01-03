/*
 * Scheduler.c
 *
 *  Created on: Feb 7, 2012
 *      Author: B40150
 */

#include "Scheduler.h"
#include "PE_Types.h"
#include "Tasks.h"
#include "SysClk.h"
/*   Task ID						Task Function			Time Task  */
#define SCHEDULER_TASKS_TABLE     \
    TABLE(Task1, DataMgnrTask, 5) \
    TABLE(Task2, StepperTask, 51) \
    TABLE(Task3, IluCtrlTask, 102)

#undef TABLE
#define TABLE(a, b, c) a,

/* Enumeration of Tasks IDs */

typedef enum SchedulerTask_Enum_Tag
{
    SCHEDULER_TASKS_TABLE
        MAX_NUM_TASKS
} scheduler_tasks_t;

#undef TABLE
#define TABLE(a, b, c) b,

/* Array of pointer to functions */

pt2Func task_table_ptr[MAX_NUM_TASKS] = {SCHEDULER_TASKS_TABLE};

#undef TABLE
#define TABLE(a, b, c) c,

uint32_t task_table_time[MAX_NUM_TASKS] = {SCHEDULER_TASKS_TABLE};

/******************************************************************************
 * Global functions
 ******************************************************************************/

/*******************************************************************************
 *
 * @brief    SCHD_Scheduler
 * @param    none
 * @return   none
 *
 ********************************************************************************/

void Scheduler_Init(void)
{
    volatile uint8_t u8_schd_task_idx;
    volatile uint32_t u32_schd_ticks = 0x00000000;
    volatile uint32_t u32_schd_modulus;
    volatile uint16_t u16_schd_active_task;
    volatile uint16_t u16_schd_task_mask;
    volatile uint32_t u32_schd_previous_tick = 0x00000000;

    for (;;)
    {
        u32_schd_ticks = Clock_GetTicks();
        u16_schd_active_task = 0x0000;

        if (u32_schd_previous_tick != u32_schd_ticks)
        {
            u32_schd_previous_tick = u32_schd_ticks;
            for (u8_schd_task_idx = 0; u8_schd_task_idx < MAX_NUM_TASKS; u8_schd_task_idx++)
            {
                u32_schd_modulus = u32_schd_ticks % task_table_time[u8_schd_task_idx];
                u16_schd_task_mask = 0x0000;

                if (0x00000000 == u32_schd_modulus)
                {
                    u16_schd_task_mask = (uint16_t)(1 << u8_schd_task_idx);
                    u16_schd_active_task |= u16_schd_task_mask;
                }
            }
            if (0x0000 != u16_schd_active_task)
            {
                for (u8_schd_task_idx = 0; u8_schd_task_idx < MAX_NUM_TASKS; u8_schd_task_idx++)
                {
                    if ((uint16_t)(1 << u8_schd_task_idx) & u16_schd_active_task)
                        (*task_table_ptr[u8_schd_task_idx])();
                }
            }
        }
    }
}
