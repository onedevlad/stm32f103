#include <stdbool.h>
#include <stdint.h>
#include "lib/gpio.h"
#include "lib/systick.h"
#include "led/toggle.h"

#define LED_PORT GPIOC
#define LED_PIN 13

#define BTN_PORT GPIOA
#define BTN_PIN 1

static void set_led(bool on) {
  gpio_write_pin(LED_PORT, LED_PIN, !on);
}

void setup_led_toggle(void) {
  gpio_configure_pin(LED_PORT, LED_PIN, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PP);
  set_led(false);

  gpio_configure_pin(BTN_PORT, BTN_PIN, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PUPD);
  gpio_write_pin(BTN_PORT, BTN_PIN, true); // ODR=1 -> pull-up
}

static bool was_pressed = false;
static bool is_led_on = false;
static uint32_t last_change = 0;

void run_led_toggle(void) {
  const bool is_pressed = !gpio_read_pin(BTN_PORT, BTN_PIN);

  if (
    is_pressed == was_pressed ||
    systick_get_ms() - last_change < 20
  ) return;

  last_change = systick_get_ms();
  was_pressed = is_pressed;

  if (is_pressed) {
    is_led_on = !is_led_on;
    set_led(is_led_on);
  }
}
