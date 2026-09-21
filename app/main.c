#include <stdint.h>

#include "init/rcc.h"
#include "init/gpio.h"
#include "init/systick.h"
#include "init/tim.h"

#define PWM_PERIOD (1000)
static int32_t duty = 0;
static int32_t duty_step = 15;
static int32_t last_breath_ms = 0;

static void breathe_led(void) {
  if (systick_get_ms() - last_breath_ms < 20) return;
  last_breath_ms = systick_get_ms();

  duty += duty_step;
  if (duty <= 0 || (uint32_t) duty >= PWM_PERIOD) duty_step = -duty_step;
  tim2_pwm_set_duty(duty);
}

static bool was_pressed = false;
static bool is_led_on = false;
static uint32_t last_change = 0;
static void poll_btn(void) {
  const bool is_btn_pressed = gpio_is_btn_pressed();
  if (
    is_btn_pressed == was_pressed ||
    systick_get_ms() - last_change < 20
  ) return;

  last_change = systick_get_ms();
  was_pressed = is_btn_pressed;

  if (is_btn_pressed) {
    is_led_on = !is_led_on;
    gpio_set_led_state(is_led_on);
  }
}

int main(void) {
  rcc_setup_72mhz();
  systick_setup();
  gpio_enable_mco();
  gpio_setup_led();
  gpio_set_led_state(false);

  gpio_setup_btn();
  gpio_setup_pwm();
  tim2_pwm_setup(72, PWM_PERIOD); // 72MHz / 72 / 1000 = 1kHz PWM


  while(1) {
    breathe_led();
    poll_btn();
  }

  return 0;
}
