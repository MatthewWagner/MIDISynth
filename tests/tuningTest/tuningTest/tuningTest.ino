// This program is a test for tuning a function generator with two digital potentiometers such as the MCP415X through a multiplexer.
// Note: This includes code to make the test easily expandable to more digiPots through more multiplexers.
// The circuit should be wired as follows.

// Buttons: 
// 29 _\_ ground (digiPot1 down)
// 30 _\_ ground (digiPot1 up)
// 31 _\_ ground (digiPot2 down)
// 32 _\_ ground (digiPot2 up)

// Digital potentiometer 1: 
// 1 CS  -> C0 (MUX)
// 2 SCK -> 13 (SCK)
// 3 SDI -> 11 (MOSI)
// 4 VSS -> 3.3V
// 5 P0B -> NC
// 6 P0W -> MM Probe
// 7 P0A -> MM Probe
// 8 VDD -> ground

// Digital potentiometer 2: 
// 1 CS  -> C1 (MUX)
// 2 SCK -> 13 (SCK)
// 3 SDI -> 11 (MOSI)
// 4 VSS -> 3.3V
// 5 P0B -> NC
// 6 P0W -> MM Probe
// 7 P0A -> MM Probe
// 8 VDD -> ground

// Multiplexer:
// Pins
#define muxS0 20
#define muxS1 21
#define muxS2 22
#define muxS3 23

#define mux1En 13
#define mux2En 14
#define mux3En 15
#define mux4En 16
#define mux5En 17
#define mux6En 18
#define mux7En 19

#define muxSig 22

#include <SPI.h>

struct device {
  int mux;
  int pin;
  int value = 0;
};

device digiPot1;
device digiPot2;

void updateDigiPot(device selectedDevice);

void setup() {
SPI.begin();
Serial.begin(9600);
pinMode(INPUT_PULLUP, 29);
pinMode(INPUT_PULLUP, 30);
pinMode(INPUT_PULLUP, 31);
pinMode(INPUT_PULLUP, 32);
digiPot1.mux = 1;
digiPot1.pin = 0;

digiPot2.mux = 1;
digiPot2.pin = 1;
}

void loop() {
  int x = 0;
  int y = 0;
  while(1) {
    if(!digitalRead(29) && x >= 0) {
      x--;
    }
    if(!digitalRead(30)) {
      x++;
    }
    if(!digitalRead(31) && x >= 0) {
      y--;
    }
    if(!digitalRead(32)) {
      y++;
    }
    digiPot1.value = x;
    digiPot2.value = y;
    updateDigiPot(digiPot1);
    updateDigiPot(digiPot2);
    delay(10);  
  }
}

void updateDigiPot(device selectedDevice) {
    setMux(selectedDevice);
    SPI.transfer(0);
    SPI.transfer(selectedDevice.value);
    Serial.println(selectedDevice.value);
}

void setMux (device selectedDevice) {
  digitalWrite(mux1En, 0);
  digitalWrite(mux2En, 0);
  digitalWrite(mux3En, 0);
  digitalWrite(mux4En, 0);
  digitalWrite(mux5En, 0);
  digitalWrite(mux6En, 0);
  digitalWrite(mux7En, 0);

  int j = selectedDevice.pin;
  bool pinValue[4];
  for(int i = 0; i < 4; i++) {
    pinValue[i] = j%2;
    j = j/2;
  }
  
  digitalWrite(muxS0, pinValue[0]);
  digitalWrite(muxS1, pinValue[1]);
  digitalWrite(muxS2, pinValue[2]);
  digitalWrite(muxS3, pinValue[3]);
  
  switch(selectedDevice.mux) {
    case 1:
      digitalWrite(mux1En, 1);
      break;
    case 2:
      digitalWrite(mux2En, 1);
      break;
    case 3:
      digitalWrite(mux3En, 1);
      break;
    case 4:
      digitalWrite(mux4En, 1);
      break;
    case 5:
      digitalWrite(mux5En, 1);
      break;
    case 6:
      digitalWrite(mux6En, 1);
      break;
    case 7:
      digitalWrite(mux7En, 1);
      break;
  }
 }
