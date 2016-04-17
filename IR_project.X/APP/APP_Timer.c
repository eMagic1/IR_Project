#ifndef __APP_TIMER_C__
#define __APP_TIMER_C__

#include "APP_Timer.h"
#include "../HAL/common.h"
#include "../HAL/HAL_Timer.h"


unsigned char Timer_15s_Is_Over = 0;

static void Setting_Timer_IRQ()
{
    Timer_15s_Is_Over = 1;
    HAL_Timer1_Stop();
}

void Setting_Timer_Start(void)
{
    HAL_Timer1_Init(15, &Setting_Timer_IRQ);
    Timer_15s_Is_Over = 0;
}

void Setting_Timer_Stop(void)
{
    HAL_Timer1_Stop();
    Timer_15s_Is_Over = 0;
}
#endif
