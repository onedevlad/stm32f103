#include <stdbool.h>
#include "gpio.h"
#include "rcc.h"

#define MCO_PIN 8  // PA8
#define LED_PIN 13 // PC13
#define PWM_PIN 0  // PA0 (TIM2_CH1)

void gpio_configure_pin(gpio_t *port, uint32_t pin, uint32_t mode, uint32_t cnf) {
  const uint32_t p = pin & 0xF; // Clamp to 0-15
  volatile uint32_t *cr = (p < 8) ? &port->CRL : &port->CRH;
  const uint32_t shift = (p & 7) * 4;
  const uint32_t config =
    FIELD_PREP(GPIO_CR_MODE, mode) |
    FIELD_PREP(GPIO_CR_CNF, cnf);

  MODIFY_REG(*cr, GPIO_CR_PIN << shift, config << shift);
}

void gpio_enable_mco(void) {
  rcc_apb2_enable(RCC_APB2ENR_IOPAEN);
  rcc_set_mco_source(RCC_CFGR_MCO_SYSCLK);

  gpio_configure_pin(GPIOA, MCO_PIN, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_AF_PP);
}

void gpio_setup_led(void) {
  rcc_apb2_enable(RCC_APB2ENR_IOPCEN);
  gpio_configure_pin(GPIOC, LED_PIN, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PP);
}

void gpio_set_led_state(bool state) {
  GPIOC->BSRR = state
    ? GPIO_BSRR_BS(LED_PIN)
    : GPIO_BSRR_BR(LED_PIN);
}

void gpio_setup_pwm(void) {
  rcc_apb1_enable(RCC_APB1ENR_TIM2EN);
  rcc_apb2_enable(RCC_APB2ENR_IOPAEN);
  gpio_configure_pin(GPIOA, PWM_PIN, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_AF_PP);
}
