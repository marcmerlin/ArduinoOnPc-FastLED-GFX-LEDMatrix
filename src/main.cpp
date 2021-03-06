/*
 * main.cpp
 *
 *
 * 2017 July ChrisMicro
 *
 */

//#include <iostream>
//using namespace std;
//#include "./cores/arduino/SerialConsole.h"
#include "Arduino.h"
#include SKETCH_FILE


//SerialConsole Serial;

//#include "sketch.ino"
//#include "Blink.ino"
//#include "AnalogReadSerial.ino"
//#include "TFT_demo.ino"
//#include "Touch.ino"
//#include "Flappy.ino"
//#include "Adafruit_touchpaint.ino"
//#include "Adafruit_pictureEmbed.ino"
//#include "gameOfLife.ino"
//#include "cellArt.ino"
//#include "TekSpriteEditor.ino"
//#include "guiTest.ino"
//#include <TekSpriteEditor2.ino>

int main()
{
	//XWindow win(480,270,"test");
	//win.initScreen();

	//initScreen();

	setup();
	//XWindow staticTFT;
	//while(!staticTFT.MouseButtonRight_flag) // mousebutton flag of any window used for exit
	//while(!staticTFT.exitRequested())
	while(1) // tbd: no clean exit yet
	{
		loop();
		delayMicroseconds(10); // leave a little bit calculation time to other applications
#ifdef LINUX_RENDERER_SDL
		// SDL rendering is much faster than FastLED pixel pushing, so we add a delay to emulate
		// the delay you'd get from real LEDs like WS2812B
		delay(LINUX_RENDERER_SDL_MAIN_DELAY);
#endif
	}

	//closeScreen();

	//win.closeScreen();
	return 0;
}


/*
 ArduinoOnPc

 © ChrisMicro 2017.
 This file is part of ArduinoOnPc.
 ArduinoOnPc is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 GuiPittix is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public License
 along with ArduinoOnPc.  If not, see <http://www.gnu.org/licenses/>.

 web-site: https://github.com/ChrisMicro/ArduinoOnPc
 */
