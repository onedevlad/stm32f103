#include <stdbool.h>
#include "gpio.h"

void enable_mco(void) {
  GPIOA_CRH &= ~0xF;
  GPIOA_CRH |= 0x3; // MODE 11 - Output, 50MHz max
  GPIOA_CRH |= (0x2 << 2); // CNF 10 - AF output, Push-Pull
}

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
