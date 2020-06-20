#include <stm32f4xx.h>
#include <stdint.h>

// user LED (LD2) is connected to PA5
// PA15 is just a random IO pin that maps to a header...
#define USER_LED_MD (1U<<10)
#define USER_LED_O  (1U<<5)
#define PIN_PA15_MD (1U<<30)
#define PIN_PA15_O  (1U<<15)
#define GPIOA_CLOCK (1U)

uint32_t user_stack[40];
uint32_t pa15_stack[40];

uint32_t* sp_userled = &user_stack[40]; // initialize to 40 because we want to start at bottom of stack (higher address)
uint32_t* sp_pa15 = &pa15_stack[40];

volatile uint32_t tick;
volatile uint32_t _tick;

void GPIO_Init(void);
void DelayS(uint32_t seconds);
void ledOn(void);
void ledOff(void);
void pa15On(void);
void pa15Off(void);

int userled_main(void) {
	while(1) {
		ledOn();
		DelayS(1);
		ledOff();
		DelayS(1);
	}
}

int pa15_main(void) {
	while(1) {
		pa15On();
		DelayS(1);
		pa15Off();
		DelayS(1);
	}
}

int main(void) {
	GPIO_Init();
	
	// creating stack for pa15_main thread
	*(--sp_pa15) = (1U << 24);                 // xPSR... set 24th bit to indicate thumb mode
	*(--sp_pa15) = (uint32_t)&pa15_main; // PC... set to execute pa15_main
	*(--sp_pa15) = 0x0000000DU;             // LR... random value
	*(--sp_pa15) = 0x0000000EU;             // R12... random value
	*(--sp_pa15) = 0x0000000AU;             // R3... random value
	*(--sp_pa15) = 0x0000000FU;             // R2... random value
	*(--sp_pa15) = 0x0000000EU;             // R1... random value
	*(--sp_pa15) = 0x0000000DU;             // R0... random value
	
	// creating stack for userLED_main thread
	*(--sp_userled) = (1U << 24);                 // xPSR... set 24th bit to indicate thumb mode
	*(--sp_userled) = (uint32_t)&userled_main; // PC... set to execute userled_main
	*(--sp_userled) = 0x0000000BU;             // LR... random value
	*(--sp_userled) = 0x0000000EU;             // R12... random value
	*(--sp_userled) = 0x0000000EU;             // R3... random value
	*(--sp_userled) = 0x0000000FU;             // R2... random value
	*(--sp_userled) = 0x0000000EU;             // R1... random value
	*(--sp_userled) = 0x0000000EU;             // R0... random value
	
	while(1);
	
	return 0;
}

void GPIO_Init(void) {
	RCC->AHB1ENR |= GPIOA_CLOCK;
	GPIOA->MODER |= USER_LED_MD|PIN_PA15_MD;
	
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
		GPIOA->ODR |= USER_LED_O;
}

void ledOff(void) {
		GPIOA->ODR &= ~USER_LED_O;
}

void pa15On(void) {
		GPIOA->ODR |= PIN_PA15_O;
}

void pa15Off(void) {
		GPIOA->ODR &= ~PIN_PA15_O;
}