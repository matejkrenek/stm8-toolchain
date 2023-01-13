DEVICE=STM8S103
DEVICE_FLASH=STM8S103F3
STLINK=ST-LINK
F_CPU=16000000

ifeq ($(OS),Windows_NT)
    CC_ROOT = "/c/Program Files/SDCC"
else
    CC_ROOT = /opt/sdcc
endif

CC = $(SDCC_PATH)/bin/sdcc

C_DEFS =					\
-DF_CPU=$(F_CPU) 			\
-D$(DEVICE) 				\

C_INCLUDES =				\


C_FLAGS =					\


clean::
	@echo -e "Cleaned!!!"
	
compile:
	@echo -e "Compiled!!!"

flash::
	@echo -e "Flashed!!!"

run::
	make clean
	make compile
	make flash