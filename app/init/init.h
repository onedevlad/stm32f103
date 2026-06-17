#ifndef INIT_H
#define INIT_H

#define RCC_BASE    0x40021000
#define FLASH_BASE  0x40022000

#define RCC_CR      (*(volatile uint32_t *)(RCC_BASE + 0x00))
#define RCC_CFGR    (*(volatile uint32_t *)(RCC_BASE + 0x04))
#define FLASH_ACR   (*(volatile uint32_t *)(FLASH_BASE + 0x00))
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))

/* FLASH_ACR bits */
#define FLASH_ACR_LATENCY_2WS 0x2 // 10
#define FLASH_ACR_PRFTBE      (1 << 4) // 1 0000

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH  (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR  (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

void setup_rcc(void);

#endif
