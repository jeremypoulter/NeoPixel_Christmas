#include "Off.h"
#include "RainbowCycle.h"
#include "Rainbow.h"
#include "TheaterChase.h"
#include "ColourWipe.h"
#include "Sparkle.h"
#include "NeoPixelPattern.h"
#include "Config.h"

#include <MicroTasks.h>
#include <MicroTasksButtonEvent.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

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

#ifdef ENABLE_OFF
Off off = Off(&strip);
#endif
#ifdef ENABLE_COLOUR_WIPE
ColourWipe colourWipe = ColourWipe(&strip);
#endif
#ifdef ENABLE_THEATER_CHASE
TheaterChase theaterChase = TheaterChase(&strip);
#endif
#ifdef ENABLE_RAINBOW
Rainbow rainbow = Rainbow(&strip);
#endif
#ifdef ENABLE_RAINBOW_CHASE
RainbowCycle rainbowCycle = RainbowCycle(&strip);
#endif
#ifdef ENABLE_SPARKLE
Gradient sparkleColour = Gradient(ColorGamma(255, 255, 0), ColorGamma(0, 255, 255));  // Blue-Cyan - Red-Magenta
Sparkle sparkle = Sparkle(&strip, 0.1, 0.5, &sparkleColour);
#endif

NeoPixelPattern *patterns[] =
{
#ifdef ENABLE_OFF
  &off,
#endif
#ifdef ENABLE_COLOUR_WIPE
  &colourWipe,
#endif
#ifdef ENABLE_THEATER_CHASE
  &theaterChase,
#endif
#ifdef ENABLE_RAINBOW
  &rainbow,
#endif
#ifdef ENABLE_RAINBOW_CHASE
  &rainbowCycle,
#endif
#ifdef ENABLE_SPARKLE
  &sparkle,
#endif
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
