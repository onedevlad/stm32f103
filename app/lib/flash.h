#ifndef INC_FLASH_H
#define INC_FLASH_H

#include <stddef.h>
#include <stdint.h>
#include "lib/memorymap.h"
#include "lib/common.h"

typedef struct {
  volatile uint32_t ACR;     // 0x00
  volatile uint32_t KEYR;    // 0x04
  volatile uint32_t OPTKEYR; // 0x08
  volatile uint32_t SR;      // 0x0C
  volatile uint32_t CR;      // 0x10
  volatile uint32_t AR;      // 0x14
  uint32_t _reserved0;       // 0x18
  volatile uint32_t OBR;     // 0x1C
  volatile uint32_t WRPR;    // 0x20
} flash_t;

#define FLASH ((flash_t *)FLASH_BASE)

#define FLASH_ACR_LATENCY GENMASK(2, 0)
#define FLASH_ACR_PRFTBE  BIT(4)

#define FLASH_ACR_LATENCY_0WS 0x00
#define FLASH_ACR_LATENCY_1WS 0x01
#define FLASH_ACR_LATENCY_2WS 0x02

#endif
