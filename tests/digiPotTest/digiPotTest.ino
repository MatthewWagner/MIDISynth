// This program is a test for controlling a digital potentiometer such as the MCP415X.
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

#include <SPI.h>

void setup() {
SPI.begin();
Serial.begin(9600);
}

void loop() {
    SPI.transfer(0);
    int potValue = map(analogRead(24), 0, 1023, 0, 257);
    SPI.transfer(potValue);
    Serial.println(potValue);
    delay(10);
}
