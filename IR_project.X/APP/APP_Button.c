#ifndef __APP_BUTTON_C__
#define __APP_BUTTON_C__
#include "APP_Button.h"

#include "../HAL/common.h"
#include "../HAL/HAL_Buttons.h"
#include "../HAL/HAL_Timer.h"
#include "../APP/APP_LEDs.h"
volatile unsigned char Button_Press = 0;
volatile unsigned char Button_Release = 0;
volatile unsigned char Button_3s = 0;

static void Button_3s_Handler(void)
{
    unsigned char Button_Value;  
        
    Button_3s = Button_Press;
    Button_Press = BUTTON_NONE;
    Button_Release = BUTTON_NONE;
    HAL_Button_Init(&Button_IRQ__Handler);
    HAL_Timer1_Stop();  
}

void Button_IRQ__Handler2(void)
{
    unsigned char Button_Value;  
        
    HAL_Button_Get_Flag(&Button_Value);
    if((Button_Press == Button_Value)&&(Button_3s == BUTTON_NONE))
    {
        Button_Release = Button_Press;
        Button_Press = BUTTON_NONE;
        Button_3s = BUTTON_NONE;
        HAL_Button_Init(&Button_IRQ__Handler);
        HAL_Timer1_Stop();
    }
}

void Button_IRQ__Handler(void)
{
 
    unsigned char Button_Value;  
    HAL_Debonce();
    HAL_Button_Get_Flag(&Button_Value);
    if(Button_3s == BUTTON_NONE)
    {
        Button_Press = Button_Value;
        Button_Release = BUTTON_NONE;
        Button_3s = BUTTON_NONE;
        HAL_Button_Change_Edge(&Button_IRQ__Handler2);
        HAL_Timer1_Init(3, &Button_3s_Handler);    
    }
}

#endif