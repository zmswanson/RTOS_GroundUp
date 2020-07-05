#ifndef IO_H
#define IO_H

#include <stdint.h>

/* Green user led PA5, red ext. led PA6 */
#define GREEN_LED (1U << 5)
#define RED_LED   (1U << 6)

/* User button PC13 */
#define SW1 (1U << 13)

#define MODER5  (1U << 10)
#define MODER6  (1U << 12)
#define MODER13 (1U << 26)

#define IOCLKA (1U)
#define IOCLKC (1U << 2)

uint32_t sw_input(void);
void led_on(uint32_t led);
void ioa_init(void);
void ioc_init(void);
#endif