#include "lib/tim.h"
#include "lib/rcc.h"

void tim2_pwm_setup(uint32_t psc, uint32_t arr) {
  rcc_apb1_enable(RCC_APB1ENR_TIM2EN); // TIM2 is on APB1

  TIM2->PSC = psc - 1;
  TIM2->ARR = arr - 1;

  // PWM mode 1: output high while CNT < CCR1, low otherwise
  MODIFY_REG(TIM2->CCMR1, TIM_CCMR1_OC1M, TIM_CCMR1_OC1M_PWM1);
  TIM2->CCMR1 |= TIM_CCMR1_OC1PE;

  TIM2->CCER |= TIM_CCER_CC1E;
  TIM2->CR1  |= TIM_CR1_ARPE;

  TIM2->EGR |= TIM_EGR_UG; // Latch PSC/ARR into their shadow registers now
  TIM2->CR1 |= TIM_CR1_CEN;
}

void tim2_pwm_set_duty(uint32_t compare) {
  TIM2->CCR1 = compare;
}
