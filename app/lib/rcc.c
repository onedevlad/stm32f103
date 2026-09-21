#include "lib/rcc.h"
#include "lib/flash.h"

static uint32_t rcc_get_sysclk_source(void) {
  return FIELD_GET(RCC_CFGR_SWS, RCC->CFGR);
}

static void rcc_set_sysclk_source(uint32_t source) {
  source &= 0x3;
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, FIELD_PREP(RCC_CFGR_SW, source));
  // Wait for System Clock Switch Status bits (SWS)
  while(rcc_get_sysclk_source() != source);
}

static void enable_hse(void) {
  // 1. Enable HSE (8Mhz)
  // 7.3.1 Clock control register (RCC_CR)
  // Once HSE_ON is set, MCU reports on Bit 17 (HSE RDY)
  // when oscillator is stable
  RCC->CR |= RCC_CR_HSE_ON;
  while(!(RCC->CR & RCC_CR_HSE_RDY));
}

static void set_prescalers(uint32_t ahb, uint32_t apb1, uint32_t apb2) {
  // Mask defaults:
  // HPRE (AHB prescaler)        = SYSCLK/1 (not divided)
  // APB1 (low-speed prescaler)  = HCLK/1   (not divided)
  // APB2 (high-speed prescaler) = HCLK/1   (not divided)
  MODIFY_REG(
    RCC->CFGR,
    RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
    FIELD_PREP(RCC_CFGR_HPRE,  ahb)  |
    FIELD_PREP(RCC_CFGR_PPRE1, apb1) |
    FIELD_PREP(RCC_CFGR_PPRE2, apb2)
  );
}

void rcc_apb2_enable(uint32_t source) {
  RCC->APB2ENR |= RCC_APB2ENR_VALID_BITS & source;
}

void rcc_apb1_enable(uint32_t source) {
  RCC->APB1ENR |= RCC_APB1ENR_VALID_BITS & source;
}

void rcc_set_mco_source(uint32_t source) {
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, FIELD_PREP(RCC_CFGR_MCO, source));
}

// Lowest speed this MCU can go. ~15'625HZ on HCLK, sub-1kHZ on APB1
void rcc_setup_snail_pace(void) {
  set_prescalers(
    RCC_CFGR_HPRE_DIV512,
    RCC_CFGR_PPRE1_HCLK_DIV16,
    RCC_CFGR_PPRE2_HCLK_DIV16
  );

  rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_HSICLK);
}

void rcc_setup_8mhz(void) {
  enable_hse();

  set_prescalers(
    RCC_CFGR_HPRE_NO_DIV,
    RCC_CFGR_PPRE1_HCLK_NO_DIV,
    RCC_CFGR_PPRE2_HCLK_NO_DIV
  );

  rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_HSECLK);
}

void rcc_setup_72mhz(void) {
  enable_hse();

  // 2. Configure PLL
  // 7.3.2 Clock configuration register (RCC_CFGR)
  MODIFY_REG(
    RCC->CFGR,
    RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC,
    FIELD_PREP(RCC_CFGR_PLLMUL, RCC_CFGR_PLLMUL_PLL_CLK_MUL9) |
    FIELD_PREP(RCC_CFGR_PLLSRC, RCC_CFGR_PLLSRC_HSE_CLK)
  );

  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY));

  // 3. Configure Flash 2 wait state. 2WS is required for 72 MHz
  // Needs to be set before setting SYSCLK
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2WS);
  FLASH->ACR |= FLASH_ACR_PRFTBE;

  set_prescalers(
    RCC_CFGR_HPRE_NO_DIV,
    RCC_CFGR_PPRE1_HCLK_DIV2,
    RCC_CFGR_PPRE2_HCLK_NO_DIV
  );
  rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_PLLCLK);
}
