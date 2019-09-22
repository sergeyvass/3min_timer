/*
 * main.h
 *
 * Created: 06.03.2019 19:09:09
 *  Author: Vasia
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define LED_DIR DDRB
#define BUZ_DIR DDRB
#define BUT_DIR DDRB

#define LED_PORT PORTB 
#define BUZ_PORT PORTB
#define BUT_PORT PORTB
#define BUT_VAL  PINB

#define LED_PIN 4
#define BUZ_PIN 0
#define BUZ_PIN_2 1
#define BUT_PIN 3

#define SET_REG(REG,BIT) REG|=1<<BIT
#define CLR_REG(REG,BIT) REG&=~(1<<BIT)

#define LED_ON LED_PORT&=~(1<<LED_PIN)
#define LED_OFF LED_PORT|=1<<LED_PIN

#define PIN_INT_INIT MCUCR &=~((1<<ISC01) | (1<< ISC00)); GIMSK |= 1<<PCIE; PCMSK|= 1<<PCINT3



void init_pins();
uint8_t but_state();
void BUZ_ON();
void BUZ_OFF();
void play_finish();
void play_start();
void WDT_off();
void play_tick();
void BUZ_high();
void BUZ_low();




#endif /* MAIN_H_ */