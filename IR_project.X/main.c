/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <stdlib.h> 

#include "HAL/common.h"
#include "HAL/HAL_Buttons.h"
#include "HAL/HAL_Buzzer.h"
#include "HAL/HAL_Eeprom.h"
#include "HAL/HAL_IR.h"
#include "HAL/HAL_Leds.h"
#include "HAL/HAL_OPTO.h"

#include "APP/APP_Beeper.h"
#include "APP/APP_Button.h"
#include "APP/APP_Eeprom.h"
#include "APP/APP_IR.h"
#include "APP/APP_LEDs.h"
#include "APP/APP_Opto.h"
#include "APP/APP_Timer.h"
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
unsigned char Parse_Data(unsigned char * p_LoadID)
{
    unsigned char u8_Result = 0;
    unsigned short Data;
    unsigned char bLen = 0;
    unsigned char delta_pulse;
    unsigned char u8_Index_Load;
    unsigned char u8_Index_Data;
    
    *p_LoadID = 0;
    for ( u8_Index_Load = 0; u8_Index_Load< NUMBER_LOAD; u8_Index_Load++)
    {
        Read_IR_Data_Len(u8_Index_Load, &bLen);
        if(bLen >= Number_Pulse)
        {
            delta_pulse = bLen - Number_Pulse;
            bLen = Number_Pulse;
        }
        else
        {
            delta_pulse = Number_Pulse- bLen;          
        }
        if(delta_pulse*10 < bLen*2)// 20%
        {
            for(u8_Index_Data = 0; u8_Index_Data < bLen; u8_Index_Data++)
            {
                Read_IR_Data_At(u8_Index_Load, &Data, u8_Index_Data);
                if( abs(IR_Data[u8_Index_Data]*10- Data*10) > IR_Data[u8_Index_Data]*2)//20%
                {
                    break;
                }
            }    
            if(u8_Index_Data >= bLen)
            {
                u8_Result = 1;
                *p_LoadID = u8_Index_Load + 1;
                break;
            }
        }
    }
    
    return u8_Result;
}
void main(void)
{
    static unsigned char Setting_Timer_Is_Running = 0;
    unsigned char u8_State_Load;
    OPTO_LOAD_ID Load_ID;
    E_LOAD_STATE Load_State;
    
    //HAL init
    HAL_Button_Init(&Button_IRQ_Handler);
    HAL_Buzzer_GPIO_Init();
    HAL_Buzzer_PWM_Init(FREQUENCY_MED, VOLUME_HIGH);
    GPIO_Leds_Init();
    GPIO_OPTOs_Init();
    //App Init
    APP_IR_Start_Read_Data();
    
    //init state when start up (power up)    
    for(unsigned char i = 0; i < NUMBER_LOAD; i++)
    {
        Read_State_Of_Load(i, &u8_State_Load);
        if(u8_State_Load < 2)
        {
            LOAD_Change_State(i, u8_State_Load);
            LEDs_Change_State(i, u8_State_Load);
        }
        else
        {
            u8_State_Load = 0;
            LOAD_Change_State(i, u8_State_Load);// turn off
            LEDs_Change_State(i, u8_State_Load);
            Write_State_Of_Load(i, &Load_State);
        }
    }
    
    while(1)
    {
        if(Button_3s != 0)
        {     
            BEEPER_On_Setting();
            LEDs_Blink(Button_3s);
            if(Setting_Timer_Is_Running == 0)
            {
                //start timer 15s
                Setting_Timer_Start();
                Setting_Timer_Is_Running = 1;
            }
            else
            {
                if(Timer_15s_Is_Over)
                {
                    //exit setting
                    Button_3s =0 ;
                    Setting_Timer_Is_Running = 0;
                    BEEPER_Setting_Error();
                    LEDs_Stop_Blink();
                }
            }           
            if((IR_Has_Signal)&&(Setting_Timer_Is_Running))
            {
                //save data to flash
                Write_IR_Data(Button_3s - 1, IR_Data, Number_Pulse);
                //reset button 3s
                Button_3s = 0 ;
                IR_Has_Signal = 0;
                Setting_Timer_Stop();
                BEEPER_Setting_OK();
                LEDs_Stop_Blink();
            }
        }
        
        if(Button_Release != 0)
        {
            if(Button_Release == Button_3s)// press button one more times when setting for this button
            {
                //exit Read IR
                Button_3s = 0;
                Button_Release = 0;
                if(Setting_Timer_Is_Running)
                {
                    Setting_Timer_Stop();
                }
                BEEPER_Setting_Error();
                LEDs_Stop_Blink();
            }
            else
            {
                BEEPER_Direct_Beep();
                //get satte
                Read_State_Of_Load(Button_Release - 1, &u8_State_Load);
                //chaneg load
                Load_ID = Button_Release - 1;
                Load_State = 1 - u8_State_Load;
                LOAD_Change_State(Load_ID, Load_State);
                LEDs_Change_State(Load_ID, Load_State);
                //save state
                Write_State_Of_Load(Load_ID, &Load_State);
                Button_Release = 0;
            }
        }
        
        if((IR_Has_Signal)&&(Button_3s == 0))
        {
            if (Parse_Data(&Button_Release))
            {
                 BEEPER_Direct_Beep();
                //get satte
                Read_State_Of_Load(Button_Release - 1, &u8_State_Load);
                //chaneg load            
                Load_ID = Button_Release - 1;
                Load_State = 1 - u8_State_Load;
                LOAD_Change_State(Load_ID, Load_State);
                LEDs_Change_State(Load_ID, Load_State);
                //save state
                Write_State_Of_Load(Load_ID, &Load_State);
                Button_Release = 0;
            }
            else
            {
                BEEPER_Setting_Error();
            }
            IR_Has_Signal = 0;
        }
        CLRWDT();
        /* TODO <INSERT USER APPLICATION CODE HERE> */
    }

}

