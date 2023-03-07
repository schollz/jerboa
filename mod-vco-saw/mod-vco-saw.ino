#include "/home/zns/Arduino/jerboa/jerboa.h"
#include "/home/zns/Arduino/jerboa/generated-vco-table.h"

word phase;

void Setup() {}

void Loop() {
  unsigned long long int aa = 1;
  word offset = word(InA()) + word(InB()) + word(InK());
  phase += pgm_read_word(VCO_TABLE+1);
  
  OutF(120);

  if (phase & 0x8000) {
    LedOn();
  } else {
    LedOff();
  }
}
