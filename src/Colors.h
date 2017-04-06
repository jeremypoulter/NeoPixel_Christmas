#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Linear interpolation of a value x within range x0, x1 to value
// y within range y0, y1.
inline float lerp(float x, float x0, float x1, float y0, float y1) {
  return y0+(x-x0)*((y1-y0)/(x1-x0));
}

// Helper function to gamma correct a pixel color.
uint32_t ColorGamma(uint8_t red, uint8_t green, uint8_t blue);

// Color gradient that represents a smooth transition from
// the specified primary to secondary color.
class Gradient {
public:
  Gradient(uint32_t primary, uint32_t secondary):
    _primary(primary), _secondary(secondary)
  {}
  ~Gradient() {}

  uint32_t interpolate(float x, float x0=0.0, float x1=1.0);

private:
  uint32_t _primary;
  uint32_t _secondary;
};

#endif
