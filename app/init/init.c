#include "system.h"
#include "init.h"

void setup_rcc(void) {
  // Enable HSE
  RCC_CR |= (1 << 16);
  while (!(RCC_CR & (1 << 17)));

  RCC_CFGR &= ~(0xF << 18);       // clear PLLMUL
  RCC_CFGR |= (0x7 << 18);        // set x9
  RCC_CFGR &= ~(1 << 16);         // clear PLLSRC
  RCC_CFGR |= (1 << 16);          // select HSE

  // Enable PLL
  RCC_CR |= (1 << 24); // PLLON
  while (!(RCC_CR & (1 << 25))); // PLLRDY

  // Configure Flash 2 wait state is correct for 72 MHz
  // Needs to be set before setting SYSCLK
  FLASH_ACR =
    FLASH_ACR_LATENCY_2WS |
    FLASH_ACR_PRFTBE;

  /* 4. Reset prescalers (AHB, APB1, APB2 = /1) */
  RCC_CFGR &= ~(
    (0xF << 4) |
    (0x7 << 8) |
    (0x7 << 11)
  );

  // APB1 /2
  RCC_CFGR |= (0x4 << 8); // PPRE1

  // Select PLL as SYSCLK
  RCC_CFGR &= ~(0x3 << 0); // Reset SW
  RCC_CFGR |= (0x2 << 0); // SW: PLL as SYSCLK

  while ((RCC_CFGR & (0x3 << 2)) != (0x2 << 2)); // SWS

  // Enable GPIOC
  RCC_APB2ENR |= (1 << 4);
}
