;This program will be somewhat different from the Udemy video b/c I am using ST Nucleo-F411RE
;Green user led: PA5
;RCC APB1 periph clock enable 0x40023840 (GPIOA: bit 0)
;GPIO A 0x40020000
;    Mode 0x40020000 (PA5: bits 11 and 10 (01=general output))
;    Output data 0x40020014 (PA5: bit 5)

RCC_AHB1ENR	EQU	0x40023830
GPIOA_MODER	EQU	0x40020000
GPIOA_ODR	EQU	0x40020014
	
GPIOA_EN	EQU	1

MODER5_OUT	EQU 1 << 10
MODER15_OUT	EQU	1 << 30
	
LED_GREEN	EQU 1 << 5
LED_RED		EQU	1 << 15
	
DELAY		EQU	0x000F
	
ONESEC		EQU	5333333

				AREA	|.text|,CODE,READONLY,ALIGN=2
				THUMB
				EXPORT __main

__main
	BL	GPIOA_Init
	
GPIOA_Init
	LDR		R0,=RCC_AHB1ENR		; load rcc_ahb1enr address
	LDR		R1,[R0]				; point r0 to rcc_ahb1enr
	ORR		R1,GPIOA_EN			; enable GPIO A peripheral clock
	STR		R1,[R0]				; commit changes to rcc_ahb1enr
	
	LDR		R0,=GPIOA_MODER		; load gpioa_moder
	LDR		R1,=(MODER15_OUT|MODER5_OUT)	; set port A5 and A15 to general purpose output
	STR		R1,[R0]				; commit changes to gpioa_moder
	MOV		R1,#0
	LDR		R2,=GPIOA_ODR
	
Blink
	MOVW	R1,#LED_GREEN
	STR		R1,[R2]
	LDR		R3,=ONESEC
	BL		Delay
	
	
	MOVW	R1,#LED_RED
	STR		R1,[R2]
	LDR		R3,=ONESEC
	BL		Delay
	B		Blink	
	
Delay
	SUBS	R3,R3,#1
	BNE		Delay
	BX		LR
	
	ALIGN
	END