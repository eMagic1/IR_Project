#ifndef __APP_IR_C__
#define __APP_IR_C__

#include "APP_IR.h"
#include "../HAL/common.h"
#include "../HAL/HAL_Timer.h"
#include "../HAL/HAL_IR.h"


unsigned char IR_Has_Signal = 0;
unsigned short IR_Data[254];
unsigned char Number_Pulse = 0;

void IR_IRQ_Handler(void)
{    
    static unsigned char edge;
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
        if(IR_Data[Number_Pulse - 1] > MAX_COUNT_ON_PLUSE)
        {
            IR_Has_Signal = 1;
            HAL_Timer4_Stop();            
            //start new read IR
            edge = 0;
            HAL_Set_Trigger_Edg_IR(edge, &IR_IRQ_Handler);
        }
        else
        {
            Number_Pulse++;
            HAL_Timer4_Reset();
            edge = edge - 1; // toggle edge
            HAL_Set_Trigger_Edg_IR(edge, &IR_IRQ_Handler);
        }
    }
}

void APP_IR_Start_Read_Date(void)
{
    HAL_Set_Trigger_Edg_IR(0, &IR_IRQ_Handler);
}

#endif