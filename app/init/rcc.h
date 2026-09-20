#ifndef INC_RCC_H
#define INC_RCC_H

#include <stdint.h>
#include <stddef.h>
#include "memorymap.h"
#include "common.h"

typedef struct {
  volatile uint32_t CR;       // 0x00
  volatile uint32_t CFGR;     // 0x04
  volatile uint32_t CIR;      // 0x08
  volatile uint32_t APB2RSTR; // 0x0C
  volatile uint32_t APB1RSTR; // 0x10
  volatile uint32_t AHBENR;   // 0x14
  volatile uint32_t APB2ENR;  // 0x18
  volatile uint32_t APB1ENR;  // 0x1C
  volatile uint32_t BDCR;     // 0x20
  volatile uint32_t CSR;      // 0x24
} rcc_t;

_Static_assert(offsetof(rcc_t, CSR) == 0x24, "rcc_t layout wrong");

#define RCC ((rcc_t *)RCC_BASE)

// CR
#define RCC_CR_HSE_ON  BIT(16)
#define RCC_CR_HSE_RDY BIT(17)
#define RCC_CR_PLLON   BIT(24)
#define RCC_CR_PLLRDY  BIT(25)

// CFGR
#define RCC_CFGR_SW      GENMASK(1, 0)   // system clock switch
#define RCC_CFGR_SWS     GENMASK(3, 2)   // system clock switch status
#define RCC_CFGR_HPRE    GENMASK(7, 4)   // AHB prescaler
#define RCC_CFGR_PPRE1   GENMASK(10, 8)  // APB1 prescaler
#define RCC_CFGR_PPRE2   GENMASK(13, 11) // APB2 prescaler
#define RCC_CFGR_PLLSRC  GENMASK(16, 16) // PLL source
#define RCC_CFGR_PLLMUL  GENMASK(21, 18) // PLL multiplier
#define RCC_CFGR_MCO     GENMASK(26, 24) // master clock out


// RCC_CFGR Values
#define RCC_CFGR_MCO_SYSCLK 0x4

#define RCC_CFGR_PLLMUL_PLL_CLK_MUL9 0x7

#define RCC_CFGR_PLLSRC_HSE_CLK  0x1
#define RCC_CFGR_PPRE1_HCLK_DIV2 0x4
#define RCC_CFGR_PPRE1_HCLK_DIV16 0x7

#define RCC_CFGR_PPRE2_HCLK_NO_DIV 0x0
#define RCC_CFGR_PPRE2_HCLK_DIV16 0x7

#define RCC_CFGR_PPRE1_HCLK_NO_DIV 0x0

#define RCC_CFGR_HPRE_NO_DIV 0x0
#define RCC_CFGR_HPRE_DIV512 0xF

// RCC_APB2ENR: APB2 peripheral clock enable register 
#define RCC_APB2ENR_IOPEEN BIT(6)
#define RCC_APB2ENR_IOPDEN BIT(5)
#define RCC_APB2ENR_IOPCEN BIT(4)
#define RCC_APB2ENR_IOPBEN BIT(3)
#define RCC_APB2ENR_IOPAEN BIT(2)
#define RCC_APB2ENR_VALID_BITS (\
  RCC_APB2ENR_IOPAEN |\
  RCC_APB2ENR_IOPBEN |\
  RCC_APB2ENR_IOPCEN |\
  RCC_APB2ENR_IOPDEN |\
  RCC_APB2ENR_IOPEEN  \
)

// RCC_APB1ENR: APB1 peripheral clock enable register 
#define RCC_APB1ENR_TIM2EN BIT(0)
#define RCC_APB1ENR_VALID_BITS (\
  RCC_APB1ENR_TIM2EN \
)

// SWS: System clock switch status
#define RCC_CFGR_SWS_SYSCLKSEL_HSICLK		0x0
#define RCC_CFGR_SWS_SYSCLKSEL_HSECLK		0x1
#define RCC_CFGR_SWS_SYSCLKSEL_PLLCLK		0x2

// SW: System clock switch
#define RCC_CFGR_SW_SYSCLKSEL_HSICLK		0x0
#define RCC_CFGR_SW_SYSCLKSEL_HSECLK		0x1
#define RCC_CFGR_SW_SYSCLKSEL_PLLCLK		0x2

void rcc_setup_snail_pace(void);
void rcc_setup_8mhz(void);
void rcc_setup_72mhz(void);

void rcc_apb2_enable(uint32_t bits);
void rcc_apb1_enable(uint32_t bits);
void rcc_set_mco_source(uint32_t source);

#endif
