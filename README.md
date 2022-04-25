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
- [PROGMEM](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)

## Software

### Bluetooth Connection

Bluetooth connection is established by a simple client-server model, where the Android app (client) initiates a communication session with the ScorePort (server). When a device is found, the Android code calls a new thread to create a Bluetooth connection with the selected device.

### Android App

Developed in Android Studio and written in the Kotlin programming language, with extensive markup language (XML) for the user interface. The app includes user functionality for changing score and period; starting and stopping the clock; resetting the clock to user inputted time with count up or countdown mode; setting custom period time for different sports; and displaying custom messages when the clock is not running.

The user interface was mocked up in [Figma](https://www.figma.com/file/UGBB1Kjmnd156oiMjIX9bv/ScorePort-App-UI?node-id=0%3A1) before developement and these designs were referenced when for the final layouts shown below.

![image](https://user-images.githubusercontent.com/77314661/165063783-3c49c2be-0373-4f65-8c33-8a2b45ccfc6b.png) 	 	 
![image](https://user-images.githubusercontent.com/77314661/165063400-9f81dc5b-006e-497b-91ba-6f706facfc0a.png)
![image](https://user-images.githubusercontent.com/77314661/165063423-3e2ca544-b6ad-454c-84f6-6a8a20bea0c2.png)

![image](https://user-images.githubusercontent.com/77314661/165063521-ac4b7017-4e05-4127-b498-ceb87e9bf9c2.png)
![image](https://user-images.githubusercontent.com/77314661/165063542-7791f9a0-577c-4931-bed1-5449059bf0cf.png)
![image](https://user-images.githubusercontent.com/77314661/165063759-a9dd0232-ca48-4c56-adaa-1b0e0852e46d.png)

 	 	 
### Dependencies
- [Android Bluetooth](https://developer.android.com/guide/topics/connectivity/bluetooth) 	 	 
- [Droiduino](https://developer.android.com/guide/topics/connectivity/bluetooth)  	
