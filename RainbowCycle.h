// RainbowCycle.h

#ifndef _RAINBOWCYCLE_h
#define _RAINBOWCYCLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Rainbow.h"

class RainbowCycle : public Rainbow
{
  protected:


  public:
    RainbowCycle(Adafruit_NeoPixel *strip) : Rainbow(strip)
    {
    }

    unsigned long loop(WakeReason reason);
};

#endif

