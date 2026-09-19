#ifndef INC_TIM_H
#define INC_TIM_H

#include "memorymap.h"
#include "common.h"

#define TIM2_CR1   MMIO(TIM2_BASE + 0x00)
#define TIM2_EGR   MMIO(TIM2_BASE + 0x14)
#define TIM2_CCMR1 MMIO(TIM2_BASE + 0x18)
#define TIM2_CCER  MMIO(TIM2_BASE + 0x20)
#define TIM2_PSC   MMIO(TIM2_BASE + 0x28)
#define TIM2_ARR   MMIO(TIM2_BASE + 0x2C)
#define TIM2_CCR1  MMIO(TIM2_BASE + 0x34)

// TIM2_CR1 bits
#define TIM_CR1_ARPE BIT7 // Auto-reload preload enable
#define TIM_CR1_CEN  BIT0 // Counter enable

// TIM2_EGR bits
#define TIM_EGR_UG BIT0 // Update generation (reloads PSC/ARR shadow regs)

// TIM2_CCMR1 bits (channel 1, output compare mode)
#define TIM_CCMR1_OC1PE_SHIFT 3
#define TIM_CCMR1_OC1PE (0x1 << TIM_CCMR1_OC1PE_SHIFT)
#define TIM_CCMR1_OC1M_SHIFT 4
#define TIM_CCMR1_OC1M (0x7 << TIM_CCMR1_OC1M_SHIFT)
#define TIM_CCMR1_OC1M_PWM_MODE_1 0x6

// TIM2_CCER bits
#define TIM_CCER_CC1E BIT0 // Capture/compare 1 output enable

void tim2_pwm_setup(uint32_t psc, uint32_t arr);
void tim2_pwm_set_duty(uint32_t compare);

#endif
