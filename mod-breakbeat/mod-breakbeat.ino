// Sampler Player
// InA() -> selects sample
// InB() -> gates
// InK() -> also selects sample

// make breakbeat

#include "/home/zns/Arduino/jerboa/jerboa.h"
#include "/home/zns/Arduino/jerboa/random.h"
#include "/home/zns/Arduino/jerboa/generated-breakbeat-table.h"


int phase_ar = 0;  // audio-rate index
word phase_sample = 0;
byte volume = 255;
byte select_sample = 0;
byte select_sample_start = 0;
byte select_sample_end = NUM_SAMPLES-1;
byte stretch = 0;
byte direction = 1;  // 0 = reverse, 1 = forward
byte retrig = 4;
void Setup() {
  RandomSetup();
}

void Loop() {

  int z = ((int)pgm_read_byte(SAMPLE_TABLE + phase_sample)) * volume;
  OutF(z >> 8);

  phase_ar++;
  if (phase_ar % (3 + stretch) == 0) {
    phase_sample += (direction * 2 - 1);
    if (phase_sample > pos[NUM_SAMPLES]) {
      phase_sample = 0;
    } else if (phase_sample < 0) {
      phase_sample = pos[NUM_SAMPLES];
    }

    if (phase_sample % retrigs[retrig] == 0) {
      byte random_retrig = RandomByte();
      byte random_jump = RandomByte();
      if (RandomByte() < 60) {
        direction = 0;
      } else {
        direction = 1;
      }
      if (random_retrig < 30) {
        retrig = 6;
      } else if (random_retrig < 60) {
        retrig = 5;
      } else if (random_retrig < 90) {
        retrig = 3;
      } else if (random_retrig < 120) {
        retrig = 2;
      } else {
        retrig = 4;
      }
      if (direction == 1) select_sample++;
      if (direction == 0) {
        if (select_sample == 0) {
          select_sample = select_sample_end;
        } else {
          select_sample--;
        }
      }
      if (select_sample < select_sample_start) select_sample = select_sample_end;
      if (select_sample > select_sample_end) select_sample = select_sample_start;
      if (random_jump<60) {
        select_sample = linlin(random_jump,0,60,0,NUM_SAMPLES);
      }
      phase_sample = pos[select_sample];
    }
  }
}
