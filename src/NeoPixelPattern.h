// NeoPixelPattern.h

#ifndef _NEOPIXELPATTERN_h
#define _NEOPIXELPATTERN_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <MicroTasksTask.h>
#include <Adafruit_NeoPixel.h>

class NeoPixelPattern : public MicroTasks::Task
{
  protected:
    Adafruit_NeoPixel *strip;

  public:
    NeoPixelPattern(Adafruit_NeoPixel *strip) :
      strip(strip)
    {}
};

#endif
