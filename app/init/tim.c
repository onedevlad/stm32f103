#include "tim.h"

void tim2_pwm_setup(uint32_t psc, uint32_t arr) {
  TIM2_PSC = psc;
  TIM2_ARR = arr;

  // PWM mode 1: output high while CNT < CCR1, low otherwise
  TIM2_CCMR1 =
    (TIM2_CCMR1 & ~TIM_CCMR1_OC1M) |
    (TIM_CCMR1_OC1M_PWM_MODE_1 << TIM_CCMR1_OC1M_SHIFT);
  TIM2_CCMR1 |= TIM_CCMR1_OC1PE;

  TIM2_CCER |= TIM_CCER_CC1E;
  TIM2_CR1 |= TIM_CR1_ARPE;

  TIM2_EGR |= TIM_EGR_UG; // Latch PSC/ARR into their shadow registers now
  TIM2_CR1 |= TIM_CR1_CEN;
}

void tim2_pwm_set_duty(uint32_t compare) {
  TIM2_CCR1 = compare;
}
