// Rainbow.h

#ifndef _RAINBOW_h
#define _RAINBOW_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "NeoPixelPattern.h"

class Rainbow : public NeoPixelPattern
{
  protected:
    uint8_t wait;
    uint16_t j;

    uint32_t Wheel(byte WheelPos);

  public:
    Rainbow(Adafruit_NeoPixel *strip) :
      wait(20), j(0), NeoPixelPattern(strip) 
    {
    }

    void setup();
    unsigned long loop(WakeReason reason);
};

#endif

