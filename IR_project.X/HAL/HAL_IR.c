#ifndef __HAL_IR_C__
#define __HAL_IR_C__
/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <stdbool.h>
#include "xc.h"
#include "HAL_IR.h"
/******************************************************************************/
/*Type define                                                                  */
/******************************************************************************/
typedef void (*f_void_IRS)(void);

f_void_IRS * f_IR_Interrupt_Handler;

void HAL_Init_IR_IO(void)
{
    ANSELA = 0x00; //use for digital input
    TRISA2 = RA2 = 1; //input and pull up
}

void HAL_Set_Trigger_Edg_IR(bool bl_Rasing_Or_Falling, f_void_IRS * f_p_handler)
{
   f_IR_Interrupt_Handler = f_p_handler;
   INTEDG = (unsigned char)bl_Rasing_Or_Falling;
   INTE=1;      //enable INT interrupt
   INTF=0;      // clear INT interrupt flag
   GIE=1;       // enable global interrupt
}
#endif
