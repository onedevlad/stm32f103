#include "systick.h"

#define SYSTICK_RELOAD (72000U - 1) // 72MHz / 72000 = 1kHz
_Static_assert(SYSTICK_RELOAD <= STK_LOAD_RELOAD, "reload doesn't fit in 24 bits");

static volatile uint32_t ms_counter;

void systick_setup(void) {
  SYSTICK->LOAD = SYSTICK_RELOAD;
  SYSTICK->VAL = 0;
  MODIFY_REG(
    SYSTICK->CTRL,
    STK_CTRL_ENABLE | STK_CTRL_TICKINT | STK_CTRL_CLKSOURCE,
    STK_CTRL_ENABLE | STK_CTRL_TICKINT | STK_CTRL_CLKSOURCE_AHB
  );
}

void sys_tick_handler(void) {
  ms_counter++;
}

uint32_t systick_get_ms(void) {
  return ms_counter;
}

void sleep(uint32_t millis) {
  const uint32_t start = systick_get_ms();
  while (systick_get_ms() - start < millis);
}
