BOARD_TAG                        = uno
MCU                              = atmega328p
F_CPU                            = 16000000
AVRDUDE_ARD_BAUDRATE			 			 = 115200
ARDUINO_LIBS        			 			 = GraphicsLib MI0283QT9 SD digitalWriteFast SPI
LOCAL_CPP_SRCS 									 = $(wildcard src/**/*.cpp)

include $(ARDMK_DIR)/Arduino.mk
