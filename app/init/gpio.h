#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdint.h>

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH  (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR  (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

void gpio_setup(void);
void set_led_state(bool state);

#endif
