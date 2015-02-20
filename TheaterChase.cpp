// 
// 
// 

#include "TheaterChase.h"


void TheaterChase::setup()
{
  colours[0] = strip->Color(127, 0, 0);
  colours[1] = strip->Color(0, 127, 0);
  colours[2] = strip->Color(0, 0, 127);
  colours[3] = strip->Color(127, 0, 127);
  colours[4] = strip->Color(127, 127, 0);
  colours[5] = strip->Color(0, 127, 127);
  colours[6] = strip->Color(127, 127, 127);

  numberCycles = 0;
  q = 0;
  colour = 0;
}

unsigned long TheaterChase::loop(WakeReason reason)
{
  // turn every third pixel off
  for (int i = 0; i < strip->numPixels(); i = i + 3) {
    strip->setPixelColor(i + q, 0);
  }

  // Update the state  
  if (++q >= 3)
  {
    q = 0;
    if (++numberCycles >= 10)
    {
      numberCycles = 0;
      if (++colour >= numColors) {
        colour = 0;
      }
    }
  }

  // turn every third pixel on
  for (int i = 0; i < strip->numPixels(); i = i + 3) {
    strip->setPixelColor(i + q, colours[colour]);
  }
  strip->show();


  // Come back in a bit
  return wait;
}
