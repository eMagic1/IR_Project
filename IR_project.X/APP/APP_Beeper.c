#ifndef __APP_BEEPER_C__
#define __APP_BEEPER_C__

#include "APP_Beeper.h"
#include "../HAL/HAL_Buzzer.h"

struct_Beeper strt_Beeper_Value;
struct_time_beeper * p_strt_Time_Beep;
unsigned char u8_Number_Beep;
unsigned char u8_Current_Beep;
unsigned char u8_Beeper_State;

#define NUMBER_BEEP_OK  1
const struct_time_beeper BEEP_PRESS_OK = {200, 100};
#define NUMER_BEEP_ON   2
const struct_time_beeper BEEP_ON_SETTING[NUMER_BEEP_ON] = { {200,50} , {300,100} };
#define NUMBER_BEEP_SETTING_OK  2
const struct_time_beeper BEEP_SETTING_OK[NUMBER_BEEP_SETTING_OK] ={ {300,100}, {200,50} };
#define NUMBER_BEEP_ERROR   3
const struct_time_beeper BEEP_SETTING_ERROR[NUMBER_BEEP_ERROR] = {{200,100}, {200, 100}, {400,100}};

void BEEPER_Set_Volume_Frequency(unsigned short frequency, unsigned short Volume)
{
    strt_Beeper_Value.u16_Beeper_Frequency = frequency;
    switch(Volume)
    {
        case 0:
            strt_Beeper_Value.u8_Beeper_Volume = 15;
            break;            
        case 1:
            strt_Beeper_Value.u8_Beeper_Volume = 30;
            break;
        case 2:
            strt_Beeper_Value.u8_Beeper_Volume = 50;
            break;
        default:
            strt_Beeper_Value.u8_Beeper_Volume = 50;
            break;
    }            
    HAL_Buzzer_PWM_Init(strt_Beeper_Value.u16_Beeper_Frequency, strt_Beeper_Value.u8_Beeper_Volume);
}

void BEEPER_Timer_Handler(void)
{    
    if(u8_Beeper_State == BEEPER_STATE_ON)
    {
        if(u8_Current_Beep < u8_Number_Beep)
        {
            //init timer with time off, and BEEPER_Timer_Handler to process
            u8_Beeper_State == BEEPER_STATE_OFF;
        }
        else
        {
            //stop timer here
        }
        HAL_Buzzer_Off();        
    }
    else
    {
        if(u8_Current_Beep < u8_Number_Beep)
        {     
            u8_Current_Beep++;
            //init timer with time on, and BEEPER_Timer_Handler to process
            u8_Beeper_State == BEEPER_STATE_ON;
            HAL_Buzzer_On(); 
        }
    }
}

void BEEPER_Direct_Beep(void)
{    
    u8_Number_Beep = NUMBER_BEEP_OK;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_PRESS_OK;
    //init timer with BEEP_PRESS_OK time on, and BEEPER_Timer_Handler to process
    HAL_Buzzer_On();
    u8_Current_Beep = 0;
}

void BEEPER_On_Setting(void)
{
    u8_Number_Beep = NUMER_BEEP_ON;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_ON_SETTING;
    //init timer with  time on, and BEEPER_Timer_Handler to process
    HAL_Buzzer_On();
    u8_Current_Beep = 0;
}

void BEEPER_Setting_OK(void)
{
    u8_Number_Beep = NUMBER_BEEP_SETTING_OK;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_SETTING_OK;
    //init timer with  time on, and BEEPER_Timer_Handler to process
    HAL_Buzzer_On();
    u8_Current_Beep = 0;
}

void BEEPER_Setting_Error(void)
{
    u8_Number_Beep = NUMBER_BEEP_ERROR;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_SETTING_ERROR;
    //init timer with  time on, and BEEPER_Timer_Handler to process
    HAL_Buzzer_On();
    u8_Current_Beep = 0;
}
#endif
