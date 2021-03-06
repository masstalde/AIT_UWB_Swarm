# This file was automagically generated by mbed.org. For more information, 
# see http://mbed.org/handbook/Exporting-to-GCC-ARM-Embedded

GCC_BIN = 

DEBUG := 1
BUILD_SLAVE := 

PROJECT = AIT_UWB_Tracker
TARGET := TARGET_NUCLEO_F411RE
TARGET_BOARD := NUCLEO_F411RE
TOOLCHAIN := TOOLCHAIN_GCC_ARM

OBJDIR := ./obj

BASE := ../..
SRCDIR := $(BASE)/src
LIBDIR := $(BASE)/lib

SYS_PATH := $(SRCDIR)/mbed/$(TARGET)/$(TOOLCHAIN)
SYS_OBJECTS := $(wildcard $(addsuffix /*.o, $(SYS_PATH)))
 

INCLUDE_PATHS := $(SRCDIR)
INCLUDE_PATHS += $(SRCDIR)/DW1000
INCLUDE_PATHS += $(SRCDIR)/PC
INCLUDE_PATHS += $(SRCDIR)/BufferedSerial
INCLUDE_PATHS += $(SRCDIR)/BufferedSerial/Buffer
INCLUDE_PATHS += $(SRCDIR)/mavlink_bridge
INCLUDE_PATHS += $(SRCDIR)/UWB2WayMultiRange
INCLUDE_PATHS += $(SRCDIR)/UWBProtocol
INCLUDE_PATHS += $(SRCDIR)/UWBSlave

INCLUDE_PATHS += $(SRCDIR)/mbed
INCLUDE_PATHS += $(SRCDIR)/mbed/$(TARGET) 
INCLUDE_PATHS += $(SRCDIR)/mbed/$(TARGET)/$(TOOLCHAIN) 
INCLUDE_PATHS += $(SRCDIR)/mbed/$(TARGET)/TARGET_STM
INCLUDE_PATHS += $(SRCDIR)/mbed/$(TARGET)/TARGET_STM/$(TARGET) 

 
INCS :=  $(patsubst %, -I%, $(INCLUDE_PATHS))

OBJS := $(wildcard $(addsuffix /*.c, $(INCLUDE_PATHS)))
OBJS += $(wildcard $(addsuffix /*.cpp, $(INCLUDE_PATHS)))
OBJS := $(notdir $(OBJS))
OBJS := $(OBJS:.cpp=.o)
OBJS := $(OBJS:.c=.o)
OBJS := $(patsubst %, $(OBJDIR)/%, $(OBJS))
OBJECTS = $(OBJS) 
 
LIBRARY_PATHS = -L../../src/mbed/$(TARGET)/$(TOOLCHAIN)
LIBRARIES = -lmbed
 
LINKER_SCRIPTS := ../../src/mbed/$(TARGET)/$(TOOLCHAIN)/STM32F411XE.ld


LS := $(patsubst %, -T%, $(LINKER_SCRIPTS))

VPATH := $(INCLUDE_PATHS)
#VPATH +=  ../../src/libs/
#VPATH +=  ../../src/drivers/

############################################################################### 
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE 	= $(GCC_BIN)arm-none-eabi-size

CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=$(FLOAT_ABI) 
CC_FLAGS = $(CPU) -c -g -fno-common -fmessage-length=0 -Wall -Wextra -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -MMD -MP
CC_SYMBOLS = -DTARGET_RTOS_M4_M7 -DTARGET_FF_ARDUINO -DTOOLCHAIN_GCC_ARM -DNUCLEO_F411RE -D__CORTEX_M4 -DTARGET_LIKE_MBED -DTARGET_CORTEX_M -D__FPU_PRESENT=1 -DTARGET_LIKE_CORTEX_M4 -DTARGET_M4 -D__MBED__=1 -DTARGET_STM -DTARGET_STM32F4 -DTARGET_FF_MORPHO -DTOOLCHAIN_GCC -DTARGET_STM32F411RE -DMBED_BUILD_TIMESTAMP=1458564878.84 -DARM_MATH_CM4 

LD_FLAGS = $(CPU) -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float -Wl,--wrap,main -Wl,-Map=$(PROJECT).map,--cref
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys
LD_FLAGS += -Wl,-Map=$(PROJECT).map,--cref
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys

ifeq ($(HARDFP),1)
	FLOAT_ABI = hard
else
	FLOAT_ABI = softfp
endif


  CC_FLAGS += -D_DEBUG
  CC_FLAGS += -O0
  CC_FLAGS += -DDEBUG


ifdef $(BUILD_SLAVE)
  CC_FLAGS += -DBUILD_SLAVE
endif
	
upload: all
	cp $(PROJECT).bin /cygdrive/n/	
		
all: $(PROJECT).bin $(PROJECT).hex 

clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(PROJECT).hex $(PROJECT).map $(PROJECT).lst $(OBJECTS) $(DEPS)

$(OBJDIR)/%.o: %.s Makefile
	@echo --- assembling $<...
	$(AS) $(CPU) -o $@ $<
	@sed -e "s/\\\[ ]*\\\/\\\/g" \
		-e "s/C:\\\/\/cygdrive\/c\//g" \
	    -e "s/c:\\\/\/cygdrive\/c\//g" < $(OBJDIR)/$*.d >  $(OBJDIR)/$*.p;
	    
	$(RM) $(OBJDIR)/$*.d

$(OBJDIR)/%.o: %.c Makefile
	@echo --- compiling $<...
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99  $(INCS) -o $@ $<
	@sed -e "s/\\\[ ]*\\\/\\\/g" \
		-e "s/C:\\\/\/cygdrive\/c\//g" \
	    -e "s/c:\\\/\/cygdrive\/c\//g" < $(OBJDIR)/$*.d >  $(OBJDIR)/$*.p;
	
	$(RM) $(OBJDIR)/$*.d

$(OBJDIR)/%.o: %.cpp Makefile
	@echo --- compiling $<...
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 -fno-rtti $(INCS) -o $@ $<
	@sed -e "s/\\\[ ]*\\\/\\\/g" \
		-e "s/C:\\\/\/cygdrive\/c\//g" \
	    -e "s/c:\\\/\/cygdrive\/c\//g" < $(OBJDIR)/$*.d >  $(OBJDIR)/$*.p;
	
	$(RM) $(OBJDIR)/$*.d


$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS) 
	@echo --- linking...
	$(LD) $(LD_FLAGS) $(LS) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)
	$(SIZE) $@

$(PROJECT).bin: $(PROJECT).elf
	@$(OBJCOPY) -O binary $< $@

$(PROJECT).hex: $(PROJECT).elf
	@$(OBJCOPY) -O ihex $< $@

$(PROJECT).lst: $(PROJECT).elf
	@$(OBJDUMP) -Sdh $< > $@

lst: $(PROJECT).lst

size:
	$(SIZE) $(PROJECT).elf

DEPS = $(OBJECTS:.o=.p) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)
