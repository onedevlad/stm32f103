#ifndef INC_SYSTICK_H
#define INC_SYSTICK_H

#include <stddef.h>
#include "lib/memorymap.h"
#include "lib/common.h"

typedef struct {
  volatile uint32_t CTRL;  // 0x00
  volatile uint32_t LOAD;  // 0x04
  volatile uint32_t VAL;   // 0x08
  volatile uint32_t CALIB; // 0x0C
} systick_t;

_Static_assert(offsetof(systick_t, CALIB) == 0x0C, "systick_t layout wrong");

#define SYSTICK ((systick_t *)SYSTICK_BASE)

// CTRL
#define STK_CTRL_ENABLE    BIT(0)        // 1 = counter enabled
#define STK_CTRL_TICKINT   BIT(1)        // 1 = interrupt on reaching 0
#define STK_CTRL_CLKSOURCE GENMASK(2, 2) // Bit 2
#define STK_CTRL_COUNTFLAG BIT(16)       // 1 = counted to 0 since last read

#define STK_CTRL_CLKSOURCE_AHB_DIV8 FIELD_PREP(STK_CTRL_CLKSOURCE, 0)
#define STK_CTRL_CLKSOURCE_AHB      FIELD_PREP(STK_CTRL_CLKSOURCE, 1)

// LOAD/VAL
#define STK_LOAD_RELOAD GENMASK(23, 0)

void sys_tick_handler(void);

void systick_setup(void);
uint32_t systick_get_ms(void);

void sleep(uint32_t millis);

#endif
