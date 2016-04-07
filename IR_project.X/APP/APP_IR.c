#ifndef __APP_IR_C__
#define __APP_IR_C__

#include "APP_IR.h"
#include "../HAL/common.h"
#include "../HAL/HAL_Timer.h"
#include "../HAL/HAL_IR.h"


unsigned char IR_Has_Signal = 0;
unsigned short IR_Data[100];
unsigned char Number_Pulse = 0;

static void IR_IRQ_Handler(void)
{    
    static unsigned char edge = 0;
    if(Number_Pulse == 0)//start IR signal
    {
        //falling edge
        //start timer        
        HAL_Timer4_Reset();
        HAL_Timer46_Init();  
        Number_Pulse++;
        edge = 1;// change to raising edge
        HAL_Set_Trigger_Edg_IR(edge, &IR_IRQ_Handler);
    }
    else
    {
        HAL_Timer4_Get_TickCount(&IR_Data[Number_Pulse - 1]);
        Number_Pulse++;
        HAL_Timer4_Reset();
        edge = 1 - edge; // toggle edge
        HAL_Set_Trigger_Edg_IR(edge, &IR_IRQ_Handler);
    }
}
static void APP_IR_End_Read_Data(void)
{
    IR_Has_Signal = 1;
    HAL_Timer4_Stop();            
    HAL_Set_Trigger_Edg_IR(0, &IR_IRQ_Handler);
}

void APP_IR_Start_Read_Data(void)
{
    HAL_Set_Trigger_Edg_IR(0, &IR_IRQ_Handler);
    HAL_IR_Set_Overload_Handler(MAX_COUNT_ON_PLUSE, &APP_IR_End_Read_Data);
}

#endif