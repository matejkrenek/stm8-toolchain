CONFIG_FILE = ./config.json

define GetFromConfig
	$(shell node -p "require('$(CONFIG_FILE)').$(1)")
endef

DEVICE = $(strip $(call GetFromConfig,device))
DEVICE_FLASH = $(strip $(call GetFromConfig,flash.device))
STLINK = $(strip $(call GetFromConfig,flash.stlink))
F_CPU = 16000000
SKIP_TRAPS = 1
OUTPUT_DIR = ./build
LIB_DIR = ./lib
APP_DIR = ./app
TARGET = $(OUTPUT_DIR)/out
LIB ?= SPL

ifeq ($(OS),Windows_NT)
    CC_ROOT = "/c/Program Files/SDCC"
else
    CC_ROOT = /opt/sdcc
endif

CC = $(CC_ROOT)/bin/sdcc

C_DEFS =					\
-D F_CPU=$(F_CPU) 			\

C_INCLUDES =				\
-I app/inc					\
	
C_INCLUDES += $(addprefix -I ,$(wildcard $(LIB_DIR)/**/inc))

C_FLAGS =					\
-mstm8 						\
-lstm8						\
--opt-code-size 			\
--std-sdcc99 				\
--nogcse 					\
--all-callee-saves 			\
--stack-auto 				\
--fverbose-asm 				\
--float-reent 				\
--no-peep					\

APP_SOURCES = $(notdir $(wildcard $(APP_DIR)/src/*.c))
APP_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(APP_SOURCES:.c=.rel))
APP_INCLUDES  = $(wildcard $(APP_DIR)/inc/*.h)
APP_ASMS := $(addprefix $(OUTPUT_DIR)/, $(APP_SOURCES:.c=.asm))

LIB_SOURCES = $(notdir $(wildcard $(LIB_DIR)/**/src/*.c))
LIB_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(LIB_SOURCES:.c=.rel))
LIB_INCLUDES  = $(wildcard $(LIB_DIR)/**/inc/*.h)
LIB_ASMS := $(addprefix $(OUTPUT_DIR)/, $(LIB_SOURCES:.c=.asm))

VPATH = $(APP_DIR)/src $(wildcard $(LIB_DIR)/**/src)

compile: $(TARGET).ihx

$(TARGET).ihx: $(APP_ASMS) $(LIB_ASMS)
	.make/asms_to_objects $^	
	$(CC) $(C_FLAGS) $(C_DEFS) -o $(TARGET).ihx $(APP_OBJECTS) $(LIB_OBJECTS)
	@node .make/size_calculation --files=$(TARGET).ihx

$(OUTPUT_DIR)/%.asm: %.c Makefile $(APP_INCLUDES) | $(OUTPUT_DIR)
	$(CC) $(C_FLAGS) -I app/inc $(C_DEFS) -D$(DEVICE) $(C_INCLUDES) -DSKIP_TRAPS=$(SKIP_TRAPS) -c $< -o $@

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

install:
	bash .make/install
	@node .make/update --library=$(LIB) --device=$(DEVICE)

update:
	bash .make/install
	@node .make/update --library=$(LIB) --device=$(DEVICE)

clean:
	@rm -Rf $(OUTPUT_DIR)

flash:
	@node .make/flash

test:
	@echo -e $(APP_ASMS)

run:
	make clean
	make compile
	make flash

.PHONY: clean