#include "stm32f4xx.h"                  // Device header
#include <stdint.h>
#include "delay.h"
#include "io.h"

int main(void) {
	uint32_t sw_state;
	
	ioa_init();
	ioc_init();

	while(1) {
		sw_state = sw_input();
		
		switch(sw_state) {
			case 0:
				led_on(RED_LED);
				break;
			case SW1:
				led_on(GREEN_LED);
				break;
			default:
				led_on(GREEN_LED|RED_LED);
				break;
		}
	}
	
	return 0;
}
