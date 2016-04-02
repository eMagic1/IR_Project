/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
typedef void f_void_IRS(void);

extern f_void_IRS * f_Button_Interrupt_Handler;
extern f_void_IRS * f_IR_Interrupt_Handler;
extern f_void_IRS * f_Timer_0_IRS_Handler;
extern f_void_IRS * f_Timer_1_IRS_Handler;
extern f_void_IRS * f_IR_Interrupt_Handler;
extern f_void_IRS * f_Button_Interrupt_Handler;

extern unsigned short u16_Max_Count_Timer0_Interrupt;
extern unsigned short u16_Max_Count_Timer1_Interrupt;
extern unsigned short IR_Tick_Count;

// Interrupt Handler
void interrupt ISR(void)
{
    static unsigned short T0_Tick_Count = 0;
    static unsigned short T1_Tick_Count = 0;
    
    // INT External Interrupt
    if(INTCONbits.INTF == 1)   // if the INT External Interrupt flag is set...
    {        
        f_IR_Interrupt_Handler();
        INTF = 0;                
        INTE = 1;      //enable INT interrupt
    }
    
    //button IRQ
    if (IOCIF) 
    {                                                
        f_Button_Interrupt_Handler();
        IOCIF = 0;                              //must clear the flag in software        
        IOCIE = 1; 
    }
    
    //Timer0 Interrupt Handler
    if (INTCONbits.TMR0IF ==1) // timer 0 interrupt
    {
        T0_Tick_Count++;
        if(T0_Tick_Count > u16_Max_Count_Timer0_Interrupt)
        {
            f_Timer_0_IRS_Handler();
            T0_Tick_Count = 0;
        }
        INTCONbits.TMR0IE = 1;
        INTCONbits.TMR0IF = 0;   // clear the flag
    }
    // timer 1 Interrupt 
    if(PIR1bits.TMR1IF == 1)
    {
        T1_Tick_Count++;
        if(T1_Tick_Count > u16_Max_Count_Timer1_Interrupt)
        {
            f_Timer_1_IRS_Handler();
            T1_Tick_Count = 0;
        }
        PIE1bits.TMR1IE = 1;
        PIR1bits.TMR1IF = 0;   // clear the flag        
    }
    // Timer4 Interrupt- Freq = 33333.33 Hz - Period = 0.000030 seconds
    if (PIR3bits.TMR4IF == 1)          // timer 4 interrupt flag
    {
        IR_Tick_Count++;
        PIR3bits.TMR4IF = 0;  
        PIE3bits.TMR4IE = 0; 
    }
}