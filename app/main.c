#include <stdint.h>

#include "init/rcc.h"
#include "init/gpio.h"
#include "init/systick.h"
#include "init/tim.h"

static void sleep(uint32_t millis) {
  const uint32_t start = systick_get_ms();
  while (systick_get_ms() - start < millis);
}

int main(void) {
  rcc_setup_72mhz();
  systick_setup();
  gpio_enable_mco();
  gpio_setup_led();
  gpio_setup_pwm();

  const uint32_t pwm_period = 999; // duty steps: 0..999 (~100%)
  tim2_pwm_setup(71, pwm_period); // 72MHz / (71 + 1) / (999 + 1) = 1kHz PWM

  int32_t duty = 0;
  int32_t duty_step = 15;

  while(1) {
    gpio_set_led_state(0);
    sleep(100);

    gpio_set_led_state(1);
    sleep(100);

    duty += duty_step;
    if (duty <= 0 || (uint32_t) duty >= pwm_period) duty_step = -duty_step;
    tim2_pwm_set_duty(duty);
  }

  return 0;
}
