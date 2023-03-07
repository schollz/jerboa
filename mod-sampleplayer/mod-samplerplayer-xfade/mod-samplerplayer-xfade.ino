// Sampler Player
// InA() -> selects sample
// InB() -> gates
// InK() -> also selects sample

#include "C:\Users\Zack\Downloads\nm2\jerboa\jerboa.h"
//#include "C:\Users\Zack\Downloads\nm2\jerboa\generated-sampleplayer-table.h"
#include "C:\Users\Zack\Downloads\nm2\jerboa\generated-jesu-table.h"

int n;
int p[2] = {0, 0};
int i = 0;
bool gated = false;
bool playing = false;
byte xfade = 0;

void Setup() {
  n = sizeof(JESU_TABLE) / sizeof(byte);
}

void Loop() {
  word sample = word(InA()) + word(InB());

  
  byte gate = InB();
  if (gate > 128 && !gated) {
    gated = true;
    // reset one of the players
    i = 1 - i;
    p[i] = 0;
    playing = true;
    LedOn();
  } else if (gated < 128 && gated) {
    gated = false;
  }

  // update phase
  for (int j = 0; j < 2; j++) {
    p[j]++;
    if (p[j] >= n) {
      p[j] = 0;
      if (j == i) {
        playing = false;
        LedOff();
      }
    }
  }

  if (playing) {
    byte f[2] = {0,0};
    f[0] = pgm_read_byte(JESU_TABLE + p[0]);
    f[1] = pgm_read_byte(JESU_TABLE + p[1]);

    if (i == 0 && xfade > 0) {
      xfade--;
    } else if (i == 1 && xfade < 255) {
      xfade++;
    }
    OutF(((f[0] * (255 - xfade) * 100 / 255) +  (f[1] * xfade * 100 / 255)) / 100);

  }
}
