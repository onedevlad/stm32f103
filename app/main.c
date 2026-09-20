#include <stdint.h>

#include "init/rcc.h"
#include "init/gpio.h"
#include "init/systick.h"
#include "init/tim.h"

int main(void) {
  rcc_setup_72mhz();
  systick_setup();
  gpio_enable_mco();
  gpio_setup_led();
  gpio_setup_pwm();

  const uint32_t pwm_period = 1000; // duty steps: 0..1000 (~100%)
  tim2_pwm_setup(72, pwm_period); // 72MHz / 72 / 1000 = 1kHz PWM

  int32_t duty = 0;
  int32_t duty_step = 15;

  while(1) {
    duty += duty_step;
    if (duty <= 0 || (uint32_t) duty >= pwm_period) duty_step = -duty_step;
    tim2_pwm_set_duty(duty);
    sleep(20);
  }

  return 0;
}
