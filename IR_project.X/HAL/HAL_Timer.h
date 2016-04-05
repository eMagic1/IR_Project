/* 
 * File:   HAL_Timer.h
 * Author: Minh
 *
 * Created on April 2, 2016, 5:22 PM
 */

#ifndef HAL_TIMER_H
#define	HAL_TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
void HAL_Debonce(void);
void HAL_Timer_0_Init(unsigned short timer_ms, f_void_IRS * f_p_func);
void HAL_Timer0_Reset(void);
void HAL_Timer0_Stop(void);

void HAL_Timer1_Init(unsigned short timer_ms, f_void_IRS * f_p_func);
void HAL_Timer1_Reset(void);
void HAL_Timer1_Stop(void);

void HAL_Timer46_Init(void);
void HAL_Timer4_Get_TickCount(unsigned short * value);
void HAL_Timer4_Reset(void);
void HAL_Timer4_Stop(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_TIMER_H */

