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

// create neopixel opbjects for: time/shot/score
Adafruit_NeoPixel seconds = Adafruit_NeoPixel(N_LEDS, PIN_SECONDS, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel minutes = Adafruit_NeoPixel(N_LEDS, PIN_MINUTES, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel guestShots = Adafruit_NeoPixel(N_LEDS, PIN_GUESTSHOTS, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel guestScore = Adafruit_NeoPixel(N_LEDS, PIN_GUESTSCORE, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel homeShots = Adafruit_NeoPixel(N_LEDS, PIN_HOMESHOTS, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel homeScore = Adafruit_NeoPixel(N_LEDS, PIN_HOMESCORE, NEO_GRB + NEO_KHZ800);
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
  seconds.begin();    //in initialize neoPixel strip object (req'd)
  seconds.show();     // turn off all pixels in strip  
  minutes.begin();
  minutes.show();
  guestShots.begin();
  guestShots.show();
  guestScore.begin();
  guestScore.show();
  homeShots.begin();
  homeShots.show();
  homeScore.begin();
  homeScore.show();
}

void loop() {

  // To read message received from other Bluetooth Device
  if (Serial.available() > 0) { // Check if there is data coming
    msg = Serial.readString(); // Read the message as String
    Serial.println("Android Command: " + msg);
  }

  // Change score on serial command
  if (msg == "<increment home score>") {
    blank (homeScore);
    displayTen (homeScore);
    Serial.println("Home score incremented\n"); // Then send status message to Android
    msg = ""; // reset command
  }

  if (msg == "<decrement home score>") {
    //blank(&homeScore);
    //displayNine(&homeScore);
    Serial.println("Home score decremented\n"); // Then send status message to Android
    msg = ""; // reset command
  }

}

//=================================================================================================//
// functions to display each digit per neoPixel
//=================================================================================================//

// blank - call this function between functions to updating digits
void blank(Adafruit_NeoPixel* strip) {
  strip->fill(strip.Color(0, 0, 0), 0, 56);
}

// nine
static void displayNine(Adafruit_NeoPixel &strip) {
  tensBottom(strip, strip.Color(0, 0, 0));
  tensBottomR(strip, strip.Color(0, 0, 0));
  tensMiddle(strip, strip.Color(0, 0, 0));
  tensTop(strip, strip.Color(0, 0, 0));
  tensTopL(strip, strip.Color(0, 0, 0));
  tensTopR(strip, strip.Color(0, 0, 0));

  onesBottom(strip, strip.Color(255, 0, 0));
  onesBottomR(strip, strip.Color(255, 0, 0));
  onesMiddle(strip, strip.Color(255, 0, 0));
  onesTop(strip, strip.Color(255, 0, 0));
  onesTopL(strip, strip.Color(255, 0, 0));
  onesTopR(strip, strip.Color(255, 0, 0));
  strip.show();
}
// ten
static void displayTen(Adafruit_NeoPixel &strip) {
  tensBottomR(strip, strip.Color(255, 0, 0));
  tensTopR(strip, strip.Color(255, 0, 0));

  onesBottom(strip, strip.Color(255, 0, 0));
  onesBottomR(strip, strip.Color(255, 0, 0));
  onesTop(strip, strip.Color(255, 0, 0));
  onesTopL(strip, strip.Color(255, 0, 0));
  onesTopR(strip, strip.Color(255, 0, 0));
  strip.show();
}

//=================================================================================================//
// helper functions to display digits
//=================================================================================================//

//=================helper functions to display tens digits=====================//

static void tensBottom(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 4; i < 8; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTop(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 20; i < 24; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensBottomL(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 0; i < 4; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensBottomR(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 8; i < 12; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensMiddle(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 12; i < 16; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTopL(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 16; i < 20; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTopR(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 24; i < 28; i++) {
    strip.setPixelColor(i, c);
  }
}
//=================helper functions to display ones digits=====================//

static void onesBottom(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 32; i < 36; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTop(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 48; i < 52; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesBottomL(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 28; i < 32; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesBottomR(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 36; i < 40; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesMiddle(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 40; i < 44; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTopL(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 44; i < 48; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTopR(Adafruit_NeoPixel &strip, uint32_t c) {
  for (uint16_t i = 52; i < 56; i++) {
    strip.setPixelColor(i, c);
  }
}
