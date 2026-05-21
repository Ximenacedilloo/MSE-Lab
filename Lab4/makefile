include sources.mk

BUILD_DIR = build
LINKER_DIR = linker

EXEC = $(BUILD_DIR)/app.elf

LINKER_FILE = $(LINKER_DIR)/STM32f4.ld
CPU = cortex-m4
ARCH = armv7e-m
SPECS = nosys.specs
FPU = fpv4-sp-d16

ARCHFLAGS = 		\
-mcpu=$(CPU) 		\
-mthumb 			\
-march=$(ARCH) 		\
-mfloat-abi=hard 	\
-mfpu=$(FPU) 		\
--specs=$(SPECS)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

CC = arm-none-eabi-gcc

CFLAGS = 			\
-g 					\
-O0 				\
-std=c99 			\
-Werror 			\
-Wall 				\
-DSTM32F411xE		\
$(ARCHFLAGS)

LDFLAGS = 		\
-nostdlib 		\
-T 				\
$(LINKER_FILE)	\
-lgcc

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< $(CFLAGS) $(INCLUDES) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY : build

build : $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $@

.PHONY : flash

flash : $(EXEC)
	openocd -f board/st_nucleo_f4.cfg -c "program $(EXEC) verify reset" -c shutdown

.PHONY : clean

clean : 
	rm -f $(OBJS) $(EXEC)
	rm -rf $(BUILD_DIR)