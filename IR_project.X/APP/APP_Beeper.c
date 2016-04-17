#ifndef __APP_BEEPER_C__
#define __APP_BEEPER_C__

#include "APP_Beeper.h"
#include "../HAL/common.h"
#include "../HAL/HAL_Buzzer.h"
#include "../HAL/HAL_Timer.h"
#include "APP_LEDs.h"
struct_Beeper strt_Beeper_Value;
struct_time_beeper * p_strt_Time_Beep;
unsigned char u8_Number_Beep;
unsigned char u8_Current_Beep;
unsigned char u8_Beeper_State;

#define NUMBER_BEEP_OK  1
const struct_time_beeper BEEP_PRESS_OK = {2, 1};
#define NUMER_BEEP_ON   2
const struct_time_beeper BEEP_ON_SETTING[NUMER_BEEP_ON] = { {2,1} , {3,1} };
#define NUMBER_BEEP_SETTING_OK  2
const struct_time_beeper BEEP_SETTING_OK[NUMBER_BEEP_SETTING_OK] ={ {3,1}, {2,1} };
#define NUMBER_BEEP_ERROR   3
const struct_time_beeper BEEP_SETTING_ERROR[NUMBER_BEEP_ERROR] = {{2,1}, {2, 1}, {4,1}};

void BEEPER_Set_Volume_Frequency(unsigned short frequency, VOLUME_LEVEL Volume)
{
    strt_Beeper_Value.u16_Beeper_Frequency = frequency;
    switch(Volume)
    {
        case VOLUME_LOW:
            strt_Beeper_Value.u8_Beeper_Volume = 15;
            break;            
        case VOLUME_MED:
            strt_Beeper_Value.u8_Beeper_Volume = 30;
            break;
        case VOLUME_HIGH:
            strt_Beeper_Value.u8_Beeper_Volume = 50;
            break;
        case VOLUME_MAX:
            strt_Beeper_Value.u8_Beeper_Volume = 75;
            break;            
        default:
            strt_Beeper_Value.u8_Beeper_Volume = 50;
            break;
    }         
    setPWMFreq(strt_Beeper_Value.u16_Beeper_Frequency, strt_Beeper_Value.u8_Beeper_Volume);
}

void BEEPER_Timer_Handler(void)
{    
         LEDs_Change_State(LED_1, 1);
    if(u8_Beeper_State == BEEPER_STATE_ON)
    {   
        if(u8_Current_Beep < u8_Number_Beep)
        {
            //init timer with time off, and BEEPER_Timer_Handler to process
            HAL_Timer_0_Init(p_strt_Time_Beep[u8_Current_Beep].time_off, &BEEPER_Timer_Handler);
            u8_Beeper_State == BEEPER_STATE_OFF;
            u8_Current_Beep++;
        }
        else
        {
            //stop timer here
            HAL_Timer0_Stop();
        }
        HAL_Buzzer_Off();        
    }
    else
    {
        if(u8_Current_Beep < u8_Number_Beep)
        {     
            //init timer with time on, and BEEPER_Timer_Handler to process
            HAL_Timer_0_Init(p_strt_Time_Beep[u8_Current_Beep].time_on, &BEEPER_Timer_Handler);
            u8_Beeper_State == BEEPER_STATE_ON;
            //setPWMFreq(strt_Beeper_Value.u16_Beeper_Frequency, strt_Beeper_Value.u8_Beeper_Volume);
            HAL_Buzzer_On(); 
        }
    }
}

void BEEPER_Direct_Beep(void)
{    
    u8_Number_Beep = NUMBER_BEEP_OK;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_PRESS_OK;
    u8_Current_Beep = 0;
    //init timer with BEEP_PRESS_OK time on, and BEEPER_Timer_Handler to process
    HAL_Timer_0_Init(p_strt_Time_Beep[u8_Current_Beep].time_on, &BEEPER_Timer_Handler);
    //setPWMFreq(strt_Beeper_Value.u16_Beeper_Frequency, strt_Beeper_Value.u8_Beeper_Volume);
    HAL_Buzzer_On();
}

void BEEPER_On_Setting(void)
{
    u8_Number_Beep = NUMER_BEEP_ON;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_ON_SETTING;
    u8_Current_Beep = 0;    
    //init timer with  time on, and BEEPER_Timer_Handler to process
    HAL_Timer_0_Init(p_strt_Time_Beep[u8_Current_Beep].time_on, &BEEPER_Timer_Handler);
    HAL_Buzzer_On();

}

void BEEPER_Setting_OK(void)
{
    u8_Number_Beep = NUMBER_BEEP_SETTING_OK;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_SETTING_OK;
    u8_Current_Beep = 0;
    //init timer with  time on, and BEEPER_Timer_Handler to process
    HAL_Timer_0_Init(p_strt_Time_Beep[u8_Current_Beep].time_on, &BEEPER_Timer_Handler);
    HAL_Buzzer_On();
}

void BEEPER_Setting_Error(void)
{
    u8_Number_Beep = NUMBER_BEEP_ERROR;
    u8_Beeper_State = BEEPER_STATE_ON;
    p_strt_Time_Beep = &BEEP_SETTING_ERROR;
    u8_Current_Beep = 0;
    //init timer with  time on, and BEEPER_Timer_Handler to process
    HAL_Timer_0_Init(p_strt_Time_Beep[u8_Current_Beep].time_on, &BEEPER_Timer_Handler);    
    HAL_Buzzer_On();
}
#endif
