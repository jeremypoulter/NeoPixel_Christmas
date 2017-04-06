// Sparkle.h

#ifndef _SPARKLE_h
#define _SPARKLE_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "NeoPixelPattern.h"
#include "Colors.h"

class Sparkle : public NeoPixelPattern
{
  protected:
    float* _frequencies;
    uint16_t _n;
    Gradient *colors;

    void randomizeFrequencies(uint16_t n, float f0, float f1);

  public:
    Sparkle(Adafruit_NeoPixel *strip, float f0, float f1, Gradient *colors) :
      NeoPixelPattern(strip),
      colors(colors)
    {
      randomizeFrequencies(strip->numPixels(), f0, f1);
    }
    ~Sparkle() {
      if (_frequencies != NULL) {
        delete[] _frequencies;
      }
    }

    void setup();
    unsigned long loop(MicroTasks::WakeReason reason);
};

#endif
