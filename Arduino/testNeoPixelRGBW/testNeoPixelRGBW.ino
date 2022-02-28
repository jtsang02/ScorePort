/*
 * Test sketch for 2 digits on one pin
 * using Bluetooth connection
 * by Droiduino
 */
#include <Adafruit_NeoPixel.h>

#define N_LEDS              120
#define TEST_PIN            12   // pin assignment

// create neopixel object
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, TEST_PIN, NEO_RGBW + NEO_KHZ800); 

// set default color
uint32_t red = strip.Color(0, 255, 0, 0);    

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  strip.begin();
  strip.show();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  strip.setPin(TEST_PIN);
  allOn(red);
  strip.show();
  delay(5000);

}

//=================reset both digits=====================//

static void blank() {
  strip.fill(strip.Color(0, 0, 0, 0), 0, N_LEDS);
}

//=================functions for tens=====================//

static void allOn(uint32_t c) {
  for(uint16_t i=0; i<120; i++) {
    strip.setPixelColor(i, c);
  }
}

static void tensBottom(uint32_t c) {
  for(uint16_t i=4; i<8; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTop(uint32_t c) {
  for(uint16_t i=20; i<24; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensBottomL(uint32_t c) {
  for(uint16_t i=0; i<4; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensBottomR(uint32_t c) {
  for(uint16_t i=8; i<12; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensMiddle(uint32_t c) {
  for(uint16_t i=12; i<16; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTopL(uint32_t c) {
  for(uint16_t i=16; i<20; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTopR(uint32_t c) {
  for(uint16_t i=24; i<28; i++) {
    strip.setPixelColor(i, c);
  }
}

//=================functions for ones=====================//

static void onesBottom(uint32_t c) {
  for(uint16_t i=32; i<36; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTop(uint32_t c) {
  for(uint16_t i=48; i<52; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesBottomL(uint32_t c) {
  for(uint16_t i=28; i<32; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesBottomR(uint32_t c) {
  for(uint16_t i=36; i<40; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesMiddle(uint32_t c) {
  for(uint16_t i=40; i<44; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTopL(uint32_t c) {
  for(uint16_t i=44; i<48; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTopR(uint32_t c) {
  for(uint16_t i=52; i<56; i++) {
    strip.setPixelColor(i, c);
  }
}
