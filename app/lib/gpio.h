#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stddef.h>
#include "memorymap.h"
#include "common.h"

typedef struct {
  volatile uint32_t CRL;   // 0x00 pins 0-7 config
  volatile uint32_t CRH;   // 0x04 pins 8-15 config
  volatile uint32_t IDR;   // 0x08 input data
  volatile uint32_t ODR;   // 0x0C output data
  volatile uint32_t BSRR;  // 0x10 bit set/reset
  volatile uint32_t BRR;   // 0x14 bit reset
  volatile uint32_t LCKR;  // 0x18 config lock
} gpio_t;

typedef struct {
  gpio_t *port;
  uint8_t pin; // 0-15
} pin_t;

_Static_assert(offsetof(gpio_t, LCKR) == 0x18, "gpio_t layout wrong");

#define GPIOA ((gpio_t *)GPIOA_BASE)
#define GPIOC ((gpio_t *)GPIOC_BASE)

// CRL/CRH: each pin owns a 4-bit nibble, MODE in [1:0] and CNF in [3:2]
#define GPIO_CR_PIN  GENMASK(3, 0)
#define GPIO_CR_MODE GENMASK(1, 0)
#define GPIO_CR_CNF  GENMASK(3, 2)

// BSRR: write-only. Bits 15:0 set pin n, bits 31:16 reset pin n
#define GPIO_BSRR_BS(n) BIT(n)
#define GPIO_BSRR_BR(n) BIT((n) + 16)

// GPIO_CRH/L Values
#define GPIO_CNF_INPUT_ANALOG 0x0
#define GPIO_CNF_INPUT_FLOAT  0x1
#define GPIO_CNF_INPUT_PUPD   0x2
#define GPIO_CNF_OUTPUT_PP    0x0 // Push-Pull
#define GPIO_CNF_OUTPUT_OD    0x1 // Open Drain
#define GPIO_CNF_OUTPUT_AF_PP 0x2 // Alternate Function Push-Pull
#define GPIO_CNF_OUTPUT_AF_OD 0x3 // Alternate Function Open Drain

#define GPIO_MODE_INPUT         0x0
#define GPIO_MODE_OUTPUT_10_MHZ 0x1
#define GPIO_MODE_OUTPUT_2_MHZ  0x2
#define GPIO_MODE_OUTPUT_50_MHZ 0x3

void gpio_configure_pin(pin_t pin, uint32_t mode, uint32_t cnf);
void gpio_write_pin(pin_t pin, bool high);
bool gpio_read_pin(pin_t pin);

#endif
