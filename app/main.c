#include <stdint.h>

#include "init/rcc.h"
#include "init/gpio.h"
#include "init/systick.h"

static void sleep(uint32_t millis) {
  const uint32_t start = systick_get_ms();
  while (systick_get_ms() - start < millis);
}

int main(void) {
  rcc_setup_72mhz();
  systick_setup();
  gpio_enable_mco();
  gpio_setup_led();

  while(1) {
    gpio_set_led_state(0);
    sleep(100);

    gpio_set_led_state(1);
    sleep(100);
  }

  return 0;
}
