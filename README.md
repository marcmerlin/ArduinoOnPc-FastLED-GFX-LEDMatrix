# ArduinoOnPc FastLED::GFX LEDMatrix Fork

Blog posts with details:  
* Raspberry Pi/RGB Panels: http://marc.merlins.org/perso/arduino/post_2020-01-01_Running-FastLED_-Adafruit_GFX_-and-LEDMatrix-code-on-High-Resolution-RGBPanels-with-a-Raspberry-Pi.html
* Linux/Intel and X11/SDL: http://marc.merlins.org/perso/arduino/post_2020-01-24_Running-Arduino-code-with-2D-FastLED_-Adafruit_GFX_-and-LEDMatrix-displays-on-Linux.html


## What?

With this software you can run an Arduino Sketch on your PC and is specifically designed to test code written for any of:
- https://github.com/marcmerlin/Framebuffer_GFX (base class)
- https://github.com/pixelmatix/SmartMatrix
- https://github.com/adafruit/Adafruit-GFX-Library
- https://github.com/FastLED/FastLED  
- https://github.com/marcmerlin/LEDMatrix  
using SDL on Linux

If you have run code that runs on any of:
- https://github.com/marcmerlin/FastLED_NeoMatrix/
- https://github.com/marcmerlin/SmartMatrix_GFX/
- https://github.com/marcmerlin/FastLED_SPITFT_GFX (SSD1331, ILI9341, and ST7735 TFTs)  
it can then run with this linux/SDL backend too.

I modified the upstream ArduinoOnPC to display on an rPi using RGBPanels thanks to this driver:
https://github.com/marcmerlin/FastLED_RPIRGBPanel_GFX
ArduinoOnPC is used here to run Arduino code on Raspberry Pis to take advantage of
the extra CPU power, extra RAM, etc...  In my specific case, it also allows displaying
arduino code on the faster and more capable rpi-rgb-led-matrix RGBPanel driver.

After you run git submodules init, you will find my suite of demos from
https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos


## Three display drivers: SDL (default on linux/intel), X11 (non default, slow, linux/intel), RGBPanel (linux/rPi)

For development/Debugging, you can also run on PC using the (slow) X11 output or faster SDL output.
https://github.com/marcmerlin/ArduinoOnPc-FastLED-GFX-LEDMatrix/blob/master/examples/Makefile  
is used to select X11 vs SDL rendering on linux/intel. rPi is auto detected in 
https://github.com/marcmerlin/ArduinoOnPc-FastLED-GFX-LEDMatrix/blob/952bb957162238dc0ef6cbb0c3355e1c48959500/makeNativeArduino.mk#L32  

In turn this affects 
https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L39  which will use one of the 3 available rendering backend for ArduinoOnPc.


### SDL Driver
Please see this code to see how to use the driver:
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L48
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L268
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L722

Because the SDL driver is much faster than talking to real FastLED, the code for linux introduces a slowdown delay (LINUX_RENDERER_SDL_MAIN_DELAY) defined here: https://github.com/marcmerlin/ArduinoOnPc-FastLED-GFX-LEDMatrix/blob/19e23178f66363e95ebd818822b49fcc4ea26db7/examples/Makefile#L7

![102_demo_snaps](https://user-images.githubusercontent.com/1369412/71480161-a982c800-27ac-11ea-8f0e-fb149b6a9ae2.jpg)
![103_demo_snaps](https://user-images.githubusercontent.com/1369412/71480163-abe52200-27ac-11ea-9cb1-f4d23bdf96ac.jpg)

### X11 Driver
Please see this code to see how to use the driver:
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L44
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L239
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L716

### Rpi RGBPanel Driver
Please see this code to see how to use the driver:
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L40
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L293
* https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/4436f8b5a71ceea4ef480f75f83b811b037c2cf6/neomatrix_config.h#L727

![image](https://user-images.githubusercontent.com/1369412/71642449-9cce0a80-2cab-11ea-876d-8c9bd6ef3b72.png)

## Original "What?" (when this project was only meant to be run on PCs for debugging):
With this software you can run an Arduino Sketch on your PC.
You don't need an Arduino hardware.
The focus here is mainly on TFTs connected to an Arduino.

This software is made for Linux using the X11 window manager.
If you want to use it on windows the only current option is a virtual machine.

## Original "Why?" (also when this project was only meant to be run on PCs for debugging):

Some Arduino boards do not have a debugging possibility.
To find the errors in your sketches it might be usefull to be able to use a debugger.
Using this tool you can debug your program locally, and develop without having
to tinker with any additional hardware.

As a reminder this fork is also meant to run Arduino code on rPi.


## Installation / Requirements

You need [gcc](https://gcc.gnu.org/) and [make](https://www.gnu.org/software/make/) installed.

The project uses git submodules to include some Arduino libraries. To get them, you have to run
```
git submodule init
git submodule update
```
after checking out the repository.

List of libraries imported (git submodule list)

APIs:
* libraries/FastLED 
* libraries/LEDMatrix 
* libraries/Framebuffer_GFX: holds a CRGB framebuffer and bridges to Adafruit GFX APIs

Drivers:
* libraries/FastLED_TFTWrapper_GFX: Small wrapper I wrote to display a Framebuffer_GFX framebuffer in ArduinoOnPC's X11 renderer
* libraries/FastLED_RPIRGBPanel_GFX: Glue driver that feeds a Framebuffer_GFX framebuffer to rpi-rgb-led-matrix to display on RGB Panels on Raspberry Pi (not needed on a PC)
* rpi-rgb-led-matrix: Henner Zeller's indispensable library to display on RGBPanels on rPi.

Demo code I gathered/ported/sorted by the API they use (FastLED, FastLED::NeoMatrix/Adafruit::GFX, or LEDMatrix):
* examples/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos 

If you use FastLED_RPIRGBPanel_GFX, make sure you first build rpi-rgb-led-matrix:
```
cd rpi-rgb-led-matrix; make
```

## X11

If you don't use my special rPI RGBPanel driver ( https://github.com/marcmerlin/FastLED_RPIRGBPanel_GFX ), 
to emulate a TFT this project then uses X11. Therefore you have to install X11 support, something like:
```
sudo apt-get install libx11-dev
sudo pacman -Sy libx11
yum install libx11
```

BUG: Even if you use the RGB Panel output, compilation will likely needlessly require X11 even if the end binary
will not require it.

## Compilation

### Makefile


```
# GFX examples that use either SDL (default on intel), X11, or RGBPanel (Default on rPi) output:
cd examples/GFX_Sublime_Demos/
examples/GFX_Sublime_Demos$ make
examples/GFX_Sublime_Demos$ ./Sublime_Demo
# Use numeric keypad + to make brighter or n/p to select demo
```

```
# Original examples that only compile with the slow X11 backend (not prefixed by GFX_):
cd examples/Adafruit_touchpaint

# Compile the code
make

# Execute
./Adafruit_touchpaint
```
