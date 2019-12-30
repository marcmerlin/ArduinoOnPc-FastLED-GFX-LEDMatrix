CUSTOM_LIBS := libraries

ARDUINO_LIBS += SPI
ARDUINO_LIBS += FastLED
ARDUINO_LIBS += Framebuffer_GFX
ARDUINO_LIBS += Adafruit_GFX
ARDUINO_LIBS += LEDMatrix

BUILD_ROOT := build
include ../../makeNativeArduino.mk
