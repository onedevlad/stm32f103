#ifndef INC_TIM_H
#define INC_TIM_H

#include <stddef.h>
#include "memorymap.h"
#include "common.h"

typedef struct {
  volatile uint32_t CR1;   // 0x00
  volatile uint32_t CR2;   // 0x04
  volatile uint32_t SMCR;  // 0x08
  volatile uint32_t DIER;  // 0x0C
  volatile uint32_t SR;    // 0x10
  volatile uint32_t EGR;   // 0x14
  volatile uint32_t CCMR1; // 0x18
  volatile uint32_t CCMR2; // 0x1C
  volatile uint32_t CCER;  // 0x20
  volatile uint32_t CNT;   // 0x24
  volatile uint32_t PSC;   // 0x28
  volatile uint32_t ARR;   // 0x2C
  uint32_t _reserved0;     // 0x30
  volatile uint32_t CCR1;  // 0x34
  volatile uint32_t CCR2;  // 0x38
  volatile uint32_t CCR3;  // 0x3C
  volatile uint32_t CCR4;  // 0x40
} tim_t;

_Static_assert(offsetof(tim_t, CCR1) == 0x34, "tim_t layout wrong");
_Static_assert(offsetof(tim_t, PSC) == 0x28, "tim_t layout wrong");

#define TIM2 ((tim_t *) TIM2_BASE)

// CR1
#define TIM_CR1_CEN  BIT(0)
#define TIM_CR1_ARPE BIT(7)

// EGR
#define TIM_EGR_UG BIT(0)

// CCMR1, output compare mode
#define TIM_CCMR1_OC1PE     BIT(3)
#define TIM_CCMR1_OC1M      GENMASK(6, 4)
#define TIM_CCMR1_OC1M_PWM1 FIELD_PREP(TIM_CCMR1_OC1M, 6)
#define TIM_CCMR1_OC1M_PWM2 FIELD_PREP(TIM_CCMR1_OC1M, 7)

// CCER
#define TIM_CCER_CC1E BIT(0)

void tim2_pwm_setup(uint32_t psc, uint32_t arr);
void tim2_pwm_set_duty(uint32_t compare);

#endif
