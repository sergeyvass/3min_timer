/*
 * timer_3m.c
 *
 * Created: 06.03.2019 19:06:29
 * Author : Vasia
 */ 
#define F_CPU 449775UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/wdt.h> 
#include "main.h"
#include "WDT.h"

#define MIN_1 58000//1000   // Одна минута

ISR(PCINT0_vect)
{
	return;
}

ISR (WDT_vect)
{
	WDT_off();
}

void sleep_on()
{
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_mode();
}

#define MIN_CICL 7
void sleep_1min()
{
	for(uint8_t i=0; i<MIN_CICL; ++i)
	{
		WDT_on(sleep_8s);
		sleep_on();
	}
}

void timer_start()
{
	play_start();
	//_delay_ms(500);
	sleep_1min();
	play_tick();
	sleep_1min();
	play_tick();
	sleep_1min();
	play_finish();	
}

int main(void)
{
	WDT_off();
	init_pins();
	while(1)
	{
		sei();
		sleep_on();
		timer_start();		
	}
}


void init_pins()
{
	SET_REG(LED_DIR, LED_PIN);
	LED_OFF;
	
	SET_REG(BUZ_DIR, BUZ_PIN);
	SET_REG(BUZ_DIR, BUZ_PIN_2);
	CLR_REG(BUZ_PORT, BUZ_PIN);
	
	CLR_REG(BUT_DIR, BUT_PIN);
	PIN_INT_INIT;
	
}

uint8_t but_state()
{
	return (BUT_VAL & (1<<BUT_PIN));	
}

void BUZ_ON()
{
	
	TCCR0A|=1<<COM0A1 | 0<<COM0A0 | 1<<WGM01 | 1<<WGM00;
	TCCR0B|=0<<CS00 | 1<<CS02 | 0<<CS01 | 0<<WGM02;
	OCR0A=200;
}

void BUZ_OFF()
{
	TCCR0A=0;
	TCCR0B|=0<<CS00 | 0<<CS02 | 0<<CS01;
}

void play_tick()
{
	for(uint8_t j=0; j<60;++j)
	{
		BUZ_high();
		_delay_us(3800);
		BUZ_low();
		_delay_us(3800);
	}
}

void play_start()
{
	#define SIZE_MUSIC 4
	uint16_t gamma[5]={3800,3400,3000,2900,2600};
	uint8_t noti[SIZE_MUSIC]={1,2,3,4};	
	for(uint8_t i=0; i<SIZE_MUSIC; ++i)
	{
		for(uint16_t j=0; j<60;++j)
		{
			BUZ_high();
			switch(noti[i])
			{
				case 0:
				_delay_us(gamma[0]);
				break;
				case 1:
				_delay_us(gamma[1]);
				break;
				case 2:
				_delay_us(gamma[2]);
				break;
				case 3:
				_delay_us(gamma[3]);
				break;
				case 4:
				_delay_us(gamma[4]);
				break;
			}
			BUZ_low();
			switch(noti[i])
			{
				case 0:
				_delay_us(gamma[0]);
				break;
				case 1:
				_delay_us(gamma[1]);
				break;
				case 2:
				_delay_us(gamma[2]);
				break;
				case 3:
				_delay_us(gamma[3]);
				break;
				case 4:
				_delay_us(gamma[4]);
				break;
			}
		}
	}
}


void play_finish()
{
	uint16_t gamma[5]={3800,3400,3000,2900,2600};
	uint8_t noti[12]={3,2,1,0,4,4,3,2,1,0,4,4};
	for(uint8_t i=0; i<12; ++i)
	{
		for(uint16_t j=0; j<60;++j)
		{
			BUZ_high();
			switch(noti[i])
			{
				case 0:
					_delay_us(gamma[0]);	
					break;
				case 1:
					_delay_us(gamma[1]);
					break;
				case 2:
					_delay_us(gamma[2]);
					break;
				case 3:
					_delay_us(gamma[3]);
					break;
				case 4:
					_delay_us(gamma[4]);
					break;
			}
			BUZ_low();
			switch(noti[i])
			{
				case 0:
				_delay_us(gamma[0]);
				break;
				case 1:
				_delay_us(gamma[1]);
				break;
				case 2:
				_delay_us(gamma[2]);
				break;
				case 3:
				_delay_us(gamma[3]);
				break;
				case 4:
				_delay_us(gamma[4]);
				break;
			}
		}
	}
}

void BUZ_high()
{
	SET_REG(BUZ_PORT, BUZ_PIN);
	CLR_REG(BUZ_PORT, BUZ_PIN_2);
}

void BUZ_low()
{
	CLR_REG(BUZ_PORT, BUZ_PIN);
	SET_REG(BUZ_PORT, BUZ_PIN_2);
}