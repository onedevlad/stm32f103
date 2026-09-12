#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include "memorymap.h"
#include "common.h"

#define GPIOA_CRH MMIO(GPIOA_BASE + 0x04)
#define GPIOC_CRH MMIO(GPIOC_BASE + 0x04)
#define GPIOC_ODR MMIO(GPIOC_BASE + 0x0C)

void enable_mco(void);
void setup_led(void);
void set_led_state(bool state);

#endif
