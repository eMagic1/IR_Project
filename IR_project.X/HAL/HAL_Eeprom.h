/* 
 * File:   HAL_Eeprom.h
 * Author: Minh
 *
 * Created on March 31, 2016, 8:26 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

void HAL_Eeprom_Write(int i_Address, unsigned char u8_Data);
void HAL_Eeprom_Read(int i_Address, unsigned char * p_u8_Data);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_EEPROM_H */

