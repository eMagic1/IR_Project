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
        Read_State_Of_Load(1, &u8_State_Load);
        LOAD_Change_State(Load_ID, u8_State_Load);
        LEDs_Change_State(Load_ID, u8_State_Load);
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
            }
        }
        
        if((IR_Has_Signal)&&(Button_3s == 0))
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
        }
        CLRWDT();
        /* TODO <INSERT USER APPLICATION CODE HERE> */
    }

}

