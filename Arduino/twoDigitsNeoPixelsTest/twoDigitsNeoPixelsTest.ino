/*
 * Test sketch for 2 digits on one pin
 * using Bluetooth connection
 * by Droiduino
 */
#include <Adafruit_NeoPixel.h>

#define N_LEDS  56
// pin assignment
// time
#define TEST_PIN  12

String msg,cmd;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, TEST_PIN, NEO_GRB + NEO_KHZ800); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  msg = "";

  strip.begin();
  strip.show();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  //nine
  tensBottom(strip.Color(0, 0, 0));
  tensBottomR(strip.Color(0, 0, 0));
  tensMiddle(strip.Color(0, 0, 0));
  tensTop(strip.Color(0, 0, 0));
  tensTopL(strip.Color(0, 0, 0));
  tensTopR(strip.Color(0, 0, 0));
  
  onesBottom(strip.Color(255, 0, 0));
  onesBottomR(strip.Color(255, 0, 0));
  onesMiddle(strip.Color(255, 0, 0));
  onesTop(strip.Color(255, 0, 0));
  onesTopL(strip.Color(255, 0, 0));
  onesTopR(strip.Color(255, 0, 0));
  strip.show();
  delay(5000);
  blank();

  //ten
  tensBottomR(strip.Color(255, 0, 0));
  tensTopR(strip.Color(255, 0, 0));
  
  onesBottom(strip.Color(255, 0, 0));
  onesBottomR(strip.Color(255, 0, 0));
  onesTop(strip.Color(255, 0, 0));
  onesTopL(strip.Color(255, 0, 0));
  onesTopR(strip.Color(255, 0, 0));
  strip.show();
  delay(5000);
  blank();

}

//=================reset both digits=====================//

static void blank() {
  strip.fill(strip.Color(0, 0, 0), 0, 56);
}

//=================functions for tens=====================//

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
