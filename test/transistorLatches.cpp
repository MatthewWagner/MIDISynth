// This program is a test for controlling transistors through latches and multiplexers.
// The circuit should be wired as follows.

// Analog potentiometer: 
// left -> 5V
// wiper -> pin 24 (A10)
// right -> ground

// Digital potentiometer: 
// 1 CS  -> ground
// 2 SCK -> 13 (SCK)
// 3 SDI -> 11 (MOSI)
// 4 VSS -> 3.3V
// 5 P0B -> NC
// 6 P0W -> MM Probe
// 7 P0A -> MM Probe
// 8 VDD -> ground

#include <Arduino.h>

void setup() {
Serial.begin(9600);
}

void loop() {
    
    Serial.println(potValue);
    delay(10);
}
