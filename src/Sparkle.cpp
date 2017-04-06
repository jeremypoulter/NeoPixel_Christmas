#include "Sparkle.h"
#include "Colors.h"

#define NUM_FREQ 50

void Sparkle::randomizeFrequencies(uint16_t n, float f0, float f1) {
  if(n > NUM_FREQ) {
    n = NUM_FREQ;
  }
  if (_frequencies != NULL) {
    delete[] _frequencies;
  }
  _frequencies = new float[n];
  _n = n;
  for (uint16_t i=0; i<n; ++i) {
    _frequencies[i] = lerp(random(4096), 0, 4095, f0, f1);
  }
}

void Sparkle::setup()
{
}

unsigned long Sparkle::loop(MicroTasks::WakeReason reason)
{
  float currentS = millis() / 1000.0;
  for (uint16_t i=0; i<strip->numPixels(); ++i) {
    float t = sin(2.0*PI*_frequencies[i % NUM_FREQ]*currentS);
    uint32_t color = colors->interpolate(t, -1.0, 1.0);
    strip->setPixelColor(i, color);
  }
  strip->show();

  // Come back in a bit
  return 0;
}
