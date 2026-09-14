#ifndef INC_RCC_H
#define INC_RCC_H

#include "memorymap.h"
#include "common.h"

// RCC Registers
#define RCC_CR      MMIO(RCC_BASE + 0x00)
#define RCC_CFGR    MMIO(RCC_BASE + 0x04)
#define RCC_APB2ENR MMIO(RCC_BASE + 0x18)

// RCC_CR Values
#define RCC_CR_PLLRDY  BIT25
#define RCC_CR_PLLON   BIT24
#define RCC_CR_HSE_RDY BIT17
#define RCC_CR_HSE_ON  BIT16

// RCC_CFGR Values
#define RCC_CFGR_MCO_SHIFT 24
#define RCC_CFGR_MCO (0x7 << RCC_CFGR_MCO_SHIFT)
#define RCC_CFGR_MCO_SYSCLK 0x4

#define RCC_CFGR_PLLMUL_SHIFT 18
#define RCC_CFGR_PLLMUL (0xF << RCC_CFGR_PLLMUL_SHIFT)

#define RCC_CFGR_PLLSRC_SHIFT 16
#define RCC_CFGR_PLLSRC (0x1 << RCC_CFGR_PLLSRC_SHIFT)

#define RCC_CFGR_PLLMUL_PLL_CLK_MUL9 0x7

#define RCC_CFGR_PLLSRC_HSE_CLK  0x1
#define RCC_CFGR_PPRE1_HCLK_DIV2 0x4
#define RCC_CFGR_PPRE1_HCLK_DIV16 0x7

#define RCC_CFGR_PPRE2_SHIFT 11
#define RCC_CFGR_PPRE2 (0x7 << RCC_CFGR_PPRE2_SHIFT)

#define RCC_CFGR_PPRE2_HCLK_NO_DIV 0x0
#define RCC_CFGR_PPRE2_HCLK_DIV16 0x7

#define RCC_CFGR_PPRE1_SHIFT 8
#define RCC_CFGR_PPRE1 (0x7 << RCC_CFGR_PPRE1_SHIFT)

#define RCC_CFGR_PPRE1_HCLK_NO_DIV 0x0

#define RCC_CFGR_HPRE_SHIFT 4
#define RCC_CFGR_HPRE (0xF << RCC_CFGR_HPRE_SHIFT)

#define RCC_CFGR_HPRE_NO_DIV 0x0
#define RCC_CFGR_HPRE_DIV512 0xF

#define RCC_CFGR_SWS_SHIFT 2
#define RCC_CFGR_SWS       (3 << RCC_CFGR_SWS_SHIFT)

#define RCC_CFGR_SW_SHIFT 0
#define RCC_CFGR_SW       (3 << RCC_CFGR_SW_SHIFT)

// RCC_APB2ENR: APB2 peripheral clock enable register 
#define RCC_APB2ENR_IOPEEN BIT6
#define RCC_APB2ENR_IOPDEN BIT5
#define RCC_APB2ENR_IOPCEN BIT4
#define RCC_APB2ENR_IOPBEN BIT3
#define RCC_APB2ENR_IOPAEN BIT2
#define RCC_APB2ENR_VALID_BITS (\
  RCC_APB2ENR_IOPAEN |\
  RCC_APB2ENR_IOPBEN |\
  RCC_APB2ENR_IOPCEN |\
  RCC_APB2ENR_IOPDEN |\
  RCC_APB2ENR_IOPEEN  \
)

// SWS: System clock switch status
#define RCC_CFGR_SWS_SYSCLKSEL_HSICLK		0x0
#define RCC_CFGR_SWS_SYSCLKSEL_HSECLK		0x1
#define RCC_CFGR_SWS_SYSCLKSEL_PLLCLK		0x2

// SW: System clock switch
#define RCC_CFGR_SW_SYSCLKSEL_HSICLK		0x0
#define RCC_CFGR_SW_SYSCLKSEL_HSECLK		0x1
#define RCC_CFGR_SW_SYSCLKSEL_PLLCLK		0x2

#define FLASH_ACR   MMIO(FLASH_BASE + 0x00)

/* FLASH_ACR bits */
#define FLASH_ACR_LATENCY_0WS 0x00
#define FLASH_ACR_LATENCY_1WS 0x01
#define FLASH_ACR_LATENCY_2WS 0x02
#define FLASH_ACR_PRFTBE      BIT4

void rcc_setup_snail_pace(void);
void rcc_setup_8mhz(void);
void rcc_setup_72mhz(void);

void rcc_apb2_enable(uint32_t bits);
void rcc_set_mco_source(uint32_t source);

#endif
