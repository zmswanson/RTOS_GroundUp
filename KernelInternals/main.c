#include <stdint.h>
#include "stm32l4xx.h"

#define USER_LED_BIT (1U<<26)
#define USER_LED     (1U<<13)
#define GPIOB_CLOCK  (1U<<1)

// Instructor provides video using STM32-Discovery board
// My source code will be modified for the STM32-Nucleo-64 board
// User LED (LD2) is connected to PA5 through SB42 and to PB13 through SB29
//     Let's use PB13 connection until we can verify user LED connection

volatile uint32_t tick;
volatile uint32_t _tick;

void GPIO_Init(void);
void DelayS(uint32_t seconds);
void ledOn(void);
void ledOff(void);

int main(void) {
	
	while(1) {
		ledOn();
		DelayS(1);
		ledOff();
		DelayS(1);
	}
}

void GPIO_Init(void) {
	RCC->AHB2ENR |= GPIOB_CLOCK; // enable the GPIO B clock from RCC
	GPIOB->MODER |= USER_LED_BIT;    // set PB13 (user led) to general output mode
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100U);
	__enable_irq();
}

void SysTick_Handler(void) {
	++tick;
}

uint32_t getTick(void) {
	__disable_irq();
	_tick = tick;
	__enable_irq();
	
	return _tick;
}

void DelayS(uint32_t seconds) {
	seconds *= 100;
	uint32_t temp = getTick();
	while((getTick() - temp) < seconds);
}

void ledOn(void) {
	GPIOB->ODR |= USER_LED;
}

void ledOff(void) {
	GPIOB->ODR &= ~USER_LED;
}