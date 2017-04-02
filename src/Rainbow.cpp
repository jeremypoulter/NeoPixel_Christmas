// 
// 
// 

#include "Rainbow.h"

void Rainbow::setup()
{
  j = 0;
}

unsigned long Rainbow::loop(WakeReason reason)
{
  for (uint16_t i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, Wheel((i + j) & 255));
  }
  strip->show();

  if (++j >= 256) {
    j = 0;
  }

  return wait;
}

uint32_t Rainbow::Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

