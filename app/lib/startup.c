#include <stdint.h>

extern uint32_t _stack, _data, _edata, _data_loadaddr, _bss, _ebss;

void reset_handler(void);
void sys_tick_handler(void);

static void default_handler(void);

__attribute__((section(".vectors"), used))
void (* const vector_table[])(void) = {
  (void (*)(void))&_stack, // 0: Initial SP
  reset_handler,           // 1
  default_handler,         // 2: NMI
  default_handler,         // 3: HardFault
  default_handler,         // 4: MemManage
  default_handler,         // 5: BusFault
  default_handler,         // 6: UsageFault
  0, 0, 0, 0,              // 7-10: Reserved
  default_handler,         // 11: SVCall
  0,                       // 12: DebugMon (reserved?)
  0,                       // 13: Reserved
  default_handler,         // 14: PendSV
  sys_tick_handler,        // 15: SysTick
};

static void default_handler(void) { while(1); }
void reset_handler(void) {
  uint32_t *src = &_data_loadaddr;
  uint32_t *dst = &_data;
  while (dst < &_edata) *dst++ = *src++;

  dst = &_bss;
  while (dst < &_ebss) *dst++ = 0;

  extern int main(void);
  main();

  while(1);
}
