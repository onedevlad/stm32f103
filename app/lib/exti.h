#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
  volatile uint32_t IMR;  // 0x00
  volatile uint32_t EMR;   // 0x04
  volatile uint32_t RTSR;  // 0x08
  volatile uint32_t FTSR;  // 0x0C
  volatile uint32_t SWIER; // 0x10
  volatile uint32_t PR;    // 0x14
} exti_t;

typedef struct {
  volatile uint32_t EVCR;    // 0x00
  volatile uint32_t MAPR;    // 0x04
  volatile uint32_t EXTICR1; // 0x08
  volatile uint32_t EXTICR2; // 0x0C
  volatile uint32_t EXTICR3; // 0x10
  volatile uint32_t EXTICR4; // 0x14
  volatile uint32_t MAPR2;   // 0x18
} afio_t;

_Static_assert(offsetof(exti_t, PR) == 0x14, "exti_t layout wrong");

#define EXTI ((exti_t *)EXTI_BASE)
#define AFIO ((afio_t *)AFIO_BASE)

#define EXTI1_IRQN 7

#define AFIO_EXTICR1_EXTI1 GENMASK(7, 4)
#define AFIO_EXTICR_PA     0b0000

#define EXTI_FTSR_TR1  GENMASK(1, 1)
#define EXTI_FTSR_TREN 0b1

#define EXTI_IMR_MR1   GENMASK(1, 1)
#define EXTI_IMR_MR1EN 0b1
#define EXTI_PR_PR1    GENMASK(1, 1)
#define EXTI_PR_DONE   0b1

void exti_setup(void);

void exti1_handler(void);

#endif
