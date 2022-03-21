/*
   Code for Arduino microcontroller to receive commands from android to update time and score.
*/
#include <Adafruit_NeoPixel.h>

#define N_LEDS 56 // number of individual LEDs in one neopixel strip

// pin assignment
#define PIN_SECONDS 11   // time - seconds
#define PIN_MINUTES 12   // time - minutes
#define PIN_GUESTSHOTS 5 // guestshots
#define PIN_GUESTSCORE 3 // guestscore
#define PIN_HOMESHOTS 7  // homeshots
#define PIN_HOMESCORE 4  // homescore

bool countDown = true; // for setting whether clock counts up or down
bool clockOn = false;
int homeScore, guestScore, homeShots, guestShots, t_secs = 0; // initialize score, shots and seconds to 0
int periodLength = 20;                                        // set period time
int t_mins = (countDown ? periodLength : 0);                  // initialize minutes
String msg;                                                   // string to read and print serial commands

// create neopixel object
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
// Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN_HOMESCORE, NEO_GRB + NEO_KHZ800); // tkcad testing
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN_HOMESCORE, NEO_RGBW + NEO_KHZ800);  // physical testing

// set default color
// uint32_t c = strip.Color(255, 0, 0); // tkcad testing
uint32_t c = strip.Color(0, 255, 0, 0);   // physical testing

void setup()
{
  // Initialization
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  msg = "";

  // initialize adafruitNeoPixels
  strip.begin(); // in initialize neoPixel strip object (req'd)
  strip.show();  // turn off all pixels in strip

  // initialize clock to 20 min, scores to 0
  strip.setPin(PIN_SECONDS);
  blank();
  displayDigit(t_secs);
  strip.setPin(PIN_MINUTES);
  blank();
  displayDigit(t_mins);
  strip.setPin(PIN_HOMESCORE);
  blank();
  displayDigit(homeScore);
  strip.setPin(PIN_GUESTSCORE);
  blank();
  displayDigit(guestScore);
  delay(100);
}

void loop()
{
  // To read message received from other Bluetooth Device
  if (Serial.available() > 0)
  {                            // Check if there is data coming
    msg = Serial.readString(); // Read the message as String
    Serial.println("Android Command: " + msg);
  }

  // Change score on serial command
  if (msg == "<increment home score>")
  {
    if (homeScore > 98)
      return;
    blank();                     // erase previous pattern
    strip.setPin(PIN_HOMESCORE); // always set pin
    homeScore++;
    displayDigit(homeScore);
    Serial.println(F("Home score incremented\n")); // send msg to android
    msg = "";                                   // reset command
  }
  if (msg == "<decrement home score>")
  {
    if (homeScore < 1)
      return;
    blank();
    strip.setPin(PIN_HOMESCORE);
    homeScore--;
    displayDigit(homeScore);
    Serial.println(F("Home score decremented\n"));
    msg = ""; // reset command
  }
  if (msg == "<increment guest score>")
  {
    if (guestScore > 98)
      return;
    blank();
    strip.setPin(PIN_GUESTSCORE); // always set pin
    guestScore++;
    displayDigit(guestScore);
    Serial.println(F("Guest score incremented\n"));
    msg = ""; // reset command
  }
  if (msg == "<decrement guest score>")
  {
    if (guestScore < 1)
      return;
    blank();
    strip.setPin(PIN_GUESTSCORE);
    guestScore--;
    displayDigit(guestScore);
    Serial.println(F("Guest score decremented\n"));
    msg = ""; // reset command
  }

  // Change shots on serial command
  if (msg == "<increment home shots>")
  {
    if (homeShots > 98)
      return;
    blank();
    strip.setPin(PIN_HOMESHOTS);
    homeShots++;
    displayDigit(homeShots);
    Serial.println(F("Home shots incremented\n"));
    msg = ""; // reset command
  }
  if (msg == "<decrement home shots>")
  {
    if (homeShots < 1)
      return;
    blank();
    strip.setPin(PIN_HOMESHOTS);
    homeShots--;
    displayDigit(homeShots);
    Serial.println(F("Home score decremented\n"));
    msg = ""; // reset command
  }
  if (msg == "<increment guest shots>")
  {
    if (guestShots > 98)
      return;
    blank();
    strip.setPin(PIN_GUESTSHOTS);
    guestShots++;
    displayDigit(guestShots);
    Serial.println(F("Guest shots incremented\n"));
    msg = ""; // reset command
  }
  if (msg == "<decrement guest shots>")
  {
    if (guestShots < 1)
      return;
    blank();
    strip.setPin(PIN_GUESTSHOTS);
    guestShots--;
    displayDigit(guestShots);
    Serial.println(F("Guest shots decremented\n"));
    msg = ""; // reset command
  }
  // update time on serial command
  if (msg == "<start>")
  {
    clockOn = true; // turn on clock
    Serial.println("Clock started\n");
    msg = "";
  }
  if (msg == "<stop>")
  {
    clockOn = false; // stop clock
    Serial.println(F("Clock stopped\n"));
    msg = "";
  }
  if (msg == "<reset>")
  {
    clockOn = false; // pause to reset clock
    resetClock();
    Serial.println(F("Clock reset\n"));
    msg = "";
  }
  if (msg == "<countdown mode>")
  { // change mode to countdown only when clock is stopped
    if (!clockOn)
    {
      countDown = true;
      Serial.println(F("countdown mode set\n"));
    }
    msg = "";
  }
  if (msg == "<countup mode>")
  { // change mode to countup only when clock is stopped
    if (!clockOn)
    {
      countDown = false;
      Serial.println(F("countup mode set\n"));
    }
    msg = "";
  }

  // functions that always run for time based on if clock is on
  if (clockOn)
    clockRunning();
}
//=================================================================================================//
// functions for time
//=================================================================================================//
static void clockRunning() // main function to handle time
{
  if (countDown)
  {
    if (t_mins > 0 && t_secs == 0)
    {              // reset seconds from 00 to 59
      t_secs = 59; // CHANGE TO 59 ON FULL SKETCH
      t_mins--;
      // display minutes
      strip.setPin(PIN_MINUTES);
      blank();
      displayDigit(t_mins);
    }
    else if (t_secs > 0) // decrement seconds only
      t_secs--;
    else
    {                  // when clock has gone to 00:00
      clockOn = false; // turn clock off so loop wont enter this function again
      Serial.println(F("Period over\n"));
      return;
    }
  }
  else
  {
    if (t_mins < periodLength && t_secs == 59) // reset seconds from 59 to 00
    {
      t_secs = 0;
      t_mins++;
      // display minutes
      strip.setPin(PIN_MINUTES);
      blank();
      displayDigit(t_mins);
    }
    else if (t_mins != periodLength && t_secs < 59) // increment seconds only -- CHANGE TO 59 ON FULL SKETCH
      t_secs++;
    else
    {                  // when clock has reached period length
      clockOn = false; // turn clock off so loop wont enter this function again
      Serial.println(F("Period over\n"));
      return;
    }
  }

  // display seconds
  strip.setPin(PIN_SECONDS);
  blank();
  displayDigit(t_secs);

  // wait 1s
  delay(1000);
}
static void resetClock() // reset clock
{
  t_mins = (countDown ? periodLength : 0);
  t_secs = 0;
  // display digits
  strip.setPin(PIN_MINUTES);
  blank();
  displayDigit(t_mins);
  strip.setPin(PIN_SECONDS);
  blank();
  displayDigit(t_secs);
}
//=================================================================================================//
// functions to update patterns on 7-seg displays
//=================================================================================================//
static void blank()
{
  strip.fill(strip.Color(0, 0, 0, 0), 0, 56);
}

// Array of function pointers to helper functions listed in order of circuit configuration
// function()  - [index]
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
    onesBottomL, onesBottom, onesBottomR, onesMiddle, onesTopL, onesTop, onesTopR};

// Array of patterns for 2 x 7-seg display, with 1 indicating LED on and 0 indicating LED off
const int patterns[][14] PROGMEM = {
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, // zero
    {1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1}, // one
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // two
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // three
    {1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1}, // four
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // five
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // six
    {1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1}, // seven
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // eight
    {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // nine

    {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1}, // ten
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1}, // eleven
    {0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1}, // twelve
    {0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1}, // thirteen
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1}, // fourteen
    {0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0}, // fifteen
    {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0}, // sixteen
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1}, // seventeen
    {0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}, // eighteen
    {0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1}, // nineteen
                                                
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1}, // twenty
    {1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1}, // twenty one
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // twenty two
    {1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // twenty three
    {1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1}, // twenty four
    {1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // twenty five
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // twenty six
    {1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1}, // twenty seven
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // twenty eight
    {1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // twenty nine
                                            
    {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1}, // thirty
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1}, // thirty one
    {0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // thirty two
    {0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // thirty three
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1}, // thirty four
    {0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // thirty five
    {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // thirty six
    {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1}, // thirty seven
    {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // thirty eight
    {0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // thirty nine
                                            
    {0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1}, // forty
    {0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1}, // forty one
    {0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1}, // forty two
    {0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1}, // forty three
    {0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1}, // forty four
    {0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0}, // forty five
    {0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, // forty six
    {0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1}, // forty seven
    {0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1}, // forty eight
    {0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1}, // forty nine
                                            
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // fifty
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1}, //  fifty one
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1}, //  fifty two
    {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1}, // fifty three
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1}, //  fifty four
    {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0}, //  fifty five
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0}, // fifty six
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1}, // fiftyseven
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, //  fifty eight
    {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1}, // fifty nine
                                            
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // sixty
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1}, // sixty one
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1}, // sixty two
    {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1}, // sixty three
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1}, // sixty four
    {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0}, // sixty five
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0}, // sixty six
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1}, // sixty seven
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1}, // sixty eight
    {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1}, // sixty nine
                                            
    {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1}, // seventy
    {0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1}, // seventy one
    {0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // seventy two
    {0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // seventy three
    {0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1}, // seventy four
    {0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // seventy five
    {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // seventy six
    {0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1}, // seventyseven
    {0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // seventy eight
    {0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // seventy nine
                                            
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, // eighty
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1}, // eighty one
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // eighty two
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // eighty three
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1}, // eighty four
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // eighty five
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // eighty six
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1}, // eightyseven
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // eighty eight
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // eighty nine
                                            
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}, // ninty
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1}, // ninty one
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // ninty two
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // ninty three
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1}, // ninty four
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // ninty five
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ninty six
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1}, // ninty seven
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // ninty eight
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // ninty nine
};

/// Displays the pattern of any valid digit on the 14 segment neopixel pattern
/// The parameter is any valid integer ranging between 0 to 99 to be displayed
static void displayDigit(int n)
{
  if (n < 0 || n > 99) // safe guard from integers out of range
    return;
  for (int i = 0; i < 14; i++)
    if (pgm_read_word(patterns[n] + i) == 1)
      (*displayStrip[i])();
  strip.show();
}
//=================================================================================================//
// helper functions to update individual strips
//=================================================================================================//

//=================helper functions to display tens digits=====================//
static void tensBottom()
{
  for (uint16_t i = 4; i < 8; i++)
    strip.setPixelColor(i, c);
}
static void tensTop()
{
  for (uint16_t i = 20; i < 24; i++)
    strip.setPixelColor(i, c);
}
static void tensBottomL()
{
  for (uint16_t i = 0; i < 4; i++)
    strip.setPixelColor(i, c);
}
static void tensBottomR()
{
  for (uint16_t i = 8; i < 12; i++)
    strip.setPixelColor(i, c);
}
static void tensMiddle()
{
  for (uint16_t i = 12; i < 16; i++)
    strip.setPixelColor(i, c);
}
static void tensTopL()
{
  for (uint16_t i = 16; i < 20; i++)
    strip.setPixelColor(i, c);
}
static void tensTopR()
{
  for (uint16_t i = 24; i < 28; i++)
    strip.setPixelColor(i, c);
}
//=================helper functions to display ones digits=====================//
static void onesBottom()
{
  for (uint16_t i = 32; i < 36; i++)
    strip.setPixelColor(i, c);
}
static void onesTop()
{
  for (uint16_t i = 48; i < 52; i++)
    strip.setPixelColor(i, c);
}
static void onesBottomL()
{
  for (uint16_t i = 28; i < 32; i++)
    strip.setPixelColor(i, c);
}
static void onesBottomR()
{
  for (uint16_t i = 36; i < 40; i++)
    strip.setPixelColor(i, c);
}
static void onesMiddle()
{
  for (uint16_t i = 40; i < 44; i++)
    strip.setPixelColor(i, c);
}
static void onesTopL()
{
  for (uint16_t i = 44; i < 48; i++)
    strip.setPixelColor(i, c);
}
static void onesTopR()
{
  for (uint16_t i = 52; i < 56; i++)
    strip.setPixelColor(i, c);
}
