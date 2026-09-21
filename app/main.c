#include <stdint.h>

#include "lib/rcc.h"
#include "lib/systick.h"

#include "led/breathe.h"
#include "led/toggle.h"
#include "misc/mco.h"

int main(void) {
  rcc_setup_72mhz();
  systick_setup();
  setup_mco();

  setup_led_breath();
  setup_led_toggle();

  while(1) {
    run_led_breath();
    run_led_toggle();
  }

  return 0;
}
