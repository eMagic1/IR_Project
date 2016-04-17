#ifndef __HAL_BUZZER_C__
#define __HAL_BUZZER_C__
/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>
#include "../system.h"
#include "HAL_Buzzer.h"
/******************************************************************************/
/*Function Name:  HAL_Buzzer_GPIO_Init                                        */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void HAL_Buzzer_GPIO_Init(void)
{
#ifdef PIC16F1825    
    TRISAbits.TRISA5 = 0;
    LATA5 = 0;                                      //PWM pin RA5       
    APFCON1bits.CCP2SEL = 1;
#endif
#ifdef PIC16F1823
    TRISCbits.TRISC5 = 0;
    LATC5 = 0;   
#endif    
}
/*
 * ================ setPWMDuty ==================================================
 *
 * This sets the registers for the PWM duty.  This is a maximum of a 10-bit value,
 * but many PWM settings will limit this anount.
 *
 * Parameters:
 *    duty:   The duty value to set in the register.  This is the actual value,
 *            not a percent.
 *
 * Returns:
 *    none:
 *
 * =============================================================================
 */
void setPWMDuty(unsigned short duty)
{
#ifdef PIC16F1825    
    CCPR2L = duty >> 2;                  // Set MSB values
    CCP2CON = ((duty & 3) << 4) | 0x0C;  // set initial duty and set PWM mode bits.    
#endif
#ifdef PIC16F1823
    CCPR1L = duty >> 2;                  // Set MSB values
    CCP1CON = ((duty & 3) << 4) | 0x0C;  // set initial duty and set PWM mode bits.
#endif  
}
 /*
 * ================ setPWMFrq ==================================================
 *
 * The function sets the PWM registers for a requested PWM frequency.  It
 * loops through the valid prescaler values (1,4,16) unitl it finds one that
 * will work.  The lowest value will yeild the highest resolution (maxDuty)
 * value, so the loop will quit at the first value it finds.  The function does
 * not range check any parameters.  This could be added or done before the function
 *
 * Parameters:
 *   Fpwm:         This is the desired PWM frequency in Hz
 *   Fosc:         This is the oscillator frequency in Hz
 *   dutyPercent:  The initial duty for the PWM.
 *
 * Returns:
 *   maxDuty:      This is the maximum value (100%) that the duty cycle can be
 *                 set to.  maxDuty/2 would give a 50% duty cycle.  The return
 *                 value is 0 then suitable setting could not be found.
 *
 * =============================================================================
 */
void setPWMFreq(unsigned short Fpwm, unsigned char dutyPercent)
{
	unsigned short pr2Val;
	unsigned char preScaler;
	unsigned short maxDuty;
	unsigned short duty;

	for (preScaler=1; preScaler<=16; preScaler *= 4)   //loop through all the valid prescalers
	{
	    pr2Val = FCY/Fpwm;
		pr2Val = pr2Val / preScaler -1;

		if (pr2Val < 256 && pr2Val > 1)  // as soon as we find a good one...break out of the loop
			break;
	}

	if (preScaler > 16)  // if this exceeds 16 we were not able to find values so return 0
		return;

	switch (preScaler)
	{
        case 1:
             T2CON = 0b00000100;
            break;
        case 4:
             T2CON = 0b00000101;
            break;
        default:
             T2CON = 0b00000111;
            break;
	}

	PR2 = pr2Val;

	maxDuty = SYS_FREQ / (Fpwm * preScaler);  // determine the maximum duty value for the registers

	duty = (maxDuty * dutyPercent) / 100;   // calculate the initial duty value from the percent

	setPWMDuty(duty);
}
/******************************************************************************/
/*Function Name:  HAL_Buzzer_PWM_Init                                         */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
#if 0
void HAL_Buzzer_PWM_Init(unsigned short frequency_Khz, unsigned char Duty)
{ 
    unsigned char u8_Period;
    unsigned char u8_Prescaler = 1;
    unsigned char u8_Duty; 
    CCP2CON = 0b00001100;  
    
    //calulate prescaler from 00 - 15 
    u8_Prescaler = (SYS_FREQ*10)/(frequency_Khz * 4 * 256);
    if(u8_Prescaler%10 > 5)
    {
        u8_Prescaler = u8_Prescaler/10 + 1;
    }
    else
    {
        u8_Prescaler = u8_Prescaler/10;
    }
    //PWM mode single output
    u8_Period = SYS_FREQ / ( frequency_Khz * 4 * u8_Prescaler ) - 1;
    PR2 = u8_Period;                                //Frequency at 486Hz. Anything over ~60Hz will get rid of any flicker
                                                    //PWM Period = [PR2 + 1]*4*Tosc*T2CKPS = [255 + 1] * 4 * (1 / 500KHz) * 1
    u8_Duty = (SYS_FREQ * Duty)/(frequency_Khz * u8_Prescaler *100);    
    CCPR2L = u8_Duty;                               //put the top 8 MSbs into CCPR2L    
    CCP2CONbits.DC2B = 0;                           //put the 2 LSbs into DC2B register to complete the 10bit resolution
    
    CCPTMRSbits.C2TSEL = 0b00;                      //select timer2 as PWM source
    T2CONbits.T2CKPS = u8_Prescaler - 1;            //prescaler     
}
#endif
/******************************************************************************/
/*Function Name:  HAL_Buzzer_On                                               */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void HAL_Buzzer_On(void)
{
    T2CONbits.TMR2ON = 1;                           //start the PWM  
}
/******************************************************************************/
/*Function Name:  HAL_Buzzer_Off                                              */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void HAL_Buzzer_Off(void)
{
    T2CONbits.TMR2ON = 0;                           //stop the PWM  
    PORTCbits.RC5 = 0;
}
#endif
