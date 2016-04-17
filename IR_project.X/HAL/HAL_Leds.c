#ifndef __HAL_LEDS_C__
#define __HAL_LEDS_C__

/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>  //PIC hardware mapping
#include "HAL_Leds.h"
/******************************************************************************/
/*Function Name:  GPIO_Leds_Init                                              */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void GPIO_Leds_Init(void)
{
    TRISCbits.TRISC3 = 0;                               //using pin as output
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    LATC = 0;
}
/******************************************************************************/
/*Function Name:  GPIO_Leds_Init                                              */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void GPIO_Leds_Set(unsigned char pin_number)
{
    PORTC |= (1 << pin_number);
}
/******************************************************************************/
/*Function Name:  GPIO_Leds_Init                                              */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void GPIO_Leds_Clear(unsigned char pin_number)
{
    PORTC &= ~(1 << pin_number);
}
#endif