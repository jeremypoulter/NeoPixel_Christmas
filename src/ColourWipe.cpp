// 
// 
// 

#include "ColourWipe.h"

void ColourWipe::setup()
{
  colours[0] = strip->Color(255, 0, 0);
  colours[1] = strip->Color(0, 255, 0);
  colours[2] = strip->Color(0, 0, 255);
  colours[3] = strip->Color(255, 0, 255);
  colours[4] = strip->Color(255, 255, 0);
  colours[5] = strip->Color(0, 255, 255);
  colours[6] = strip->Color(255, 255, 255);
  colours[7] = strip->Color(0, 0, 0);

  pixel = 0;
  index = 0;
}

unsigned long ColourWipe::loop(WakeReason reason)
{
  // Update the state  
  if (pixel >= strip->numPixels())
  {
    pixel = 0;
    if (++index >= numColors) {
      index = 0;
    }
  }

  // Set the pixel colour
  strip->setPixelColor(pixel++, colours[index]);
  strip->show();

  // Come back in a bit
  return wait;
}
