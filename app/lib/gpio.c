#include <stdbool.h>
#include "lib/gpio.h"
#include "lib/rcc.h"

void gpio_configure_pin(gpio_t *port, uint32_t pin, uint32_t mode, uint32_t cnf) {
  // Clock configuration
  _Static_assert(
    GPIOC_BASE - GPIOA_BASE == 2 * 0x400,
    "Each group of GPIO registers must be 0x400 bytes apart"
  );
  const uint32_t index = ((uintptr_t)port - GPIOA_BASE) / 0x400; // A=0, B=1, C=2...
  rcc_apb2_enable(RCC_APB2ENR_IOPAEN << index);
  (void)RCC->APB2ENR; // read back so the clock is running before first access

  // Pin configuration
  const uint32_t p = pin & 0xF; // Clamp to 0-15
  volatile uint32_t *cr = (p < 8) ? &port->CRL : &port->CRH;
  const uint32_t shift = (p & 7) * 4;
  const uint32_t config =
    FIELD_PREP(GPIO_CR_MODE, mode) |
    FIELD_PREP(GPIO_CR_CNF, cnf);

  MODIFY_REG(*cr, GPIO_CR_PIN << shift, config << shift);
}

void gpio_write_pin(gpio_t *port, uint32_t pin, bool high) {
  const uint32_t p = pin & 0xF; // clamp to 0-15
  port->BSRR = high ? GPIO_BSRR_BS(p) : GPIO_BSRR_BR(p);
}

bool gpio_read_pin(gpio_t *port, uint32_t pin) {
  return port->IDR & BIT(pin & 0xF);
}
