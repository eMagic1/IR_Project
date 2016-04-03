#ifndef __APP_BUTTON_C__
#define __APP_BUTTON_C__
#include "APP_Button.h"
#include "../HAL/common.h"
#include "../HAL/HAL_Buttons.h"
#include "../HAL/HAL_Timer.h"

unsigned char Button_Press = 0;
unsigned char Button_Release = 0;
unsigned char Button_3s = 0;

void Button_3s_Handler(void)
{
    unsigned char Button_Value[3];
    for(unsigned char i = BUTTON_1; i<= BUTTON_3; i++)
    {
        Get_Button_State(i, &Button_Value[i]);
        if((Button_Press > 0)&&(Button_Value[i] == 0)&&(i+1 == Button_Press))//still press
        {
            Button_Press = 0;
            Button_3s = i+1; //save state 3s
            //end timer here
            HAL_Timer1_Stop();
            break;
        }
    }
}

void Button_IRQ_Handler(void)
{
    unsigned char Button_Value[3];
    __delay_ms(100);//debounce

    for(unsigned char i = BUTTON_1; i<= BUTTON_3; i++)
    {
        Get_Button_State(i, &Button_Value[i]);
        if(Button_Press == 0)
        {
            if((Button_Value[i] == 0)&&(Button_3s != i+1))//pressed
            {
                Button_Press = i+1;
                //start timer here
                HAL_Timer1_Init(3000, &Button_3s_Handler);
                break;
            }
        }
        else
        {
            if((Button_Value[i] == 1)&&(i+1 == Button_Press)&&(Button_3s != i+1))//release
            {
                Button_Press = 0; 
                Button_Release = i+1;
                //end timer here
                HAL_Timer1_Stop();
                break;
            }
        }
    }
}


#endif