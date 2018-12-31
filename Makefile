# Project name
TARGET = main

# Used SPL drivers
#-------------------------------------------------------------------------------
# PERIPHDRIVERS += stm32f10x_adc
# PERIPHDRIVERS += stm32f10x_bkp
# PERIPHDRIVERS += stm32f10x_can
# PERIPHDRIVERS += stm32f10x_cec
# PERIPHDRIVERS += stm32f10x_crc
# PERIPHDRIVERS += stm32f10x_dbgmcu
# PERIPHDRIVERS += stm32f10x_exti
# PERIPHDRIVERS += stm32f10x_flash
# PERIPHDRIVERS += stm32f10x_fsmc
PERIPHDRIVERS += stm32f10x_gpio
# PERIPHDRIVERS += stm32f10x_i2c
# PERIPHDRIVERS += stm32f10x_iwdg
# PERIPHDRIVERS += stm32f10x_pwr
PERIPHDRIVERS += stm32f10x_rcc
# PERIPHDRIVERS += stm32f10x_rtc
# PERIPHDRIVERS += stm32f10x_sdio
# PERIPHDRIVERS += stm32f10x_spi
# PERIPHDRIVERS += stm32f10x_tim
# PERIPHDRIVERS += stm32f10x_usart
# PERIPHDRIVERS += stm32f10x_wwdg
# PERIPHDRIVERS += misc

# Defines
#-------------------------------------------------------------------------------
DEFINES += USE_STDPERIPH_DRIVER
DEFINES += STM32F10X_MD_VL

DEFINES += GCC_ARMCM3
DEFINES += VECT_TAB_FLASH

# Tools
#-------------------------------------------------------------------------------
AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
CP = arm-none-eabi-objcopy
SZ = arm-none-eabi-size
RM = rm

# CMSIS, SPL paths
#-------------------------------------------------------------------------------
CMSIS_PATH         = cmsis
STDPERIPH_INC_PATH = stdperiph/inc
STDPERIPH_SRC_PATH = stdperiph/src

# ASM startup file path
#-------------------------------------------------------------------------------
STARTUP = startup/startup_stm32f10x_md_vl.s

# SRC paths
#-------------------------------------------------------------------------------
SOURCEDIRS := src
SOURCEDIRS += $(CMSIS_PATH)

# Headers paths
#-------------------------------------------------------------------------------
INCLUDES += .
INCLUDES += $(SOURCEDIRS)
INCLUDES += $(CMSIS_PATH)
INCLUDES += $(STDPERIPH_INC_PATH)

# Other libs
#-------------------------------------------------------------------------------
LIBPATH +=
LIBS    +=

# Compiler flags
#-------------------------------------------------------------------------------
CFLAGS += -mthumb -mcpu=cortex-m3 # Arch, CS
CFLAGS += -std=gnu99              # Using C99
CFLAGS += -Wall -pedantic         # Show all warnings
CFLAGS += -Os                     # Optimizing
CFLAGS += -ggdb                   # Generate dbg info for gdb
CFLAGS += -fno-builtin

CFLAGS += $(addprefix -I, $(INCLUDES))
CFLAGS += $(addprefix -D, $(DEFINES))

# Flashing utils
#------------------------------------------------------------------------------- 
TTY_PORT = ttyUSB0
FLASH_SCRIPT_PATH = serial/serial_upload

# Linker script
#-------------------------------------------------------------------------------
LDSCR_PATH = ld-scripts
LDSCRIPT   = stm32f100rb.ld

# Linker settings
#-------------------------------------------------------------------------------
LDFLAGS += -nostartfiles
LDFLAGS += -L$(LDSCR_PATH)
LDFLAGS += -T$(LDSCR_PATH)/$(LDSCRIPT)
LDFLAGS += $(addprefix -L, $(LIBPATH))
LDFLAGS += $(LIBS)

# ASM compiler settings
#-------------------------------------------------------------------------------
AFLAGS += -ahls -mapcs-32

# Object file list
#-------------------------------------------------------------------------------
OBJS += $(patsubst %.c, %.o, $(wildcard  $(addsuffix /*.c, $(SOURCEDIRS))))
OBJS += $(addprefix $(STDPERIPH_SRC_PATH)/, $(addsuffix .o, $(PERIPHDRIVERS)))
OBJS += $(patsubst %.s, %.o, $(STARTUP))

# Make filepaths
#-------------------------------------------------------------------------------
VPATH := $(SOURCEDIRS)

# Candidates for cleaning
#-------------------------------------------------------------------------------
TOREMOVE += *.elf *.bin
TOREMOVE += $(addsuffix /*.o, $(SOURCEDIRS))
TOREMOVE += $(addsuffix /*.d, $(SOURCEDIRS))
TOREMOVE += $(STDPERIPH_SRC_PATH)/*.o
TOREMOVE += $(patsubst %.s, %.o, $(STARTUP))
TOREMOVE += $(TARGET)

# Build
#-------------------------------------------------------------------------------
all: $(TARGET).bin size	

# Cleaning
#-------------------------------------------------------------------------------
clean:
	@$(RM) -f $(TOREMOVE)

# Generating *.bin firmware
#-------------------------------------------------------------------------------
$(TARGET).bin: $(TARGET).elf
	@$(CP) -O binary $(TARGET).elf $(TARGET).bin

# Printing build size
#-------------------------------------------------------------------------------
size:
	@echo "---------------------------------------------------"
	@$(SZ) $(TARGET).elf

# Linking
#------------------------------------------------------------------------------- 
$(TARGET).elf: $(OBJS)
	@$(LD) $(LDFLAGS) $^ -o $@

# Compiling
#------------------------------------------------------------------------------- 
%.o: %.c
	@$(CC) $(CFLAGS) -MD -c $< -o $@
	
%.o: %.s
	@$(AS) $(AFLAGS) -c $< -o $@

# Flashing
#------------------------------------------------------------------------------- 
flash: $(TARGET).bin
	@$(FLASH_SCRIPT_PATH) $(TTY_PORT) {upload.altID} {upload.usbID} $(TARGET).bin
# Generated gcc deps
#-------------------------------------------------------------------------------
include $(wildcart *.d)
