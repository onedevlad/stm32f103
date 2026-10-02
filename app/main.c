#include <stdint.h>

#include "lib/rcc.h"
#include "lib/systick.h"
#include "lib/exti.h"

#include "led/breathe.h"
#include "led/toggle.h"
#include "misc/mco.h"

int main(void) {
  rcc_setup_72mhz();
  systick_setup();
  setup_mco();

  setup_led_breath();
  setup_led_toggle();

  exti_setup();

  while(1) {
    run_led_breath();
  }

  return 0;
}
