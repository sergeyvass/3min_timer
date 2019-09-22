/*
 * WDT.h
 *
 * Created: 11.03.2019 16:09:51
 *  Author: Vasia
 */ 


#ifndef WDT_H_
#define WDT_H_

typedef enum
{
	sleep_16_ms,
	sleep_32_ms,
	sleep_64_ms,
	sleep_125_ms,
	sleep_250_ms,
	sleep_1_s,
	sleep_8s
} wdt_time;

void WDT_on(wdt_time time);

#endif /* WDT_H_ */