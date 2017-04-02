// TheaterChase.h

#ifndef _THEATERCHASE_h
#define _THEATERCHASE_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "NeoPixelPattern.h"

class TheaterChase : public NeoPixelPattern
{
  protected:
    static const int numColors = 7;

    int numberCycles;
    int q;

    uint8_t wait;

    uint32_t colours[numColors];
    int colour;

  public:
    TheaterChase(Adafruit_NeoPixel *strip) :
      numberCycles(0), wait(50), colour(0), q(0),
      NeoPixelPattern(strip)
    {
    }

    void setup();
    unsigned long loop(WakeReason reason);
};

#endif

