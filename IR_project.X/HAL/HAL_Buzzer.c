#ifndef __HAL_BUZZER_C__
#define __HAL_BUZZER_C__
/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>  //PIC hardware mapping
#include "..\system.h"
#include "HAL_Buzzer.h"
/******************************************************************************/
/*Function Name:  HAL_Buzzer_GPIO_Init                                        */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void HAL_Buzzer_GPIO_Init(void)
{
    TRISAbits.TRISA5 = 0;
    LATA5 = 0;                                      //PWM pin RA5       
}
/******************************************************************************/
/*Function Name:  HAL_Buzzer_PWM_Init                                         */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
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
}
#endif
