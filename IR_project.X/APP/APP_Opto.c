#ifndef __APP_OPTO_C__
#define __APP_OPTO_C__

#include "../HAL/HAL_OPTO.h"
#include "APP_Opto.h"

void LOAD_Change_State(OPTO_LOAD_ID e_Load_Id, E_LOAD_STATE e_Load_State)
{
    if(e_Load_State ==  LOAD_ON)
    {
        GPIO_OPTO_Set(e_Load_Id);
    }
    else
    {
        GPIO_OPTO_Set(e_Load_Id);
    }
}

#endif