#ifndef __HAL_BUTTTON_C__
#define __HAL_BUTTTON_C__

#include <xc.h>
#include "common.h"
#include "HAL_Buttons.h"

f_void_IRS *  f_Button_Interrupt_Handler;

void HAL_Button_Init(f_void_IRS * p_f_Handler)
{
    TRISAbits.TRISA0 = 1; // input
    ANSELAbits.ANSA0 = 0;// all is digitial
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA1 = 0;// all is digitial
    TRISAbits.TRISA4 = 1;  
    ANSELAbits.ANSA4 = 0;// all is digitial
    IOCAP = 0;
    INTCONbits.IOCIE = 1;                       //enable interrupt on change global
    
    IOCANbits.IOCAN0 = 1;
    IOCANbits.IOCAN1 = 1;  
    IOCANbits.IOCAN4 = 1; // negative edge 
    //IOCAPbits.IOCAP0 = 1;
    //IOCAPbits.IOCAP1 = 1;  
    //IOCAPbits.IOCAP4 = 1; // positive edge   

    f_Button_Interrupt_Handler = p_f_Handler;    
}

void HAL_Button_Change_Edge(f_void_IRS * p_f_Handler)
{
    TRISAbits.TRISA0 = 1; // input
    ANSELAbits.ANSA0 = 0;// all is digitial
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA1 = 0;// all is digitial
    TRISAbits.TRISA4 = 1;  
    ANSELAbits.ANSA4 = 0;// all is digitial
    IOCAN = 0;
    INTCONbits.IOCIE = 1;                       //enable interrupt on change global    

    IOCAPbits.IOCAP0 = 1;
    IOCAPbits.IOCAP1 = 1;  
    IOCAPbits.IOCAP4 = 1; // positive edge   
    f_Button_Interrupt_Handler = p_f_Handler;    
}

void HAL_Button_Get_Flag( unsigned char * state)
{
    *state = 0;
    if(IOCAF0)
    {
        *state = BUTTON_1;
    }
    else if(IOCAF1)
    {
        *state = BUTTON_2;
    }
    else if(IOCAF4)
    {
        *state = BUTTON_3;
    }   
    IOCAF = 0;
}
void HAL_Button_Get_State(E_BUTTON_ID eButton_ID, unsigned char * state)
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
