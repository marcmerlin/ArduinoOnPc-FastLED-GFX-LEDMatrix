# To get memory debugging:
# unset LD_PRELOAD ; export ASAN=yes; make
# https://github.com/google/sanitizers/wiki/AddressSanitizer
ifneq ($(ASAN),)
CFLAGS += -fsanitize=address
CXXFLAGS += -fsanitize=address
LDFLAGS += -fsanitize=address
endif

penultimateword = $(wordlist $(words $1),$(words $1), x $1)

SKETCH_ROOT := $(shell dirname $(abspath $(call penultimateword, $(MAKEFILE_LIST))))
NATIVE_ROOT := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

#Q ?= @

BUILD_ROOT ?= build
SKETCH ?= $(shell find $(SKETCH_ROOT) -maxdepth 1 -name "*.ino")

TARGET := $(shell basename -s .ino $(SKETCH))

$(shell mkdir -p $(BUILD_ROOT))

CFLAGS += -Wall -Wextra -Wno-unused-parameter -g
CFLAGS += -DARDUINO=101 -DSKETCH_FILE=\"$(SKETCH)\"
CFLAGS += -std=gnu11
CFLAGS += -lm
CFLAGS += -DARDUINOONPC

CXXFLAGS += -Wall -Wextra -Wno-unused-parameter -g
CXXFLAGS += -DARDUINO=101 -DSKETCH_FILE=\"$(SKETCH)\"
#CXXFLAGS += -Wno-class-memaccess # FastLED does some naughty things, not supported by gcc on arm
CXXFLAGS += -std=gnu++11
CXXFLAGS += -DARDUINOONPC

LDFLAGS += -Wl,--gc-sections
LDFLAGS += -L/usr/X11R6/lib -lX11  # include X11 library
LDFLAGS += -pthread                # include linux thread library
# comment this out if you arne't using https://github.com/hzeller/rpi-rgb-led-matrix/

# Copy a string like these in this file: M384BY256 M192BY160 M128BY192
CXXFLAGS += -DGFXDISPLAY_$(shell cat /root/NM/gfxdisplay)
ifneq ($(shell uname -m |grep arm),)
CXXFLAGS += -DRPIRGBPANEL
ifneq ($(shell grep 'Raspberry Pi 4' /proc/device-tree/model),)
CXXFLAGS += -DRPI4
CXXFLAGS += -DRPI
else
ifneq ($(shell grep 'Raspberry Pi 3' /proc/device-tree/model),)
CXXFLAGS += -DRPI3
CXXFLAGS += -DRPI
else
CXXFLAGS += -DRPILT3
CXXFLAGS += -DRPI
endif
endif
#pragma message "ARDUINOONPC building on ARM (guessing rPi), will link against rgbmatrix"
LDFLAGS += -L$(NATIVE_ROOT)/rpi-rgb-led-matrix/lib -lrgbmatrix -lrt
else
ifeq ($(LINUX_RENDERER_SDL),yes)
CXXFLAGS += -DFASTLED_SDL $(shell sdl2-config --cflags) -DLINUX_RENDERER_SDL -DLINUX_RENDERER_SDL_MAIN_DELAY=$(LINUX_RENDERER_SDL_MAIN_DELAY)
LDFLAGS += $(shell sdl2-config --libs)
endif
endif

DEPDIR := $(BUILD_ROOT)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

define add_lib
SRC_C    += $(shell find $1 -name '*.c')
SRC_CXX  += $(shell find $1 -name '*.cpp')
SRC_USER_C = $(shell find $(SKETCH_ROOT) -name "*.c"     | grep -Ev '\.(vscode|git)')
SRC_USER_CXX = $(shell find $(SKETCH_ROOT) -name "*.cpp" | grep -Ev '\.(vscode|git)')

INCLUDES += -I$1
endef

INCLUDES += -I$(SKETCH_ROOT)
INCLUDES += -I$(NATIVE_ROOT)/src/cores/arduino -I$(NATIVE_ROOT)/src/system
# comment this out if you arne't using https://github.com/hzeller/rpi-rgb-led-matrix/
INCLUDES += -I$(NATIVE_ROOT)/rpi-rgb-led-matrix/include
$(eval $(call add_lib,$(NATIVE_ROOT)/src))

$(foreach lib, $(ARDUINO_LIBS), $(eval $(call add_lib,$(NATIVE_ROOT)/libraries/$(lib))))

USER_FOLDERS = $(shell find $(SKETCH_ROOT) -path $(SKETCH_ROOT)/build -prune -o -type d -print  | grep -Ev '\.(vscode|git)')
INC_USER_FOLDERS = $(foreach folder, $(USER_FOLDERS), -I$(folder))


OBJECTS += $(SRC_C:%.c=$(BUILD_ROOT)/%.o)
OBJECTS += $(SRC_CXX:%.cpp=$(BUILD_ROOT)/%.o)
OBJECTS += $(SRC_USER_C:%.c=$(BUILD_ROOT)/%.o)
OBJECTS += $(SRC_USER_CXX:%.cpp=$(BUILD_ROOT)/%.o)

SRCS += $(SRC_C)
SRCS += $(SRC_CXX)
SRCS += $(SRC_USER_C)
SRCS += $(SRC_USER_CXX)

$(TARGET): $(OBJECTS)
	$(Q)$(CXX) $(INC_USER_FOLDERS) $(INCLUDES) $(OBJECTS) $(LDFLAGS) -o $@
	@size $@

clean:
	rm -r $(BUILD_ROOT)
	rm $(TARGET)

print:
	@echo "LINUX_RENDERER_SDL:\t $(LINUX_RENDERER_SDL)"
	@echo "BUILD_ROOT:\t $(BUILD_ROOT)"
	@echo "INCLUDES:\t $(INCLUDES)"
	@echo "OBJECTS:\t $(OBJECTS)"
	@echo "SRCS:\t $(SRCS)"
	@echo "SKETCH:\t $(SKETCH)"
	@echo "ROOT:\t $(NATIVE_ROOT)"
	@echo "SRC_C   :\t $(SRC_C)"
	@echo "SRC_CXX :\t $(SRC_CXX)"
	@echo "SRC_USER:\t $(SRC_USER)"
	@echo "INC_USER_FOLDERS:\t $(INC_USER_FOLDERS)"
	@echo "CXXFLAGS :\t $(CXXFLAGS)"
	@echo "LDFLAGS:\t $(LDFLAGS)"


$(BUILD_ROOT)/%.o : %.c $(DEPDIR)/%.d
	@mkdir -p `dirname $@`
	$(Q)$(CC) $(DEPFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(POSTCOMPILE)

$(BUILD_ROOT)/%.o : %.cpp $(DEPDIR)/%.d
	@mkdir -p `dirname $@`
	$(Q)$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))
