#include "stm32f4xx.h"                  // Device header
#include <stdint.h>
#include "io.h"
#include "delay.h"

uint32_t sw_input(void) {
	return (GPIOC->IDR & SW1);
}

void led_on(uint32_t led) {
	GPIOA->ODR = led;
	delay(2000000);
	GPIOA->ODR &= ~led;
}

void ioa_init(void) {
	RCC->AHB1ENR |= (IOCLKA); //enable GPIO A and C clocks
	GPIOA->MODER |= (MODER5|MODER6); //set ports A5 and A15 to general output
}

void ioc_init(void) {
	RCC->AHB1ENR |= (IOCLKC); //enable GPIO A and C clocks
	//port C13 is already in input (reset state)
}
