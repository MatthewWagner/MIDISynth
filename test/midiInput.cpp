// This program is a test for handling a MIDI input and controlling voicecs in the synth.

// The circuit should be wired as follows.

// Optocoupler: 
/* Needs Work */
// 1 CS  -> C0 (MUX)
// 2 SCK -> 13 (SCK)
// 3 SDI -> 11 (MOSI)
// 4 VSS -> 3.3V
// 5 P0B -> NC
// 6 P0W -> MM Probe
// 7 P0A -> MM Probe
// 8 VDD -> ground

#include <Arduino.h>
#include <MIDI.h>

#define numVoices 4

//ADSR values
#define off 0
#define a 1
#define d 2
#define s 3
#define r 4

struct voice {
  bool isOn = 0;
  uint8_t ch = 0;
  uint8_t waveform = 0;
  uint8_t note = 0;
  double freq = 0;
  uint8_t vel = 0;
  double timeOn = 0;
  double timeReleased = 0;
  uint8_t adsrPhase = 0;

};

void resetVoice(voice selectedVoice) {
  selectedVoice.isOn = 0;
  selectedVoice.waveform = 0;
  selectedVoice.freq = 0;
  selectedVoice.vel = 0;
  selectedVoice.timeOn = 0;
  selectedVoice.timeReleased = 0;
}

voice voices[numVoices];

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void handleNoteOn(byte channel, byte note, byte velocity);
void handleNoteOff(byte channel, byte note, byte velocity);
void handlePitchBend(byte channel, int bend);
void handleControlChange(byte channel, byte control, byte value);

void setup() {
    Serial.begin(9600);

    MIDI.begin();

    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandlePitchBend(handlePitchBend);
    MIDI.setHandleControlChange(handleControlChange);
}

void loop() {
    MIDI.read();
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
    int invalid = numVoices + 1;
    int selectedVoice = invalid;
    for(int i = numVoices - 1; i >= 0; i--) {
        if(voices[i].ch == channel) {
            if(!(voices[i].isOn)) { // voice is off
                selectedVoice = i;
            } else if(voices[i].adsrPhase == r && selectedVoice != invalid) { // voice is in release phase, we can cut it off
                selectedVoice = i;
            }
        }
    }
    if(selectedVoice != invalid) {
        voices[selectedVoice].isOn = true;
        voices[selectedVoice].note = note;
        voices[selectedVoice].vel = velocity;
        voices[selectedVoice].adsrPhase = a;
        voices[selectedVoice].timeOn = millis();
    }
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
    for(int i = numVoices - 1; i >= 0; i--) {
        if(voices[i].ch == channel && voices[i].note == note) {
            voices[i].adsrPhase = r;
            voices[i].vel = velocity;
            voices[i].timeReleased = millis();
        }
    }
}

void handlePitchBend(byte channel, int bend)
{

}

void handleControlChange(byte channel, byte control, byte value)
{

}


