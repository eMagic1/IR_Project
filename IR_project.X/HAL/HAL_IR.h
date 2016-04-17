/* 
 * File:   HAL_Timer.h
 * Author: Minh
 *
 * Created on April 2, 2016, 5:22 PM
 */

#ifndef HAL_IRRRR_H
#define	HAL_IRRRR_H

#ifdef	__cplusplus
extern "C" {
#endif

void HAL_Init_IR_IO(void);
void HAL_Set_Trigger_Edg_IR(unsigned char bl_Rasing_Or_Falling, f_void_IRS * f_p_handler);
void HAL_IR_Set_Overload_Handler(f_void_IRS * f_p_handler);
#ifdef	__cplusplus
}
#endif

#endif	/* HAL_TIMER_H */

