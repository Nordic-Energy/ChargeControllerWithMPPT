######################################
# Target
######################################
TARGET = mppt

#######################################
# Type build
######################################
DEBUG = 1
OPTIMIZE = -Og

#######################################
# Path
######################################
BUILD_DIR = build
LD_DIR = system/ldscript/

#################################
# GNU ARM Embedded Toolchain
#################################
PREFIX = arm-none-eabi-

CC  = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS  = $(PREFIX)gcc -x assembler-with-cpp
CP  = $(PREFIX)objcopy
SZ  = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

######################################
# Source files
######################################
C_SOURCES =  \
library/cmsis/src/system_stm32f3xx.c

CXX_SOURCES = \
system/startup/startupF334.cpp \
periphery/src/Adc.cpp \
periphery/src/Clock.cpp \
periphery/src/Hrpwm.cpp \
periphery/src/Led.cpp \
application/src/main.cpp \
application/src/Application.cpp \
application/src/Feedback.cpp \
application/src/Battery.cpp \
application/src/BuckConverter.cpp

#######################################
# Macros for GCC
#######################################
C_DEFS =  \
-DSTM32F334x8

C_INCLUDES =  \
system/startup/ \
library/cmsis/inc \
application/inc \
periphery/inc \
library/cmsis \
library/dsp
 
#######################################
# Flags
#######################################
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

ASFLAGS = $(MCU) $(OPTIMIZE) -Wall -fdata-sections -ffunction-sections
CFLAGS = -c $(MCU) $(DEFS) $(OPTIMIZE) $(addprefix -I,$(C_INCLUDES)) -std=c11 -Wall -fdata-sections -ffunction-sections
CXXFLAGS = -c $(MCU) $(DEFS) $(OPTIMIZE) $(addprefix -I,$(C_INCLUDES)) -std=c++17 -Wall -fdata-sections -ffunction-sections

LDSCRIPT = $(LD_DIR)stm32f334c8t6.ld
LIBS = -lc -lm -lnosys  
LDFLAGS = $(MCU) -specs=nosys.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
LDFLAGS += -mcpu=cortex-m4 -mthumb

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
CXXFLAGS += -g -gdwarf-2
endif

#################################
# Object List
#################################
OBJECTS += $(addsuffix .o,$(addprefix $(BUILD_DIR)/$(TARGET),$(basename $(C_SOURCES))))
OBJECTS += $(addsuffix .o,$(addprefix $(BUILD_DIR)/$(TARGET),$(basename $(CXX_SOURCES))))

#################################
# Target Output Files
#################################
TARGET_ELF = $(BUILD_DIR)/$(TARGET).elf
TARGET_HEX = $(BUILD_DIR)/$(TARGET).hex
TARGET_BIN = $(BUILD_DIR)/$(TARGET).bin

#################################
# Build
#################################
$(BUILD_DIR)/$(TARGET)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo $<
	@$(CXX) -c -o $@ $(CXXFLAGS) $<

$(BUILD_DIR)/$(TARGET)%.o: %.c
	@mkdir -p $(dir $@)
	@echo $<
	@$(CC) -c -o $@ $(CFLAGS) $<

$(TARGET_ELF): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	$(SZ) $(TARGET_ELF)

$(TARGET_HEX): $(TARGET_ELF)
	$(HEX) $< $@

$(TARGET_BIN): $(TARGET_ELF)
	$(BIN) $< $@

#################################
# Recipes
#################################
.PHONY: all clean

all: $(TARGET_ELF) $(TARGET_HEX) $(TARGET_BIN)

clean:
	-rm -fR $(BUILD_DIR)