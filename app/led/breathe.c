#include <stdint.h>
#include "led/breathe.h"
#include "lib/tim.h"
#include "lib/systick.h"
#include "lib/gpio.h"

static const pin_t PWM = { GPIOA, 0 };
#define PWM_PERIOD 1000

static int32_t duty = 0;
static int32_t duty_step = 15;
static int32_t last_breath_ms = 0;

void setup_led_breath(void) {
  gpio_configure_pin(PWM, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_AF_PP);
  tim2_pwm_setup(72, PWM_PERIOD); // 72MHz / 72 / 1000 = 1kHz PWM
}

void run_led_breath(void) {
  if (systick_get_ms() - last_breath_ms < 20) return;

  last_breath_ms = systick_get_ms();

  duty += duty_step;
  if (duty <= 0 || (uint32_t) duty >= PWM_PERIOD) duty_step = -duty_step;
  tim2_pwm_set_duty(duty);
}
