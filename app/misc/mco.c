#include "lib/rcc.h"
#include "lib/gpio.h"
#include "misc/mco.h"

#define MCO_PORT GPIOA
#define MCO_PIN 8

void setup_mco(void) {
  rcc_set_mco_source(RCC_CFGR_MCO_SYSCLK);
  gpio_configure_pin(MCO_PORT, MCO_PIN, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_AF_PP);
}
