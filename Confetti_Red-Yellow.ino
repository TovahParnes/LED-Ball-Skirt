#include "FastLED.h"                                          // FastLED library.

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

// Fixed definitions cannot change on the fly.
#define LED_PIN 13// Data pin to connect to the strip.
#define COLOR_ORDER RGB                                       // Color order
#define LED_TYPE WS2811
#define NUM_LEDS 250                                          // Number of LED's

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

unsigned long previousMillis;                                 // Store last time the strip was updated.


// Define variables used by the sequences.
uint8_t   fade    = 2;                                        // Rate of fading
uint8_t   minhue  = 5;                                        // Minimum hue (color) value - red
uint8_t   maxhue  = 57;                                       // Maximum hue (color) value - yellow
uint8_t   sat     = 255;                                      // The saturation aka how mych color, 255 is max
uint8_t   bri     = 150;                                      // Max brightness for each LED
uint8_t thisdelay = 100;                                      // Delay of the sequence


void setup() {
  delay(1000);                                                // Power-up safety delay
  Serial.begin(57600);

  FastLED.addLeds<LED_TYPE,LED_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  set_max_power_in_volts_and_milliamps(5, 500);               // FastLED power management set at 5V, 500mA.
} // setup()


void loop () {

  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    Confetti();                                               // Run Confetti
  }
  FastLED.show();  
} // loop()

void Confetti() {                                             // Random colored speckles that blink in and fade smoothly
  int hue = random16(minhue, maxhue);                         // Determining the hue between "minhue" and "maxhue"
  int pos = random16(NUM_LEDS);                               // Pick an LED at random.

  fadeToBlackBy(leds, NUM_LEDS, fade);                        // Fade individual pixels to black by "fade" each tic

  leds[pos] += CHSV(hue, sat, bri);                           // Set random pixel to the random hue
} // Confetti()
