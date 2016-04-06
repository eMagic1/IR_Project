#ifndef __HAL_TIMER_C__
#define __HAL_TIMER_C__

#include <xc.h>
#include "../system.h"
#include "common.h"
#include "HAL_Timer.h"

f_void_IRS * f_Timer_0_IRS_Handler;
f_void_IRS * f_Timer_1_IRS_Handler;

unsigned short u16_Max_Count_Timer0_Interrupt = 0;
unsigned short u16_Max_Count_Timer1_Interrupt = 0;

void HAL_Debonce(void)
{
    __delay_ms(100);//debounce
}

void HAL_Timer_0_Init(unsigned short timer_ms, f_void_IRS * f_p_func)
{
    unsigned short u8_MaxValue;
    unsigned short u8_Times;
         
    TMR0 = 0;
    OPTION_REGbits.TMR0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111; // prescale 
    u8_MaxValue = 1000*FCY*256*256; //ms   
    if(timer_ms < u8_MaxValue)        
    {
        TMR0 = 255-1;// limit 1 count min
        u16_Max_Count_Timer0_Interrupt = 0;
    }
    else
    {
        u8_Times = (timer_ms/u8_MaxValue);
        if(u8_Times > 255)
        {
            TMR0 = 0;
            u16_Max_Count_Timer0_Interrupt = (u8_Times/255) + 1;
        }
        else
        {
            TMR0 = 255 - u8_Times;
            u16_Max_Count_Timer0_Interrupt = 0;
        }
    }
    f_Timer_0_IRS_Handler = f_p_func;
    INTCONbits.TMR0IF = 0;        // bit2 clear timer 0 interrupt flag
    TMR0IE = 1;//enable interrupt
}

void HAL_Timer0_Reset(void)
{
    u16_Max_Count_Timer0_Interrupt = 0;
    INTCONbits.TMR0IF = 0;
}

void HAL_Timer0_Stop(void)
{
    TMR0 = 0;
    INTCONbits.TMR0IF = 0;        // bit2 clear timer 0 interrupt flag
    TMR0IE = 0;//disable interrupt
}

void HAL_Timer1_Init(unsigned short timer_ms, f_void_IRS * f_p_func)
{
    unsigned short u8_MaxValue;
    unsigned short u8_Times;
    unsigned short u16_Value;
    
    u8_MaxValue = 1000*FCY*65536*8; //ms  
    
    T1CONbits.TMR1CS = 0x00;
    T1CONbits.T1CKPS = 0b11; //prescaler 1:8
    //Timer1 Registers Prescaler= 8 - TMR1 Preset = 0 - Freq = 9.54 Hz - Period = 0.104858 seconds
    T1CONbits.T1OSCEN = 1;   // bit 3 Timer1 Oscillator Enable Control bit 1 = on
    T1CONbits.nT1SYNC = 1;   // bit 2 Timer1 External Clock Input Synchronization Control bit...1 = Do not synchronize external clock input
    T1CONbits.TMR1CS = 0;    // bit 1 Timer1 Clock Source Select bit...0 = Internal clock (FOSC/4)
    T1CONbits.TMR1ON = 1;    // bit 0 enables timer
    
    if(timer_ms < u8_MaxValue)
    {
        TMR1H = 0xFE;             // preset for timer1 MSB register
        TMR1L = 0xFF;             // preset for timer1 LSB register
    }
    else
    {        
        u8_Times = (timer_ms/u8_MaxValue);
        if(u8_Times > 65535)
        {
            u16_Value = 0; 
            TMR1H = 0;
            TMR1L = 0;
            u16_Max_Count_Timer1_Interrupt =(u8_Times/65535) + 1;
        }
        else
        {
            u16_Value = 65536 - u8_Times;
            TMR1H = (unsigned char)(u16_Value && 0xFF00) >> 8;
            TMR1L = (unsigned char)(u16_Value && 0x00FF);
        }
    }

// Interrupt Registers
  PIR1bits.TMR1IF = 0;            // clear timer1 interupt flag TMR1IF
  PIE1bits.TMR1IE  =   1;         // enable Timer1 interrupts   
  f_Timer_1_IRS_Handler = f_p_func;
}

void HAL_Timer1_Reset(void)
{
    u16_Max_Count_Timer1_Interrupt = 0;
    T1CONbits.TMR1ON = 0;    // bit 0 enables timer
    PIR1bits.TMR1IF = 0;            // clear timer1 interupt flag TMR1IF
    PIE1bits.TMR1IE  =   1;         // enable Timer1 interrupts 
    T1CONbits.TMR1ON = 1;    // bit 0 enables timer
}

void HAL_Timer1_Stop(void)
{
    T1CONbits.TMR1ON = 0;           // bit 0 enables timer
    PIR1bits.TMR1IF = 0;            // clear timer1 interupt flag TMR1IF
    PIE1bits.TMR1IE  =   0;         // enable Timer1 interrupts 
}

unsigned short IR_Tick_Count = 0;

void HAL_Timer46_Init(void)//0.1ms for 1 count
{
    T4CON |= 0;        // bits 6-3 Post scaler 1:1 thru 1:16
    T4CONbits.TMR4ON = 1;  // bit 2 turn timer4 on;
    T4CONbits.T4CKPS1 = 0; // bits 1-0  Prescaler Rate Select bits
    T4CONbits.T4CKPS0 = 0;
    PR4 = 50;         // PR4 (Timer4 Match value) for 0.1ms
    
    // Interrupt Registers      
    PIR3bits.TMR4IF = 0;
    PIE3bits.TMR4IE = 1;         // enable Timer4 interrupts    
}

void HAL_Timer4_Get_TickCount(unsigned short * value)
{
    TMR4 = 0;
    *value = IR_Tick_Count;
}

void HAL_Timer4_Reset(void)
{
    IR_Tick_Count = 0;
}

void HAL_Timer4_Stop(void)
{
    PIR3bits.TMR4IF = 0;
    PIE3bits.TMR4IE = 0;         // disable Timer4 interrupts  
}

#endif