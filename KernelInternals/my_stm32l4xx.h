#include <stdint.h>

#ifndef STM32L4XX_H     // make sure that standard stm32l4xx.h isn't already being used
#ifndef MY_STM32L4XX_H
#define MY_STM32L4XX_H

#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800
#define GPIOD_BASE 0x48000C00
#define GPIOE_BASE 0x48001000
#define GPIOF_BASE 0x48001400
#define GPIOG_BASE 0x48001800
#define GPIOH_BASE 0x48001C00

#define GPIOA ((volatile GPIO_t*) GPIOA_BASE)
#define GPIOB ((volatile GPIO_t*) GPIOB_BASE)
#define GPIOC ((volatile GPIO_t*) GPIOC_BASE)
#define GPIOD ((volatile GPIO_t*) GPIOD_BASE)
#define GPIOE ((volatile GPIO_t*) GPIOE_BASE)
#define GPIOF ((volatile GPIO_t*) GPIOF_BASE)
#define GPIOG ((volatile GPIO_t*) GPIOG_BASE)
#define GPIOH ((volatile GPIO_t*) GPIOH_BASE)
	
typedef struct {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;
} GPIO_t;

// RCC Peripherals
#define RCC_BASE 0x40021000

#define RCC ((volatile RCC_t*) RCC_BASE)

#define DMA2D_CLOCK (1U<<17)
#define TSC_CLCOK   (1U<<16)
#define CRC_CLOCK   (1U<<12)
#define FLASH_CLCOK (1U<<8)
#define DMA2_CLOCK  (1U<<1)
#define DMA1_CLOCK  (1U)

#define RNG_CLOCK   (1U<<18)
#define HASH_CLOCK  (1U<<17)
#define AES_CLOCK   (1U<<16)
#define DCMI_CLOCK  (1U<<14)
#define ADC_CLOCK   (1U<<13)
#define OTGFS_CLOCK (1U<<12)
#define GPIOI_CLOCK (1U<<8)
#define GPIOH_CLOCK (1U<<7)
#define GPIOG_CLOCK (1U<<6)
#define GPIOF_CLOCK (1U<<5)
#define GPIOE_CLOCK (1U<<4)
#define GPIOD_CLOCK (1U<<3)
#define GPIOC_CLOCK (1U<<2)
#define GPIOB_CLOCK (1U<<1)
#define GPIOA_CLOCK (1U)

typedef struct {
	uint32_t CR;
	uint32_t ICSCR;
	uint32_t CFGR;
	uint32_t PLLCFGR;
	uint32_t PLLSAI1CFGR;
	uint32_t PLLSAI2CFGR;
	uint32_t CIER;
	uint32_t CIFR;
	uint32_t CICR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t AHB3RSTR;
	uint32_t APB1RSTR1;
	uint32_t APB1RSTR2;
	uint32_t APB2RSTR;
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t AHB3ENR;
	uint32_t APB1ENR1;
	uint32_t APB1ENR2;
	uint32_t APB2ENR;
	uint32_t AHB1SMENR;
	uint32_t AHB2SMENR;
	uint32_t AHB3SMENR;
	uint32_t APB1SMENR1;
	uint32_t APB1SMENR2;
	uint32_t APB2SMENR;
	uint32_t CCIPR;
	uint32_t BDCR;
	uint32_t CSR;
	uint32_t CRRCR;
	uint32_t CCIPR2;
} RCC_t;

#endif
#endif