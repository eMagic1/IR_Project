/* 
 * File:   APP_Button.h
 * Author: mle
 *
 * Created on March 29, 2016, 3:48 PM
 */

#ifndef APP_BUTTON_H
#define	APP_BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifdef __APP_BUTTON_C__
void Button_IRQ_Handler(void);
#else
extern void Button_IRQ_Handler(void);
extern unsigned char Button_Press ;
extern unsigned char Button_Release ;
extern unsigned char Button_3s ;
#endif

#ifdef	__cplusplus
}
#endif

#endif	

