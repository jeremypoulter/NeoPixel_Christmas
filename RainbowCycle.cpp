// 
// 
// 

#include "RainbowCycle.h"

unsigned long RainbowCycle::loop(WakeReason reason)
{
  for (uint16_t i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, Wheel(((i * 256 / strip->numPixels()) + j) & 255));
  }
  strip->show();

  if (++j >= 256) {
    j = 0;
  }

  return wait;
}
