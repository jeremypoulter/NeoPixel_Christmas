#include "Off.h"
#include "RainbowCycle.h"
#include "Rainbow.h"
#include "TheaterChase.h"
#include "ColourWipe.h"
#include "Sparkle.h"
#include "NeoPixelPattern.h"

#include <MicroTasks.h>
#include <MicroTasksButtonEvent.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#ifndef BUTTON_PIN
#define BUTTON_PIN    3
#endif

#ifndef PIXEL_PIN
#define PIXEL_PIN     4
#endif

#ifndef LED_PIN
#define LED_PIN       13
#endif

#ifndef PIXELS
#define PIXELS  300
#endif

#ifndef BRIGHTNESS
#define BRIGHTNESS            255   // NeoPixel brightness
#endif

#define BUTTON_INT    (BUTTON_PIN - 2)

#ifdef __AVR_ATtiny85__
#include <SoftwareSerial.h>
#define Serial SoftwareSerial
#define SERIAL_BAUD 9600
#else
#define SERIAL_BAUD 115200
#endif

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

Off off = Off(&strip);
ColourWipe colourWipe = ColourWipe(&strip);
TheaterChase theaterChase = TheaterChase(&strip);
Rainbow rainbow = Rainbow(&strip);
RainbowCycle rainbowCycle = RainbowCycle(&strip);
Gradient sparkleColour = Gradient(ColorGamma(255, 255, 0), ColorGamma(0, 255, 255));  // Blue-Cyan - Red-Magenta
Sparkle sparkle = Sparkle(&strip, 0.1, 0.5, &sparkleColour);

NeoPixelPattern *patterns[] =
{
  &off,
  &colourWipe,
  &theaterChase,
  &rainbow,
  &rainbowCycle,
  &sparkle
};

const int numberPatterns = ARRAY_ITEMS(patterns);

MicroTasks::ButtonEvent buttonEvent(BUTTON_INT, FALLING, 200);

class SwitchPattern : public MicroTasks::Task
{
  private:
    int pattern;
    MicroTasks::EventListener buttonEventListener;

  public:
    SwitchPattern();

    void setup();
    unsigned long loop(MicroTasks::WakeReason reason);
};

SwitchPattern::SwitchPattern() :
  Task(), pattern(0), buttonEventListener(this)
{
}

void SwitchPattern::setup()
{
  buttonEvent.Register(&buttonEventListener);
  buttonEvent.Attach();

  MicroTask.startTask(patterns[pattern]);
}

unsigned long SwitchPattern::loop(MicroTasks::WakeReason reason)
{
  if (WakeReason_Event == reason &&  buttonEvent.IsTriggered())
  {
    MicroTask.stopTask(patterns[pattern]);
    if (++pattern >= numberPatterns) {
      pattern = 0;
    }
    Serial.print("Pattern ");
    Serial.println(pattern);
    MicroTask.startTask(patterns[pattern]);
  }

  // return when we next want to be called
  return MicroTask.Infinate | MicroTask.WaitForEvent;
}

SwitchPattern switchPattern = SwitchPattern();


void setup()
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  Serial.begin(SERIAL_BAUD);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(BRIGHTNESS);

  // Start our task
  MicroTask.startTask(&switchPattern);
}

void loop() {
  // Update the tasks state
  MicroTask.update();
  digitalWrite(LED_PIN, !digitalRead(BUTTON_PIN));
}
