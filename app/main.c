#include <stdint.h>

#include "init/rcc.h"
#include "init/gpio.h"

static void sleep(uint32_t millis) {
  volatile uint32_t i = 72e3 / 12 * millis;
  while (i--) __asm__("nop");
}

int main(void) {
  rcc_setup_8mhz();
  enable_mco();
  setup_led();

  while(1) {
    set_led_state(0);
    sleep(1000);
    set_led_state(1);
    sleep(1000);
  }

  return 0;
}
