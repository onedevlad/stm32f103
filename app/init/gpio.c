#include <stdbool.h>
#include "gpio.h"
#include "rcc.h"

#define MCO_PIN 8  // PA8
#define LED_PIN 13 // PC13

void gpio_configure_pin(uint32_t port, uint32_t pin, uint32_t mode, uint32_t cnf) {
  const uint32_t p = pin & 0xF; // Clamp to 0-15
  const uint32_t offset = (p < 8) ? GPIO_CRL_OFFSET : GPIO_CRH_OFFSET;
  const uint32_t shift = ((p < 8) ? p : p - 8) * 4;
  const uint32_t mask = GPIO_CR_PIN_MASK << shift;
  const uint32_t config = ((mode & 0x3) << GPIO_MODE_SHIFT) | ((cnf & 0x3) << GPIO_CNF_SHIFT);

  volatile uint32_t *cr = (volatile uint32_t *)(port + offset);
  *cr = (*cr & ~mask) | (config << shift);
}

void gpio_enable_mco(void) {
  rcc_apb2_enable(RCC_APB2ENR_IOPAEN);
  rcc_set_mco_source(RCC_CFGR_MCO_SYSCLK);

  gpio_configure_pin(GPIOA_BASE, MCO_PIN, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_AF_PP);
}

void gpio_setup_led(void) {
  rcc_apb2_enable(RCC_APB2ENR_IOPCEN);
  gpio_configure_pin(GPIOC_BASE, LED_PIN, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PP);
}

void gpio_set_led_state(bool state) {
  GPIOC_BSRR = state
    ? (1 << LED_PIN)         // Bit Set
    : (1 << (LED_PIN + 16)); // Bit Reset
}
