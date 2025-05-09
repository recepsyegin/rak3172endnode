/*
 * tarih.h
 *
 *  Created on: May 9, 2025
 *      Author: recep
 */

#ifndef INC_TARIH_H_
#define INC_TARIH_H_

//#include "main.h"
//#include "dma.h"
//#include "app_lorawan.h"
#include "gpio.h"
#include <time.h>
#include "stm32_systime.h"

typedef struct
{
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
} DateTime_t;



void Init_SystemTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute,
									uint8_t second);

void Init_SystemTime_UTC(uint16_t year, uint8_t month, uint8_t day,
                         uint8_t hour, uint8_t minute, uint8_t second);


DateTime_t Get_SystemTime_UTC(void);














#endif /* INC_TARIH_H_ */
