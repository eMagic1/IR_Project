/* 
 * File:   APP_IR.h
 * Author: mle
 *
 * Created on March 29, 2016, 2:01 PM
 */

#ifndef APP_IR_H
#define	APP_IR_H

#define MAX_COUNT_ON_PLUSE 255// 3000*0.1 = 300ms ?
#ifdef	__cplusplus
extern "C" {
#endif
#ifdef __APP_IR_C__    
void APP_IR_Start_Read_Data(void);
#else
extern unsigned char IR_Has_Signal ;
extern unsigned char IR_Data[64];
extern unsigned char Number_Pulse ;
extern void APP_IR_Start_Read_Data(void);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* APP_IR_H */

