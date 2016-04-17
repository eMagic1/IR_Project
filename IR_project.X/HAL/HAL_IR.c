#ifndef __HAL_IR_C__
#define __HAL_IR_C__
/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <stdbool.h>
#include "xc.h"
#include "common.h"
#include "HAL_IR.h"
/******************************************************************************/
/*Type define                                                                  */
/******************************************************************************/

f_void_IRS * f_IR_Interrupt_Handler;
f_void_IRS * f_IR_OverLoad_Handler;

void HAL_Init_IR_IO(void)
{
    ANSELAbits.ANSA2 = 0; //use for digital input
    TRISAbits.TRISA2 = 1;
    RA2 = 1; //input and pull up
}

void HAL_Set_Trigger_Edg_IR(unsigned char bl_Rasing_Or_Falling, f_void_IRS * f_p_handler)
{
    f_IR_Interrupt_Handler = f_p_handler;
    INTEDG = (unsigned char)bl_Rasing_Or_Falling;
    INTF=0;      // clear INT interrupt flag      
    INTE=1;      //enable INT interrupt   
}

void HAL_IR_Set_Overload_Handler(f_void_IRS * f_p_handler)
{
    f_IR_OverLoad_Handler = f_p_handler;
}
#endif
