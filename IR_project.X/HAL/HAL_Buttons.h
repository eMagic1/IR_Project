/* 
 * File:   HAL_Buttons.h
 * Author: Minh
 *
 * Created on March 31, 2016, 8:23 PM
 */

#ifndef HAL_BUTTONS_H
#define	HAL_BUTTONS_H


typedef enum
{
    BUTTON_NONE = 0,
    BUTTON_1 = 1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_MAX = 0xFF,
            
}E_BUTTON_ID;
#ifdef	__cplusplus
extern "C" {
#endif
#ifdef __HAL_BUTTTON_C__    
void HAL_Button_Init( f_void_IRS * p_f_Handler);
void HAL_Button_Change_Edge(f_void_IRS * p_f_Handler);
void HAL_Button_Get_Flag(unsigned char * state);
void HAL_Button_Get_State(E_BUTTON_ID eButton_ID, unsigned char * state);
#else
extern void HAL_Button_Init(f_void_IRS * p_f_Handler);
extern void HAL_Button_Change_Edge(f_void_IRS * p_f_Handler);
extern void HAL_Button_Get_Flag(unsigned char * state);
extern void HAL_Button_Get_State(E_BUTTON_ID eButton_ID, unsigned char * state);
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_BUTTONS_H */

