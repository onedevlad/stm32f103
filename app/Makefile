PROJECT = app
BUILD_DIR = bin

ARCH_FLAGS = -mcpu=cortex-m3 -mthumb -msoft-float
LDSCRIPT = stm32f103c8t6.ld
SHARED_DIR = ../shared
CFILES = main.c
CFILES += init/rcc.c
CFILES += init/gpio.c
CFILES += init/tim.c
CFILES += init/systick.c
CFILES += init/startup.c
OPT = -Os
TGT_LDFLAGS += -Wl,-Map=$(PROJECT).map

OOCD_INTERFACE = stlink
OOCD_TARGET = stm32f1x

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include ../rules.mk
