PROJECT = app
BUILD_DIR = bin

# CFILES += api.c
# AFILES += api-asm.S
SHARED_DIR = ../shared
CFILES = main.c
CFILES += init/rcc.c
# CFILES += init/rcc_libopencm3.c
CFILES += init/gpio.c
OPT = -Os
TGT_LDFLAGS += -Wl,-Map=$(PROJECT).map

DEVICE=stm32f103c8t6
OOCD_INTERFACE = stlink
OOCD_TARGET = stm32f1x

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
