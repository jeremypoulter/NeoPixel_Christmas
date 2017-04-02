// Off.h

#ifndef _OFF_h
#define _OFF_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "NeoPixelPattern.h"
#include "MicroTasks.h"

class Off : public NeoPixelPattern
{
  protected:

  public:
    Off(Adafruit_NeoPixel *strip) : NeoPixelPattern(strip)
    {
    }

    void setup() {
    }
    unsigned long loop(MicroTasks::WakeReason reason)
    {
      uint32_t col = strip->Color(0, 0, 0);
      for (uint16_t i = 0; i < strip->numPixels(); i++) {
        strip->setPixelColor(i, col);
      }
      strip->show();

      return 50;
    }
};

#endif
