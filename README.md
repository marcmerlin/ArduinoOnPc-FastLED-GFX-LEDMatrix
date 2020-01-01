# ArduinoOnPc FastLED::GFX LEDMatrix Fork

## What?

I modified the original to display on an rPi using RGBPanels thanks to this driver:
https://github.com/marcmerlin/FastLED_RPIRGBPanel_GFX
ArduinoOnPC in used here to run Arduino code on Raspberry Pis to take advantage of
the extra CPU power, extra RAM, etc...  In my specific case, it also allows displaying
arduino code on the faster and more capable rpi-rgb-led-matrix RGBPanel driver.

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

To emulate a TFT this project uses X11. Therefore you have to install X11 support, something like:
```
sudo apt-get install libx11-dev
sudo pacman -Sy libx11
yum install libx11
```

## Compilation

### Makefile

```
# cd into any example in examples folder, for example:
cd examples/Adafruit_touchpaint

# Compile the code
make

# Execute
./Adafruit_touchpaint
```
