BOARD_TAG                        = uno
MCU                              = atmega328p
F_CPU                            = 16000000
<<<<<<< HEAD
AVRDUDE_ARD_BAUDRATE						 = 115200
MONITOR_BAUDRATE						 = 115200

ARDUINO_LIBS        					   = GraphicsLib MI0283QT9 SD digitalWriteFast SPI
=======
AVRDUDE_ARD_BAUDRATE			 			 = 115200
ARDUINO_LIBS        			 			 = GraphicsLib MI0283QT9 SD digitalWriteFast SPI
>>>>>>> c562fbec1181e3710c51c38569c6e72763da5304
LOCAL_CPP_SRCS 									 = $(wildcard src/**/*.cpp)

MONITOR_PORT = 4
include $(ARDMK_DIR)/Arduino.mk
