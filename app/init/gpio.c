#include <stdbool.h>
#include "gpio.h"

void gpio_setup(void) {
  // Clear CNF13[1:0] and MODE13[1:0]
  GPIOC_CRH &= ~(0xF << 20);

  // MODE13 = 10 (output 2 MHz), CNF13 = 00
  GPIOC_CRH |=  (0x2 << 20);
}

void set_led_state(bool state) {
  if (state) GPIOC_ODR |=  (1 << 13);
  else       GPIOC_ODR &= ~(1 << 13);
}
