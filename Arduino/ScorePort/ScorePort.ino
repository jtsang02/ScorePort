/*
 * Tutorial to connect Arduino board to Android Smartphone
 * using Bluetooth connection
 * by Droiduino
 */
#include <Adafruit_NeoPixel.h>

#define N_LEDS            28
// pin assignment
// time
#define PIN_SECONDS_L      2    
#define PIN_SECONDS_R      3
#define PIN_MINUTES_L      4    
#define PIN_MINUTES_R      5
// guest score and shots
#define PIN_GUESTSHOTS_L   6      
#define PIN_GUESTSHOTS_R   7
#define PIN_GUESTSCORE_L   8      
#define PIN_GUESTSCORE_R   9
// home score and shots
#define PIN_HOMESHOTS_L    10          
#define PIN_HOMESHOTS_R    11
#define PIN_HOMESCORE_L    12      
#define PIN_HOMESCORE_R    13

const int ledPin = 13; // Built in LED in Arduino board
String msg,cmd;  

// store all neopixels in an array
Adafruit_NeoPixel neoPixels[] = {

  Adafruit_NeoPixel(N_LEDS, PIN_SECONDS_L, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_SECONDS_R, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_MINUTES_L, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_MINUTES_R, NEO_GRB + NEO_KHZ800),

  Adafruit_NeoPixel(N_LEDS, PIN_GUESTSHOTS_L, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_GUESTSHOTS_R, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_GUESTSCORE_L, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_GUESTSCORE_R, NEO_GRB + NEO_KHZ800),

  Adafruit_NeoPixel(N_LEDS, PIN_HOMESHOTS_L, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_HOMESHOTS_R, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_HOMESCORE_L, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN_HOMESCORE_R, NEO_GRB + NEO_KHZ800),
};

void setup() {
  // Initialization
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  msg = "";

  // initialize adafruitNeoPixels
  for (int i = 0; i < 12; i++){
    neoPixels[i].begin();
  }
  npTest.begin();
}

void loop() {
  
  // To read message received from other Bluetooth Device
  if (Serial.available() > 0){ // Check if there is data coming
    msg = Serial.readString(); // Read the message as String
    Serial.println("Android Command: " + msg);
  }

  // Control LED in Arduino board
  if (msg == "<increment home score>"){
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Home score incremented\n"); // Then send status message to Android
    msg = ""; // reset command
  } 

  if (msg == "<decrement home score>"){
    digitalWrite(ledPin, LOW); // Turn off LED
    Serial.println("Home score decremented\n"); // Then send status message to Android
    blank(neoPixels[1]);
    displayZero(neoPixels[1]);            // 
    msg = ""; // reset command
  }

}

//=================================================================================================//
// functions to display each digit per neoPixel
//=================================================================================================//

// blank - call this function between functions to updating digits
void blank(Adafruit_NeoPixel np) {
  np.fill(np.Color(0, 0, 0), 0, 28);
}
// zero
void displayZero(Adafruit_NeoPixel np){
  bottom(np, np.Color(255, 0, 0));
  bottomL(np, np.Color(255, 0, 0));
  bottomR(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  topL(np, np.Color(255, 0, 0));
  topR(np, np.Color(255, 0, 0));
  np.show();
}
// one 
void displayOne(Adafruit_NeoPixel np){
  bottomR(np, np.Color(255, 0, 0)); 
  topR(np, np.Color(255, 0, 0)); 
  np.show();
}
// two
void displayTwo(Adafruit_NeoPixel np){
  bottom(np, np.Color(255, 0, 0));
  bottomL(np, np.Color(255, 0, 0));
  middle(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  topR(np, np.Color(255, 0, 0));
  np.show();
}
// three 
static void displayThree(Adafruit_NeoPixel np){
  bottom(np, np.Color(255, 0, 0));
  bottomR(np, np.Color(255, 0, 0));
  middle(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  topR(np, np.Color(255, 0, 0));
  np.show();
}
// four
static void displayFour(Adafruit_NeoPixel np){
  bottomR(np, np.Color(255, 0, 0));
  middle(np, np.Color(255, 0, 0));
  topR(np, np.Color(255, 0, 0));
  topL(np, np.Color(255, 0, 0));
  np.show();
}
// five
static void displayFive(Adafruit_NeoPixel np){
  bottom(np, np.Color(255, 0, 0));
  bottomR(np, np.Color(255, 0, 0));
  middle(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  topL(np, np.Color(255, 0, 0));
  np.show();
}
// six
static void displaySix(Adafruit_NeoPixel np){
  bottom(np, np.Color(255, 0, 0));
  bottomR(np, np.Color(255, 0, 0));
  bottomL(np, np.Color(255, 0, 0));
  middle(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  topL(np, np.Color(255, 0, 0));
  np.show();
}
// seven
static void displaySeven(Adafruit_NeoPixel np){
  bottomR(np, np.Color(255, 0, 0)); 
  topR(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  np.show();
}
// eight
static void displayEight(Adafruit_NeoPixel np){
  bottom(np, np.Color(255, 0, 0));
  bottomR(np, np.Color(255, 0, 0));
  bottomL(np, np.Color(255, 0, 0));
  middle(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  topL(np, np.Color(255, 0, 0));
  topR(np, np.Color(255, 0, 0));
  np.show();
}
// nine
static void displayNine(Adafruit_NeoPixel np){
  bottom(np, np.Color(255, 0, 0));
  bottomR(np, np.Color(255, 0, 0));
  middle(np, np.Color(255, 0, 0));
  top(np, np.Color(255, 0, 0));
  topL(np, np.Color(255, 0, 0));
  topR(np, np.Color(255, 0, 0));
  np.show();
}

//=================================================================================================//
// helper functions to display digits
//=================================================================================================//

static void bottom(Adafruit_NeoPixel np, uint32_t c) {
  for(uint16_t i=4; i<8; i++) {
    np.setPixelColor(i, c);
  }
}
static void top(Adafruit_NeoPixel np, uint32_t c) {
  for(uint16_t i=20; i<24; i++) {
    np.setPixelColor(i, c);
  }
}
static void bottomL(Adafruit_NeoPixel np, uint32_t c) {
  for(uint16_t i=0; i<4; i++) {
    np.setPixelColor(i, c);
  }
}
static void bottomR(Adafruit_NeoPixel np, uint32_t c) {
  for(uint16_t i=8; i<12; i++) {
    np.setPixelColor(i, c);
  }
}
static void middle(Adafruit_NeoPixel np, uint32_t c) {
  for(uint16_t i=12; i<16; i++) {
    np.setPixelColor(i, c);
  }
}
static void topL(Adafruit_NeoPixel np, uint32_t c) {
  for(uint16_t i=16; i<20; i++) {
    np.setPixelColor(i, c);
  }
}
static void topR(Adafruit_NeoPixel np, uint32_t c) {
  for(uint16_t i=24; i<28; i++) {
    np.setPixelColor(i, c);
  }
}
