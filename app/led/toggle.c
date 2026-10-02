#include <stdbool.h>
#include <stdint.h>
#include "lib/gpio.h"
#include "lib/systick.h"
#include "lib/exti.h"
#include "led/toggle.h"

static const pin_t BTN = { GPIOA, 1 };
static const pin_t LED = { GPIOC, 13 };

static void set_led(bool on) {
  gpio_write_pin(LED, !on);
}

void setup_led_toggle(void) {
  gpio_configure_pin(LED, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PP);
  set_led(false);

  gpio_configure_pin(BTN, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PUPD);
  gpio_write_pin(BTN, true); // ODR=1 -> pull-up
}

static bool is_led_on = false;
static uint32_t last_change = 0;

void exti1_handler(void) {
  // Clear pending flag
  EXTI->PR = EXTI_PR_PR1;

  if (systick_get_ms() - last_change < 20) return;
  last_change = systick_get_ms();

  // Geniune press, not a bounce if BTN is still LOW
  if (!gpio_read_pin(BTN)) {
    is_led_on = !is_led_on;
    set_led(is_led_on);
  }
}
