#ifndef __APP_LEDs_C__
#define __APP_LEDs_C__

#include "../HAL/HAL_Leds.h"
#include "APP_LEDs.h"
#include "../HAL/common.h"
#include "../HAL/HAL_Timer.h"

E_LED_ID LED_Active_Blink = LED_ID_MAX;


void LEDs_Change_State(E_LED_ID e_Leds_Id, E_LED_STATE e_Led_State)
{
    if(e_Led_State ==  LED_ON)
    {
        GPIO_Leds_Set(e_Leds_Id);
    }
    else
    {
        GPIO_Leds_Clear(e_Leds_Id);
    }
}
void LEDs_Blink_Handler(void)
{
    static E_LED_STATE e_State = LED_OFF;
    if( LED_Active_Blink != LED_ID_MAX)
    {
        if(e_State == LED_OFF)
        {
            GPIO_Leds_Set(LED_Active_Blink);
            e_State = LED_ON;
        }
        else
        {
            GPIO_Leds_Clear(LED_Active_Blink);
            e_State = LED_OFF;        
        }
    }
    //restart timer here
    HAL_Timer_0_Init(500, &LEDs_Blink_Handler);
}

void LEDs_Blink(E_LED_ID e_Leds_Id)
{
    LED_Active_Blink = e_Leds_Id;
    //start timer with LEDs_Blink_Handler
    HAL_Timer_0_Init(500, &LEDs_Blink_Handler);
}

void LEDs_Stop_Blink(void)
{
    if(LED_Active_Blink != LED_ID_MAX)
    {
        GPIO_Leds_Clear(LED_Active_Blink);
        //stop timer
        HAL_Timer0_Stop();
    }
}
#endif
