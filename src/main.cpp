#include <Arduino.h>

//ADSR values
#define off 0
#define a 1
#define d 2
#define s 3
#define r 4

//Waveform values
#define square 1
#define triangle 2
#define saw 3
#define sine 4

//Adjustable settings
#define numVoices 4
#define numInputDevices 32
#define numOutputDevices 64
#define numSPIDevices 100

//Input devices
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

//SPI devices


//Pins
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

struct voice {
  bool isOn = 0;
  int ch = 0;
  int waveform = 0;
  int note = 0;
  double freq = 0;
  int vel = 0;
  double timeOn = 0;
  double timeReleased = 0;
  int adsrPhase = 0;
};

struct device {
  int mux;
  int pin;
  int value = 0;
};

struct midiMessage {
  int channel;
  int velocity;
  int note;
};

void resetVoice(voice selectedVoice) {
  selectedVoice.isOn = 0;
  selectedVoice.waveform = 0;
  selectedVoice.freq = 0;
  selectedVoice.vel = 0;
  selectedVoice.timeOn = 0;
  selectedVoice.timeReleased = 0;
}

void readMidi();
void readUI();
void updateVoices();
void vibrato();
void mixing();
void setOutputs();
void noteOff();
void noteOn();
voice voices[numVoices];
device inputDevices[numInputDevices];
device outputDevices[numOutputDevices];

void setup() {
//init input devices
for(int i = 0; i < numInputDevices; i++) {
  inputDevices[i].pin = i%16;
  inputDevices[i].mux = i/16;
}
for(int i = 0; i < numOutputDevices; i++) {
  outputDevices[i].pin = i%16;
  outputDevices[i].mux = i/16 + 1;
}
}

void loop() {
  readUI();
  updateVoices();
  readMidi();
  mixing();
  
}

void mixing() {
  for(int i = 0; i < numVoices; i++) {
    //if(voices[i].adsrToggle
  }
}

void readUI() { 
  for(int i = 0; i < 32; i++) {
    setMux(inputDevices[i]);
    inputDevices[i].value = analogRead(muxSig);
  }
}

void updateVoices() {
  
}

void noteOn(midiMessage currentMessage) {
  int selectedVoice = 16;
  for(int i = numVoices; i > 0; i--) {
    if(voices[i-1].ch == currentMessage.channel) {
      if(!(voices[i-1].isOn)) { //voice is off
        selectedVoice = i-1;
      } else if(voices[i-1].adsrPhase == r && selectedVoice != 16) { //voice is in release phase
        selectedVoice = i-1;
      }
    }
  }
  if(selectedVoice != 16) {
    voices[selectedVoice].isOn = true;
    voices[selectedVoice].note = currentMessage.note;
    voices[selectedVoice].vel = currentMessage.velocity;
    voices[selectedVoice].adsrPhase = a;
    voices[selectedVoice].timeOn = millis();
  }
}

void noteOff(midiMessage currentMessage) {
  for(int i = numVoices; i > 0; i--) {
    if(voices[i-1].ch == currentMessage.channel && voices[i-1].note == currentMessage.note) {
      voices[i-1].adsrPhase = r;
      voices[i-1].timeReleased = millis();
    }
  }
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
