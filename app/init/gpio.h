#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include "memorymap.h"
#include "common.h"

// GPIO Registers
#define GPIOA_CRH  MMIO(GPIOA_BASE + 0x04)
#define GPIOC_CRH  MMIO(GPIOC_BASE + 0x04)
#define GPIOC_BSRR MMIO(GPIOC_BASE + 0x10)

// GPIOA_CRH/L
#define GPIO_CRL_OFFSET  0x00
#define GPIO_CRH_OFFSET  0x04
#define GPIO_CR_PIN_MASK 0xF // width of one pin's MODE+CNF field
#define GPIO_MODE_SHIFT  0
#define GPIO_CNF_SHIFT   2

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

void gpio_configure_pin(uint32_t port_base, uint32_t pin, uint32_t mode, uint32_t cnf);
void gpio_enable_mco(void);
void gpio_setup_led(void);
void gpio_set_led_state(bool state);

#endif
