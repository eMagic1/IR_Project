#ifndef __APP_LEDs_C__
#define __APP_LEDs_C__

#include "APP_LEDs.h"
#include "../HAL/common.h"
#include "../HAL/HAL_Timer.h"
#include "../HAL/HAL_Leds.h"
E_LED_ID LED_Active_Blink = LED_ID_MAX;


void LEDs_Change_State(E_LED_ID e_Leds_Id, E_LED_STATE e_Led_State)
{
    if(e_Led_State ==  LED_ON)
    {
        GPIO_Leds_Set(e_Leds_Id + 2);//Led 0 is RC3
    }
    else
    {
        GPIO_Leds_Clear(e_Leds_Id + 2);
    }
}
static void LEDs_Blink_Handler(void)
{
    static E_LED_STATE e_State = LED_OFF;
    if( LED_Active_Blink != LED_ID_MAX)
    {
        e_State = LED_ON - e_State;
        LEDs_Change_State(LED_Active_Blink, e_State);
    }
}

void LEDs_Blink(E_LED_ID e_Leds_Id)
{
    LED_Active_Blink = e_Leds_Id;
    //start timer with LEDs_Blink_Handler
    HAL_Timer_0_Init(1, &LEDs_Blink_Handler);
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
