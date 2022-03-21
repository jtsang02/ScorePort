// simple sketch for testing neopixel strip
#include <Adafruit_NeoPixel.h>

// pin assignment
#define N_LEDS  56
#define TESTPIN  12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, TESTPIN, NEO_RGBW + NEO_KHZ800);  // create NP object for physical testing
uint32_t c = strip.Color(0, 255, 0, 0);   // set color for physical testing

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
}

void loop() {
  allOn();
}

static void allOn() {
  for(uint16_t i=0; i<N_LEDS; i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
