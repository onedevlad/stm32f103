#include "init_rcc.h"

void setup_rcc_1khz(void) {

}

void setup_rcc_8mhz(void) {
  // 1. Enable HSE (8MHz)
  uint32_t HSE_ON = (1 << 16);
  uint32_t HSE_RDY = (1 << 17);
  RCC_CR |= HSE_ON;
  while(!(RCC_CR & HSE_RDY));

  // 2. Reset prescalers
  RCC_CFGR &= ~(
    (0xF << 4) | // HPRE (AHB prescaler) = SYSCLK/1 (not divided)
    (0x7 << 8) | // APB1 (low-speed prescaler) = HCLK/1 (not divided)
    (0x7 << 11)  // APB2 (high-speed prescaler) = HCLK/1 (not divided)
  );

  // 3. Select HSE as SYSCLK
  // SW - System Clock Switch
  RCC_CFGR &= ~0x3; // Reset SW (00 Sets SYSCLK to HSI)
  RCC_CFGR |= 0x1; // SW (01 Sets SYSCLK to HSE)

  // Wait for System Clock Switch Status bits (SWS)
  while ((RCC_CFGR & (0x3 << 2)) != (0x1 << 2));

  // Enable GPIOC (LED) and GPIOA (PA8 MCO)
  RCC_APB2ENR |= (1 << 4) | (1 << 2);

  // Enable MCO on PA8
  RCC_CFGR &= ~(0x7 << 24);
  RCC_CFGR |= (0x4 << 24);
}

void setup_rcc_72mhz(void) {
  // 1. Enable HSE (8Mhz)
  // 7.3.1 Clock control register (RCC_CR)
  // Once HSE_ON is set, MCU reports on Bit 17 (HSE RDY)
  // when oscillator is stable
  uint32_t HSE_ON = (1 << 16);
  uint32_t HSE_RDY = (1 << 17);
  RCC_CR |= HSE_ON;
  while(!(RCC_CR & HSE_RDY));

  // 2. Configure PLL
  // 7.3.2 Clock configuration register (RCC_CFGR)

  // Zeroing out bits 18-21 (Effectively sets PLL to x2)
  RCC_CFGR &= ~(0xF << 18); // 0xF = 0b1111
  // Setting bits 18-21 to 0111 (PLL x9)
  RCC_CFGR |= (0x7 << 18);  // 0x7 = 0b111
  RCC_CFGR |= (1 << 16); // Bit 16 - PLLSRC. 0 - HSI/2, 1 - HSE

  // Enable PLL (Set PLLON) and wait for it (PLLRDY)
  uint32_t PLLON = (1 << 24);
  uint32_t PLLRDY = (1 << 25);

  RCC_CR |= PLLON;
  while (!(RCC_CR & PLLRDY));

  // 3. Configure Flash 2 wait state. 2WS is required for 72 MHz
  // Needs to be set before setting SYSCLK
  FLASH_ACR =
    FLASH_ACR_LATENCY_2WS |
    FLASH_ACR_PRFTBE;

  // Reset prescalers
  RCC_CFGR &= ~(
    (0xF << 4) | // HPRE (AHB prescaler) = SYSCLK/1 (not divided)
    (0x7 << 8) | // APB1 (low-speed prescaler) = HCLK/1 (not divided)
    (0x7 << 11)  // APB2 (high-speed prescaler) = HCLK/1 (not divided)
  );

  RCC_CFGR |= (0x4 << 8); // APB1 = HCLK/2

  // 4. Select PLL as SYSCLK
  // SW - System Clock Switch
  RCC_CFGR &= ~0x3; // Reset SW (00 Sets SYSCLK to HSI)
  RCC_CFGR |= 0x2; // SW (10 Sets SYSCLK to PLL)

  // Wait for System Clock Switch Status bit (SWS)
  while ((RCC_CFGR & (0x3 << 2)) != (0x2 << 2));

  // Enable GPIOC
  RCC_APB2ENR |= (1 << 4);
}
