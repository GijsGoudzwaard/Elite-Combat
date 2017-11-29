BOARD_TAG                        = uno
MCU                              = atmega328p
F_CPU                            = 16000000

AVRDUDE_ARD_BAUDRATE			 = 115200
MONITOR_BAUDRATE				 = 115200
ARDUINO_LIBS         			 = GraphicsLib MI0283QT9 digitalWriteFast SPI Nunchuck Wire SdFat
LOCAL_CPP_SRCS					 = $(wildcard src/main.cpp)
LOCAL_CPP_SRCS					 += $(wildcard src/**/*.cpp)

NO_CORE_MAIN_CPP = true


-include Makefile.variable
include $(ARDMK_DIR)/Arduino.mk