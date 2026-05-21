SRC_DIR = sources
INCLUDE_DIR = includes
CMSIS_CORE_DIR = CMSIS/Core/include
CMSIS_STM32_DIR = CMSIS/STM32F4xx/include

SRC = 						\
$(SRC_DIR)/main.c			\
$(SRC_DIR)/GPIO.c			\
$(SRC_DIR)/TIM.c			\
$(SRC_DIR)/Timer.c			\
$(SRC_DIR)/adc_driver.c		\
$(SRC_DIR)/sensor.c			\
$(SRC_DIR)/uart_driver.c	\
$(SRC_DIR)/serial.c			\
$(SRC_DIR)/utils.c			\
$(SRC_DIR)/STM32_startup.c 	\
$(SRC_DIR)/system_stm32f4xx.c

INCLUDES = 				\
-I$(INCLUDE_DIR)		\
-I$(CMSIS_CORE_DIR)		\
-I$(CMSIS_STM32_DIR)