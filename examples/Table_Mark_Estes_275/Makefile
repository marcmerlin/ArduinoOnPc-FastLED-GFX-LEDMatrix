CUSTOM_LIBS := libraries

# Use SDL instead of X11. It is faster but requires SDL.
LINUX_RENDERER_SDL = yes
# SDL is even too fast compared to regular neopixels, so we introduce
# a configurable delay here
LINUX_RENDERER_SDL_MAIN_DELAY = 10

ARDUINO_LIBS += SPI
ARDUINO_LIBS += FastLED
ARDUINO_LIBS += Framebuffer_GFX
# LINUX_RENDERER_SDL uses FastLED_NeoMatrix and FastLED
ARDUINO_LIBS += FastLED_NeoMatrix
# Comment this out unless you are building for X11 rendering
ARDUINO_LIBS += FastLED_TFTWrapper_GFX
# Comment this out unless you are building for RGBPanels on rPi
ARDUINO_LIBS += FastLED_RPIRGBPanel_GFX
ARDUINO_LIBS += Adafruit_GFX
ARDUINO_LIBS += LEDMatrix
ARDUINO_LIBS += LEDSprites
ARDUINO_LIBS += LEDText

BUILD_ROOT := build
include ../../makeNativeArduino.mk
