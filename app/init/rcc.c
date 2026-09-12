#include "rcc.h"

void rcc_apb2_enable(uint32_t source) {
  RCC_APB2ENR |= RCC_APB2ENR_VALID_BITS & source;
}

void rcc_set_mco_source(uint32_t source) {
  const uint32_t bits = (RCC_CFGR_MCO >> RCC_CFGR_MCO_SHIFT) & source;
  RCC_CFGR = (RCC_CFGR & ~RCC_CFGR_MCO) | (bits << RCC_CFGR_MCO_SHIFT);
}

static uint32_t rcc_get_sysclk_source(void) {
  return (RCC_CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_SHIFT;
}

static void rcc_set_sysclk_source(uint32_t source) {
  const uint32_t bits = (RCC_CFGR_SW >> RCC_CFGR_SW_SHIFT) & source;
  RCC_CFGR = (RCC_CFGR & ~RCC_CFGR_SW) | (bits << RCC_CFGR_SW_SHIFT);
  // Wait for System Clock Switch Status bits (SWS)
  while(rcc_get_sysclk_source() != source);
}

void rcc_setup_1khz(void) {

}

void rcc_setup_8mhz(void) {
  // 1. Enable HSE (8MHz)
  RCC_CR |= RCC_CR_HSE_ON;
  while(!(RCC_CR & RCC_CR_HSE_RDY));

  // 2. Reset prescalers
  RCC_CFGR &= ~(
    RCC_CFGR_HPRE  | // HPRE (AHB prescaler)        = SYSCLK/1 (not divided)
    RCC_CFGR_PPRE1 | // APB1 (low-speed prescaler)  = HCLK/1   (not divided)
    RCC_CFGR_PPRE2   // APB2 (high-speed prescaler) = HCLK/1   (not divided)
  );

  // 3. Select HSE as SYSCLK
  rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_HSECLK);
}

void rcc_setup_72mhz(void) {
  // 1. Enable HSE (8Mhz)
  // 7.3.1 Clock control register (RCC_CR)
  // Once HSE_ON is set, MCU reports on Bit 17 (HSE RDY)
  // when oscillator is stable
  RCC_CR |= RCC_CR_HSE_ON;
  while(!(RCC_CR & RCC_CR_HSE_RDY));

  // 2. Configure PLL
  // 7.3.2 Clock configuration register (RCC_CFGR)

  // Zeroing out bits 18-21 (Effectively sets PLL to x2)
  RCC_CFGR &= ~RCC_CFGR_PLLMUL; // 0xF = 0b1111
  // Setting bits 18-21 to 0111 (PLL x9)
  RCC_CFGR |= (RCC_CFGR_PLLMUL_PLL_CLK_MUL9 << RCC_CFGR_PLLMUL_SHIFT);  // 0x7 = 0b111
  RCC_CFGR |= RCC_CFGR_PLLSRC_HSE_CLK << RCC_CFGR_PLLSRC_SHIFT; // Bit 16 - PLLSRC. 0 - HSI/2, 1 - HSE

  // Enable PLL (Set PLLON) and wait for it (PLLRDY)
  RCC_CR |= RCC_CR_PLLON;
  while (!(RCC_CR & RCC_CR_PLLRDY));

  // 3. Configure Flash 2 wait state. 2WS is required for 72 MHz
  // Needs to be set before setting SYSCLK
  FLASH_ACR =
    FLASH_ACR_LATENCY_2WS |
    FLASH_ACR_PRFTBE;

  // Reset prescalers
  RCC_CFGR &= ~(
    RCC_CFGR_HPRE  | // HPRE (AHB prescaler)        = SYSCLK/1 (not divided)
    RCC_CFGR_PPRE1 | // APB1 (low-speed prescaler)  = HCLK/1 (not divided)
    RCC_CFGR_PPRE2   // APB2 (high-speed prescaler) = HCLK/1 (not divided)
  );

  RCC_CFGR |= (RCC_CFGR_PPRE1_HCLK_DIV2 << RCC_CFGR_PPRE1_SHIFT); // APB1 = HCLK/2

  // 4. Select PLL as SYSCLK
  rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_PLLCLK);
}
