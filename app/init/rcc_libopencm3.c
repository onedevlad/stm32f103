#include <libopencm3/stm32/rcc.h>
#include "rcc_libopencm3.h"

#include <libopencm3/stm32/gpio.h>

void setup_rcc_libopencm3(void) {
  rcc_osc_on(RCC_HSI); // Should already be ON by the time MCU starts up
  rcc_wait_for_osc_ready(RCC_HSI);

  // ~15.62kHz setup (slowest MCU can go)
  rcc_set_sysclk_source(RCC_CFGR_SW_SYSCLKSEL_HSICLK);
  rcc_set_hpre(RCC_CFGR_HPRE_DIV512);

  // Ouput SYSCLK at PA8 (Master Clock Out)
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO8);
  rcc_set_mco(RCC_CFGR_MCO_SYSCLK);

  // 72Mhz setup
  // rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);


  rcc_periph_clock_enable(RCC_GPIOC);
}
