#include "TFT_LinuxWrapper.h"

TFT_LinuxWrapper tft;

void setup()
{
  Serial.begin(115200);
  Serial.print("test");
  tft.begin();
  tft.fillScreen(LTDC_BLACK);

  //tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.setTextColor(LTDC_GREEN);  tft.setTextSize(3);
  tft.println("Arduino TFT emulation on PC");
  tft.setTextColor(LTDC_YELLOW); tft.setTextSize(2);
}

int Counter=0;

void loop(void)
{

  tft.print( Counter ); tft.print(" ");
  Counter++;
  analogWrite(1,Counter);
  delay(1000);
  Serial.println(Counter);
}
