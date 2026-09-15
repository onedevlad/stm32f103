#include "systick.h"

static volatile uint32_t ms_counter;

void systick_setup(void) {
  STK_LOAD = 72000 - 1;
  STK_VAL = 0;
  STK_CTRL |= (STK_CTRL_ENABLE | STK_CTRL_TICKINT | STK_CTRL_CLKSOURCE);
}

void sys_tick_handler(void) {
  ms_counter++;
}

uint32_t systick_get_ms(void) {
  return ms_counter;
}
