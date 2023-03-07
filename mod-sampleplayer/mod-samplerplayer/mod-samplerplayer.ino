// Sampler Player
// InA() -> selects sample
// InB() -> gates
// InK() -> also selects sample

// sox 00.wav -r 6440 -c 1 -b 8  0.wav trim 0 0.8822
// go run make-sample-table.go

#include "/home/zns/Arduino/jerboa/jerboa.h"
#include "/home/zns/Arduino/jerboa/random.h"
#include "/home/zns/Arduino/jerboa/generated-sample-table.h"

int p = 0;
int wait = 0;
int volume = 0;
int sample_end = pos[1];
bool gated;
bool playing = true;
word gate;
byte sample = 0;
byte division = 1;

void Setup() {
  RandomSetup();
}

void Loop() {
  //byte sample = linlin(word(InA()) + word(InK()), 0, 510, 0, NUM_SAMPLES - 1);
  gate = word(InB());

  if (gate < 128 && !gated) {
    gated = true;
    // sample = 0;
    // p = pos[sample];
    // playing = true;
    LedOn();
    volume = 255;
    byte b = RandomByte();
    if (b<128) {
      division = 1;
    } else if (b<188) {
      division = 2;
    } else if (b<200) {
      division = 4;
    } else if (b<255) {
      division = 8;
    }
    sample_end = pos[sample + 1] / division;
  } else if (gate > 128 && gated) {
    gated = false;
    // playing = false;
    LedOff();
  }

  // update phase
  if (playing) {
    wait++;pl
    // if (wait % (2 * 19320/255) == 0 && volume < 255) volume++;
    if (wait % 3 == 0) {
      if (gated) p++;
      else p--;
    }
    if (p < sample_end  && p > 0) {
      int z = ((int)pgm_read_byte(SAMPLE_TABLE + p)) * volume;
      OutF(z >> 8);
    } else if (p <= 0) {
      p = sample_end;
    } else {
      p = 0;
      // playing = false;
      // LedOff();
    }
  }
}
