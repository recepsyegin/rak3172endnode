/*
 * tarih.c
 *
 *  Created on: May 9, 2025
 *      Author: recep
 */


#include "tarih.h"


void Init_SystemTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute,
									uint8_t second)
{

	struct tm timeInfo = {0};

	timeInfo.tm_year = year - 1900;	// 1900 bazli yil
	timeInfo.tm_mon = month - 1;	// 0-11
	timeInfo.tm_mday = day;
	timeInfo.tm_hour = hour;
	timeInfo.tm_min = minute;
	timeInfo.tm_sec = second;

	time_t unix_time = mktime(&timeInfo);	// Unix epoch 1970
	time_t epoch_2000 = 946684800;			// 01-01-2000 UTC

	uint32_t seconds_since_2000 = (uint32_t)(unix_time - epoch_2000);

	SysTime_t sysTime =
	{
			.Seconds = seconds_since_2000,
			.SubSeconds = 0
	};

	SysTimeSet(sysTime);
}

void Init_SystemTime_UTC(uint16_t year, uint8_t month, uint8_t day,
                         uint8_t hour, uint8_t minute, uint8_t second)
{
    struct tm timeInfo = {0};

    timeInfo.tm_year = year - 1900;  	 // Yıl: 1900 bazlı
    timeInfo.tm_mon  = month - 1;    	 // Ay : 0-11
    timeInfo.tm_mday = day;
    timeInfo.tm_hour = hour;
    timeInfo.tm_min  = minute;
    timeInfo.tm_sec  = second;

    time_t unix_time;

    #ifdef HAVE_TIMEGM  				 // Eğer derleyicide varsa kullanılır.
        unix_time = timegm(&timeInfo);
    #else
        								 // Gömülü sistemlerde timegm genelde yoktur — mktime UTC gibi çalışır.
        unix_time = mktime(&timeInfo);
    #endif

    const time_t epoch_2000 = 946684800; // 01.01.2000 00:00:00 UTC

    uint32_t seconds_since_2000 = (uint32_t)(unix_time - epoch_2000);

    SysTime_t sysTime =
    {
        .Seconds = seconds_since_2000,
        .SubSeconds = 0
    };

    SysTimeSet(sysTime);
}

DateTime_t Get_SystemTime_UTC(void)
{
	SysTime_t sysTime = SysTimeGet();

	const time_t epoch_2000 = 946684800;
	time_t unix_time = sysTime.Seconds + epoch_2000;

	struct tm* timeInfo = gmtime(&unix_time); // UTC Dönüşümü

	DateTime_t now;
	now.year   = timeInfo->tm_year + 1900;
	now.month  = timeInfo->tm_mon + 1;
	now.day    = timeInfo->tm_mday;
	now.hour   = timeInfo->tm_hour;
	now.minute = timeInfo->tm_min;
	now.second = timeInfo->tm_sec;

	return now;
}

