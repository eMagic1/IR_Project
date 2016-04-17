#ifndef __HAL_TIMER_C__
#define __HAL_TIMER_C__

#include <xc.h>
#include "../system.h"
#include "common.h"
#include "HAL_Timer.h"
#include "HAL_Leds.h"

f_void_IRS * f_Timer_0_IRS_Handler;
f_void_IRS * f_Timer_1_IRS_Handler;

unsigned char u16_Max_Count_Timer0_Interrupt = 0;
unsigned char u16_Max_Count_Timer1_Interrupt = 0;

unsigned char T0_Tick_Count = 0;
unsigned char T1_Tick_Count = 0;
unsigned char IR_Tick_Count = 0;

void HAL_Debonce(void)
{
    __delay_ms(5);//debounce
}
//timer 500ms
void HAL_Timer_0_Init(unsigned char Count_100ms, f_void_IRS * f_p_func)
{      
    OPTION_REGbits.TMR0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111; // prescale 255
        
    TMR0 = 60;//25ms
    u16_Max_Count_Timer0_Interrupt = 4*Count_100ms;
    T0_Tick_Count = 0;
    f_Timer_0_IRS_Handler = f_p_func;
    INTCONbits.TMR0IF = 0;        // bit2 clear timer 0 interrupt flag
    TMR0IE = 1;//enable interrupt    
}

void HAL_Timer0_Reset(void)
{
    u16_Max_Count_Timer0_Interrupt = 0;
    T0_Tick_Count =  0;
    INTCONbits.TMR0IF = 0;
    TMR0IE = 1;
}

void HAL_Timer0_Stop(void)
{
    TMR0 = 0;
    INTCONbits.TMR0IF = 0;        // bit2 clear timer 0 interrupt flag
    TMR0IE = 0;//disable interrupt
}
/*Timer 1s*/
void HAL_Timer1_Init(unsigned short timer_s, f_void_IRS * f_p_func)//max 33s
{
    T1CONbits.T1CKPS = 0b11; //prescaler 1:8
    //Timer1 Registers Prescaler= 8 - TMR1 Preset = 0 - Freq = 9.54 Hz - Period = 0.104858 seconds
    T1CONbits.T1OSCEN = 0;   // bit 3 Timer1 Oscillator Enable Control bit 1 = on
    T1CONbits.nT1SYNC = 1;   // bit 2 Timer1 External Clock Input Synchronization Control bit...1 = Do not synchronize external clock input
    T1CONbits.TMR1CS = 0;    // bit 1 Timer1 Clock Source Select bit...0 = Internal clock (FOSC/4)
    
    T1CONbits.TMR1ON = 1;    // bit 0 enables timer
    
    TMR1H = 11; //250ms
    TMR1L = 120;
    u16_Max_Count_Timer1_Interrupt = 4*timer_s;
    T1_Tick_Count = 0;
    // Interrupt Registers
    PIR1bits.TMR1IF     =   0;            // clear timer1 interupt flag TMR1IF
    PIE1bits.TMR1IE     =   1;         // enable Timer1 interrupts   
    PEIE = 1;
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
/*Timer 0.1ms*/
void HAL_Timer2_Init(void)//0.1ms for 1 count
{
    //Timer2 Registers Prescaler= 1 - TMR2 PostScaler = 1 - PR2 = 200 - Freq = 10000.00 Hz - Period = 0.000100 seconds
    T2CON |= 0;        // bits 6-3 Post scaler 1:1 thru 1:16
    T2CONbits.TMR2ON = 1;  // bit 2 turn timer2 on;
    T2CONbits.T2CKPS1 = 0; // bits 1-0  Prescaler Rate Select bits
    T2CONbits.T2CKPS0 = 0;
    PR2 = 200;         // PR2 (Timer2 Match value)
    
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;         // disable Timer4 interrupts  
    PEIE = 1;
}

void HAL_Timer2_Get_TickCount(unsigned char * value)
{
    *value = IR_Tick_Count;
}

void HAL_Timer2_Reset(void)
{
    IR_Tick_Count = 0;
    
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;         // disable Timer4 interrupts  
    PEIE = 1;
}

void HAL_Timer2_Stop(void)
{
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 0;         // disable Timer4 interrupts  
}

#endif