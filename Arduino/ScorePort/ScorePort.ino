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
#define PIN_GUESTSCORE     11
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
    displayTwo();
    msg = ""; // reset command
  }

  if (msg == "<decrement home score>") {
    Serial.println("Home score decremented\n"); // Then send status message to Android
    blank();
    strip.setPin(PIN_GUESTSCORE);
    displayOne();
    msg = ""; // reset command
  }
}

//=================================================================================================//
// functions to update patterns on 7-seg displays
//=================================================================================================//
static void blank() {
  strip.fill(strip.Color(0, 0, 0), 0, 56);
}

// arr of function pointers to helper functions, in order of circuit configuration
// function    - [index]
// tensBottomL - 0
// tensBottom  - 1
// tensBottomR - 2
// tensMiddle  - 3
// tensTopL    - 4
// tensTop     - 5
// tensTopR    - 6
// onesBottomL - 7
// onesBottom  - 8
// onesBottomR - 9
// onesMiddle - 10
// onesTopL   - 11
// onesTop    - 12
// onesTopR   - 13
void (*displayStrip[])() = {
  tensBottomL, tensBottom, tensBottomR, tensMiddle, tensTopL, tensTop, tensTopR,
  onesBottomL, onesBottom, onesBottomR, onesMiddle, onesTopL, onesTop, onesTopR
};

// static void blankFirstDigit() {             // set tens to off
//   strip.fill(strip.Color(0, 0, 0), 0, 28);
// }

//one
static void displayOne() {
  (*displayStrip[7])();
  (*displayStrip[11])();
  strip.show();
}

//two
static void displayTwo() {
  (*displayStrip[8])();
  (*displayStrip[7])();
  (*displayStrip[10])();
  (*displayStrip[12])(); 
  (*displayStrip[13])();
  strip.show();
}

// //three

// //four

// //five

// //six

// //seven

// //eight

// //nine
// static void displayNine(){
//   blankFirstDigit();
//   onesBottom(strip.Color(255, 0, 0));
//   onesBottomR(strip.Color(255, 0, 0));
//   onesMiddle(strip.Color(255, 0, 0));
//   onesTop(strip.Color(255, 0, 0));
//   onesTopL(strip.Color(255, 0, 0));
//   onesTopR(strip.Color(255, 0, 0));
//   strip.show();
// }

// //ten
// static void displayTen(){
//   tensBottomR(strip.Color(255, 0, 0));
//   tensTopR(strip.Color(255, 0, 0));
//   onesBottom(strip.Color(255, 0, 0));
//   onesBottomR(strip.Color(255, 0, 0));
//   onesBottomL(strip.Color(255, 0, 0));
//   onesTop(strip.Color(255, 0, 0));
//   onesTopL(strip.Color(255, 0, 0));
//   onesTopR(strip.Color(255, 0, 0));
//   strip.show();
// }

//eleven

//twelve





// arr of patterns for 2 x 7-seg display, with 1 indicating LED on and 0 indicating LED off
int patterns[9][14] = {{0, 0, 0, 0, 0, 0, 0,    0, 0, 0, 1, 0, 0, 0}, // zero
                       {0, 0, 0, 0, 0, 0, 0,    0, 0, 1, 0, 0, 0, 1}, // one
                       {0, 0, 0, 0, 0, 0, 0,    1, 1, 0, 1, 0, 1, 1}, // two
                       {0, 0, 0, 0, 0, 0, 0,    0, 1, 1, 1, 0, 1, 1}, // three
                      };

//=================================================================================================//
//helper functions to update individual strips
//=================================================================================================//
//=================helper functions to display tens digits=====================//
uint32_t c = strip.Color(255, 0, 0);

static void tensBottom() {
  for(uint16_t i=4; i<8; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTop() {
  for(uint16_t i=20; i<24; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensBottomL() {
  for(uint16_t i=0; i<4; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensBottomR() {
  for(uint16_t i=8; i<12; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensMiddle() {
  for(uint16_t i=12; i<16; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTopL() {
  for(uint16_t i=16; i<20; i++) {
    strip.setPixelColor(i, c);
  }
}
static void tensTopR() {
  for(uint16_t i=24; i<28; i++) {
    strip.setPixelColor(i, c);
  }
}
//=================helper functions to display ones digits=====================//
static void onesBottom() {
  for(uint16_t i=32; i<36; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTop() {
  for(uint16_t i=48; i<52; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesBottomL() {
  for(uint16_t i=28; i<32; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesBottomR() {
  for(uint16_t i=36; i<40; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesMiddle() {
  for(uint16_t i=40; i<44; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTopL() {
  for(uint16_t i=44; i<48; i++) {
    strip.setPixelColor(i, c);
  }
}
static void onesTopR() {
  for(uint16_t i=52; i<56; i++) {
    strip.setPixelColor(i, c);
  }
}

// 
// https://www.tinkercad.com/things/ipT19Fd9uXQ-fabulous-luulia-amur/editel?sharecode=mgtLCh8mOluWIWKFgePiFf8DEEMq6n7NJTlxXU7f0uQ
// function pter arr
// https://forum.arduino.cc/t/array-of-functions/429541/2
