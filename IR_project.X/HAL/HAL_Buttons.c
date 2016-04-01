#ifndef __HAL_BUTTTON_C__
#define __HAL_BUTTTON_C__

#include <xc.h>
#include "HAL_Buttons.h"

f_void_IRS * f_Button_Interrupt_Handler;

void HAL_Button_Init(f_void_IRS * p_f_Handler)
{
    ANSELA = 0;// all is digitial
    TRISAbits.TRISA0 = 1; // input
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA4 = 1;

    IOCANbits.IOCAN0 = 1;
    IOCANbits.IOCAN1 = 1;  
    IOCANbits.IOCAN4 = 1; // negative edge 
    
    IOCAPbits.IOCAP0 = 1;
    IOCAPbits.IOCAP1 = 1;  
    IOCAPbits.IOCAP4 = 1; // positive edge 
    
    INTE = 1;      //enable INT interrupt
    INTF = 0;      // clear INT interrupt flag
    IOCAF = 0;
    GIE = 1;       // enable global interrupt
    f_Button_Interrupt_Handler = p_f_Handler;    
}

void Get_Button_State(E_BUTTON_ID eButton_ID, unsigned char * state)
{
    switch(eButton_ID)
    {
        case BUTTON_1:
            *state = PORTAbits.RA0;
            break;
        case BUTTON_2:
            *state = PORTAbits.RA1;
            break;
        case BUTTON_3:
            *state = PORTAbits.RA4;
            break;   
        default:
            break;
    }
}
#endif
