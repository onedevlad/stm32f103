#ifndef INC_COMMON_H
#define INC_COMMON_H

#include <stdint.h>

#define MMIO(addr) (*(volatile uint32_t *)(addr))
#define BIT(n) (1U << (n))

// Mask covering bits h..l inclusive, matching the datasheets "Bits 6:4"
#define GENMASK(h, l) ((~0U << (l)) & (~0U) >> (31 - (h)))

// Shift val into position described by the mask. The shift is
// derived from the mask, and GCC folds it to a constant
#define FIELD_PREP(mask, val) (((val) << __builtin_ctz(mask)) & (mask))

#define FIELD_GET(mask, reg) (((reg) & (mask)) >> __builtin_ctz(mask))

// Read, modify, write loop
#define MODIFY_REG(reg, clear, set) ((reg) = ((reg) & ~(clear)) | (set))

#endif
