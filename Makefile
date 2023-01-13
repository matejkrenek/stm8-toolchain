DEVICE = STM8S103
DEVICE_FLASH = STM8S103F3
STLINK = ST-LINK
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

LIB_SOURCES = stm8s_gpio.c stm8s_clk.c stm8s_tim4.c stm8s_itc.c 
LIB_OBJECTS := $(addprefix $(OUTPUT_DIR)/, $(LIB_SOURCES:.c=.rel))
LIB_INCLUDES  = $(wildcard $(LIB_DIR)/**/inc/*.h)
LIB_ASMS := $(addprefix $(OUTPUT_DIR)/, $(LIB_SOURCES:.c=.asm))

VPATH = $(APP_DIR)/src $(wildcard $(LIB_DIR)/**/src)

compile: $(TARGET).ihx

$(TARGET).ihx: $(APP_ASMS) $(LIB_ASMS)
	.make/asm2obj $^	
	$(CC) $(C_FLAGS) $(C_DEFS) -o $(TARGET).ihx $(APP_OBJECTS) $(LIB_OBJECTS)
	cp $@ ./out.ihx

$(OUTPUT_DIR)/%.asm: %.c Makefile $(APP_INCLUDES) | $(OUTPUT_DIR)
	$(CC) $(C_FLAGS) -I app/inc $(C_DEFS) -D$(DEVICE) $(C_INCLUDES) -DSKIP_TRAPS=$(SKIP_TRAPS) -c $< -o $@

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

update:
	@node .make/update --library=$(LIB) --device=$(DEVICE)

clean:
	@rm -Rf $(OUTPUT_DIR)

flash:
	@echo -e "Flashed!!!"

run:
	make update
	make clean
	make compile
	make flash

.PHONY: clean