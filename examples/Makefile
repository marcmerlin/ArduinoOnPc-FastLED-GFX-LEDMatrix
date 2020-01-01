CUSTOM_LIBS := libraries

ARDUINO_LIBS += SPI
ARDUINO_LIBS += FastLED
ARDUINO_LIBS += Framebuffer_GFX
# Comment this out unless you are building for X11 rendering
ARDUINO_LIBS += FastLED_TFTWrapper_GFX
# Comment this out unless you are building for RGBPanels on rPi
ARDUINO_LIBS += FastLED_RPIRGBPanel_GFX
ARDUINO_LIBS += Adafruit_GFX
ARDUINO_LIBS += LEDMatrix

BUILD_ROOT := build
include ../../makeNativeArduino.mk
