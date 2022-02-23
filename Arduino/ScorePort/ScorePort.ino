/*
   Tutorial to connect Arduino board to Android Smartphone
   using Bluetooth connection
   by Droiduino
*/
#include <Adafruit_NeoPixel.h>

#define N_LEDS            56
// pin assignment
// time
#define PIN_SECONDS        3
#define PIN_MINUTES        4
// guest score and shots
#define PIN_GUESTSHOTS     5
#define PIN_GUESTSCORE     6
// home score and shots
#define PIN_HOMESHOTS      7
#define PIN_HOMESCORE      12

String msg, cmd;

// create neopixel object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN_HOMESCORE, NEO_GRB + NEO_KHZ800); 
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
  // Initialization
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  msg = "";

  // initialize adafruitNeoPixels
  strip.begin();    //in initialize neoPixel strip object (req'd)
  strip.show();     // turn off all pixels in strip  
}

void loop() {

  // To read message received from other Bluetooth Device
  if (Serial.available() > 0) { // Check if there is data coming
    msg = Serial.readString(); // Read the message as String
    Serial.println("Android Command: " + msg);
  }

  // Change score on serial command
  if (msg == "<increment home score>") {
    Serial.println("Home score incremented\n"); // Then send status message to Android
    blank();  // best to start by calling this func
    strip.setPin(PIN_GUESTSCORE);  // always set pin
    displayTen();
    msg = ""; // reset command
  }

  if (msg == "<decrement home score>") {
    Serial.println("Home score decremented\n"); // Then send status message to Android
    blank();
    strip.setPin(PIN_GUESTSCORE);
    displayNine();
    msg = ""; // reset command
  }
}

//=================================================================================================//
// functions to update patterns on 7-seg displays
//=================================================================================================//
static void blank() {
  strip.fill(strip.Color(0, 0, 0), 0, 56);
}

//nine
static void displayNine(){
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
}

//ten
static void displayTen(){
  tensBottomR(strip.Color(255, 0, 0));
  tensTopR(strip.Color(255, 0, 0));
  onesBottom(strip.Color(255, 0, 0));
  onesBottomR(strip.Color(255, 0, 0));
  onesTop(strip.Color(255, 0, 0));
  onesTopL(strip.Color(255, 0, 0));
  onesTopR(strip.Color(255, 0, 0));
  strip.show();
}

//=================================================================================================//
//helper functions to update individual strips
//=================================================================================================//
//=================helper functions to display tens digits=====================//
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
//=================helper functions to display ones digits=====================//
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
