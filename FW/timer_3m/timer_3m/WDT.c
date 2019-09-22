#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "WDT.h"

void WDT_off(void)
{
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCR = 0x00;
	sei();
}

void WDT_on(wdt_time time)
{
	uint8_t temp;
	cli();
	wdt_reset();
	/* Clear WDRF in MCUSR */
	MCUSR &= ~(1<<WDRF);
	switch(time)
	{
		case sleep_16_ms:
		temp = (1<<WDTIE);
		break;
		case sleep_32_ms:
		temp = (1<<WDTIE) | (1<< WDP0);
		break;
		case sleep_64_ms:
		temp = (1<<WDTIE) | (1<< WDP1);
		break;
		case sleep_125_ms:
		temp = (1<<WDTIE) | (1<< WDP1) | (1<< WDP0);
		break;
		case sleep_250_ms:
		temp = (1<<WDTIE) | (1<< WDP2);
		break;
		case sleep_1_s:
		temp = (1<<WDTIE) | (1<< WDP1) | (1<< WDP2);
		break;
		case sleep_8s:
		temp = (1<<WDTIE) | (1<< WDP3) | (1<< WDP0);
		break;
		default:
		//PRINT_STR("Err WDT_ON\r\n");
		return;
		break;
	}
	/* Write logical one to WDCE and WDE */
	/* Keep old prescaler setting to prevent unintentional time-out */
	WDTCR |= (1<<WDCE) | (1<<WDE);
	WDTCR = temp;                   // 4 clk cicls
	sei();
}
