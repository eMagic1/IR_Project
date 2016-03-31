#ifndef __HAL_BUTTTON_C__
#define __HAL_BUTTTON_C__

#include <pic16f1825.h>

typedef void (*f_void_IRS)(void);
f_void_IRS * f_Button_Interrupt_Handler;

void HAL_Button_Init(f_void_IRS * p_f_Handler)
{
    ANSELA = 0;// all is digitial
    TRISAbits.TRISA0 = 1; // input
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA4 = 1;
    IOCANbits.IOCAN0 = 1; // negative edge
    IOCANbits.IOCAN1 = 1;
    IOCANbits.IOCAN3 = 1;
    INTE = 1;      //enable INT interrupt
    INTF = 0;      // clear INT interrupt flag
    IOCAF = 0;
    GIE = 1;       // enable global interrupt
    f_Button_Interrupt_Handler = p_f_Handler;
}

#endif
