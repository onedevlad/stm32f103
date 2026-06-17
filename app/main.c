#include "init/system.h"
#include "init/init.h"

static void gpio_setup(void) {
  // Clear CNF13[1:0] and MODE13[1:0]
  GPIOC_CRH &= ~(0xF << 20);

  // MODE13 = 10 (output 2 MHz), CNF13 = 00
  GPIOC_CRH |=  (0x2 << 20);
}

static void sleep(uint32_t millis) {
  volatile uint32_t i = 72000 / 12 * millis;
  while (i--) __asm__("nop");
}

int main(void) {
  setup_rcc();
  gpio_setup();

  while(1) {
    GPIOC_ODR &= ~(1 << 13);
    sleep(1000);
    GPIOC_ODR |=  (1 << 13);
    sleep(1000);
  }

  return 0;
}
