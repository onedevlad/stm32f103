#include <stdint.h>

/* #include "init/init_rcc_libopencm3.h" */
#include "init/init_rcc.h"
#include "init/gpio.h"

static void sleep(uint32_t millis) {
  volatile uint32_t i = 72e3 / 12 * millis;
  while (i--) __asm__("nop");
}

int main(void) {
  /* setup_rcc_libopencm3(); */
  setup_rcc_72mhz();
  gpio_setup();

  while(1) {
    set_led_state(0);
    sleep(1000);
    set_led_state(1);
    sleep(1000);
  }

  return 0;
}
