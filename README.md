# ScorePort

### Bluetooth controlled electronic scoreboard ⚽️ 🏀 🏈 ⚾️ 🏐 🏉 

A fully inflatable electronic scorekeeping system that compresses for easy storage and portable transportation.  Designed for use by intramural sports organizations and recreational sports leagues. LED displays utilize addressable LED strips assembled into 7 segment digits that are large enough to be visible from far ends of the playing court or field.  Hardware components are safely stored in a weatherproof 3D printed box allowing for access to manually turn on and off the fans and displays.  A mobile app connects to the scoreboard via a Bluetooth connection to control the time, score, shots (not built on physical prototype), and period/quarter without the need for wifi connection.

https://user-images.githubusercontent.com/77314661/164132701-eeffb46b-2096-49fd-b83a-6645149ceda1.mp4


## Features
- Set your prefered game time and default period lengths
- Customizable time settings to support a variety of sports like soccer, basketball or spikeball
- Large LED number segments for visibility on playing field or court
- Fully controllable over bluetooth on user-friendly mobile app
- Built-in goal button to flash 'GOAL' on randomized color scheme

## Hardware

### Components

- Arduino Uno (or equivalent board with built in bluetooth)
- 1x HC-06 Bluetooth Module
- 4x Adafruit 60 WS2812 Neopixel Addressable LEDs strips
- 2x Circulating Fans
- 3x quad AA battery holders
- 12x AA batteries
- 4x power switch buttons

### Schematic

![image](https://user-images.githubusercontent.com/77314661/164131380-079c965e-478b-4c2f-b70c-5bc9246357b1.png)

The Arduino and NeoPixel LED strips circuit for score/shots and clock were modelled on two separate TinkerCAD sketches (no virtual bluetooth module testing available, bluetooth connection was tested on the physical device) to test the firemware code, pin connections, addressable library, and Serial communication:

- [Clock](https://www.tinkercad.com/login?next=%2Fthings%2FipT19Fd9uXQ-fabulous-luulia-amur%2Feditel%3Fsharecode%3DmgtLCh8mOluWIWKFgePiFf8DEEMq6n7NJTlxXU7f0uQ)
- [Score / Shots](https://www.tinkercad.com/things/h8cbnCAmsZ4-1score-segment-leds/editel?sharecode=FjUpfV3TMvTk0h-rpqfup-ZYqf5LUnMXKbBtl5f3qfk)


## Firmware

Written in Arduino C for the AVR family of microcontrollers, and using the Arduino framework. Developed using Visual Studio Code and TinkerCAD for testing non-physical device. 

### Dependencies
- [adafruit/Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) 1.7.0
- [bblanchon/ArduinoJson](https://github.com/bblanchon/ArduinoJson) 6.17.2


## Software - Android App
