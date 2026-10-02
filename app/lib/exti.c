#include "lib/exti.h"
#include "lib/memorymap.h"
#include "lib/rcc.h"
#include "lib/common.h"

static inline void nvic_enable_irq(uint32_t irqn) {
  MMIO(NVIC_ISER0) = BIT(irqn);
}

void exti_setup(void) {
  rcc_apb2_enable(RCC_APB2ENR_AFIOEN);

  MODIFY_REG(
    AFIO->EXTICR1,
    AFIO_EXTICR1_EXTI1,
    FIELD_PREP(AFIO_EXTICR1_EXTI1, AFIO_EXTICR_PA)
  );

  MODIFY_REG(
    EXTI->FTSR,
    EXTI_FTSR_TR1,
    FIELD_PREP(EXTI_FTSR_TR1, EXTI_FTSR_TREN)
  );

  MODIFY_REG(
    EXTI->IMR,
    EXTI_IMR_MR1,
    FIELD_PREP(EXTI_IMR_MR1, EXTI_IMR_MR1EN)
  );

  nvic_enable_irq(EXTI1_IRQN);
}
