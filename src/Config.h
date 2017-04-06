#ifndef _CONFIG_H
#define _CONFIG_H

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

#if !defined(ENABLE_OFF) && !defined(ENABLE_COLOUR_WIPE) && !defined(ENABLE_THEATER_CHASE) && !defined(ENABLE_RAINBOW) && !defined(ENABLE_RAINBOW_CHASE) && !defined(ENABLE_SPARKLE)
#define ENABLE_OFF
#define ENABLE_COLOUR_WIPE
#define ENABLE_THEATER_CHASE
#define ENABLE_RAINBOW
#define ENABLE_RAINBOW_CHASE
#define ENABLE_SPARKLE
#endif

#endif // _CONFIG_H
