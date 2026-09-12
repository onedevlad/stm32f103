#ifndef INIT_RCC_H
#define INIT_RCC_H

#include <stdint.h>

#define RCC_BASE    0x40021000
#define FLASH_BASE  0x40022000

#define RCC_CR      (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CFGR    (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define FLASH_ACR   (*(volatile uint32_t *)(FLASH_BASE + 0x00))
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

/* FLASH_ACR bits */
#define FLASH_ACR_LATENCY_2WS 0x2 // 10
#define FLASH_ACR_PRFTBE      (1 << 4) // 1 0000

void setup_rcc_1khz(void);
void setup_rcc_8mhz(void);
void setup_rcc_72mhz(void);

#endif
