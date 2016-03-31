#ifndef __HAL_OPTO_C__
#define __HAL_OPTO_C__

/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <xc.h>  //PIC hardware mapping
#include "HAL_OPTO.h"
/******************************************************************************/
/*Function Name:  GPIO_OPTOs_Init                                              */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void GPIO_OPTOs_Init(void)
{
    TRISCbits.TRISC0 = 0;                               //using pin as output
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    LATC = 0;
}
/******************************************************************************/
/*Function Name:  GPIO_OPTO_Set                                              */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void GPIO_OPTO_Set(unsigned char pin_number)
{
    LATC |= (1 << pin_number);
}
/******************************************************************************/
/*Function Name:  GPIO_Leds_Init                                              */
/*Author :        Minh Le                                                     */
/*Date:           28/03/2016                                                  */
/*Descripton:                                                                 */
/******************************************************************************/
void GPIO_OPTO_Clear(unsigned char pin_number)
{
    LATC &= ~(1 << pin_number);
}
#endif
