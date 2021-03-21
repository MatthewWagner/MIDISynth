// This program is a test for reading inputs from the user control interface.

// The circuit should be wired as follows.



// Potentiometers 1-8: 
// 1  -> ground
// 2  -> C0 - C7 (MUX)
// 3  -> 3.3V


#define numInputDevices 8

// Input devices
#define rangeOffset0 0
#define rangeOffset1 1
#define rangeOffset2 2
#define rangeOffset3 3
#define freqOffset0 4
#define freqOffset1 5
#define freqOffset2 6
#define freqOffset3 7
#define waveformSelect0 8
#define waveformSelect1 9
#define waveformSelect2 10
#define waveformSelect3 11
#define volume0 12
#define volume1 13
#define volume2 14
#define volume3 15
#define adsrToggleCh1 16
#define adsrToggleCh2 17
#define chToggle0 18
#define chToggle1 19
#define chToggle2 20
#define chToggle3 21
#define poliphonyToggle0 22
#define poliphonyToggle1 23
#define poliphonyToggle2 24
#define poliphonyToggle3 25
#define vibratoFreq 26
#define vibratoDepth 27
#define attackValue 28
#define decayValue 29
#define sustainValue 30
#define releaseValue 31

// Multiplexer:
// Pins
#define muxS0 14
#define muxS1 15
#define muxS2 16
#define muxS3 17

#define mux1Sig 18
#define mux2Sig 19

#define mux3En 15
#define mux4En 16
#define mux5En 17
#define mux6En 18
#define mux7En 19

pinMode(14, OUTPUT);
pinMode(15, OUTPUT);
pinMode(16, OUTPUT);
pinMode(17, OUTPUT);

pinMode(15, OUTPUT);
pinMode(14, OUTPUT);
pinMode(14, OUTPUT);
pinMode(14, OUTPUT);
pinMode(14, OUTPUT);


#include <Arduino.h>
#include <SPI.h>

struct device {
  int mux;
  int pin;
  int value = 0;
};

void readUI();
void setMux(device selectedDevice);

device inputDevices[numInputDevices];
int selectedMuxSig = 1;

void setup() {
    Serial.begin(9600);
    for(int i = 0; i < numInputDevices; i++) {
        inputDevices[i].pin = i % 16;
        inputDevices[i].mux = (i + 16) / 16;
    }
}

void loop() {
  readUI(); 
  Serial.println("The input values are currently:");
  for(int i = 0; i < numInputDevices; i++) {
    Serial.println(inputDevices[i].value);
  }
  Serial.println();
  delay(100);
}

void setMux (device selectedDevice) {
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
      selectedMuxSig = mux1Sig;
      break;
    case 2:
      selectedMuxSig = mux2Sig;
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

void readUI() {
  for(int i = 0; i < 32; i++) {
    setMux(inputDevices[i]);
    inputDevices[i].value = analogRead(selectedMuxSig);
  }
}