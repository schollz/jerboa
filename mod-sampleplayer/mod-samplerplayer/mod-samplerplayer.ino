// Sampler Player
// InA() -> selects sample
// InB() -> gates
// InK() -> also selects sample

#include "C:\Users\Zack\Downloads\nm2\jerboa\jerboa.h"
//#include "C:\Users\Zack\Downloads\nm2\jerboa\generated-sampleplayer-table.h"
#include "C:\Users\Zack\Downloads\nm2\jerboa\generated-jesu-table.h"

int p = 0;
bool gated;
bool playing;

void Setup() {}

void Loop() {
  byte sample = linlin(word(InA()) + word(InK()), 0, 510, 0, NUM_SAMPLES);
  byte gate = InB();
  
  if (gate > 128 && !gated) {
    p = pos[sample];
    gated = true;
    playing = true;
    LedOn();
  } else if (gated < 128 && gated) gated = false;

  // update phase
  if (playing) {
    p++;
    if (p < pos[sample + 1]) {
      OutF(pgm_read_byte(JESU_TABLE + p));
    } else {
      playing = false;
      LedOff();
    }
  }
}
