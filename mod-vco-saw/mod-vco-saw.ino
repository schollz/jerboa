#include "C:\Users\Zack\Downloads\nm2\jerboa\jerboa.h"
#include  "C:\Users\Zack\Downloads\nm2\jerboa\generated-vco-table.h"

word phase;

void Setup() {}

void Loop() {
  unsigned long long int aa = 1;
  word offset = word(InA()) + word(InB()) + word(InK());
  phase += pgm_read_word(VCO_TABLE+offset);
  
  OutF(phase>>8);

  if (phase & 0x8000) {
    LedOn();
  } else {
    LedOff();
  }
}
