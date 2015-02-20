// ColourWipe.h

#ifndef _COLOURWIPE_h
#define _COLOURWIPE_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "NeoPixelPattern.h"

class ColourWipe : public NeoPixelPattern
{
  protected:
    static const int numColors = 8;

    uint16_t pixel;
    uint8_t wait;
    uint32_t colours[numColors];
    int index;

  public:
    ColourWipe(Adafruit_NeoPixel *strip) :
      pixel(0), wait(50), index(0),
      NeoPixelPattern(strip)
    {
    }

    void setup();
    unsigned long loop(WakeReason reason);
};

#endif

