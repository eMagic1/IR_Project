/* 
 * File:   HAL_Buttons.h
 * Author: Minh
 *
 * Created on March 31, 2016, 8:23 PM
 */

#ifndef HAL_BUTTONS_H
#define	HAL_BUTTONS_H
typedef void (*f_void_IRS)(void);

typedef enum
{
    BUTTON_1 = 0,
    BUTTON_2,
    BUTTON_3,
            
}E_BUTTON_ID;
#ifdef	__cplusplus
extern "C" {
#endif
void HAL_Button_Init(f_void_IRS * p_f_Handler);
void Get_Button_State(E_BUTTON_ID eButton_ID, unsigned char * state);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_BUTTONS_H */

