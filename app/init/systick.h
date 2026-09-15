#ifndef INC_SYSTICK_H
#define INC_SYSTICK_H

#include "memorymap.h"
#include "common.h"

// Systick registers
#define STK_CTRL  MMIO(SYSTICK_BASE + 0x00)
#define STK_LOAD  MMIO(SYSTICK_BASE + 0x04)
#define STK_VAL   MMIO(SYSTICK_BASE + 0x08)
#define STK_CALIB MMIO(SYSTICK_BASE + 0x0C)

// Systick CTRL bits
#define STK_CTRL_COUNTFLAG BIT16
#define STK_CTRL_CLKSOURCE BIT2 // 0 = AHB/8, 1 = AHB
#define STK_CTRL_TICKINT   BIT1 // 1 = Generate an interrupt on reaching 0
#define STK_CTRL_ENABLE    BIT0 // 1 = Counter enabled

#define STK_CTRL_CLKSOURCE_AHB      STK_CTRL_CLKSOURCE
#define STK_CTRL_CLKSOURCE_AHB_DIV8 0x0

#define STK_RELOAD_MASK 0x00FFFFFF // Systick is only 24bit wide

void sys_tick_handler(void);

void systick_setup(void);
uint32_t systick_get_ms(void);

#endif
