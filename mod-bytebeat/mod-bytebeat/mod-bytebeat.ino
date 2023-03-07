#include "/home/zns/Documents/jerboa/jerboa.h"

// A -> selects bytebeat 2 AND resets bytebeats if goes high?
// B -> crossfades between bytebeat 1 and 2
// K -> selects bytebeat 1
// default state: B is grounded so K can select bytebeat
// alternative: modulate A and B to randomly select other bytebeats and
// randomly crossfade them

unsigned long long t = 0;
word beat;

void Setup() {}

void Loop() {
  // byte a = 0;
  // byte b = 0;
  // byte pot3 = InB();

  // for (int i = 0; i < 2; i++) {
  //   byte aOrB;
  //   byte u;
  //   if (i == 0) {
  //     aOrB = InK();
  //   } else {
  //     aOrB = InA();
  //   }
  //   switch (linlin(aOrB, 0, 255, 1, 7)) {
  //     case 1:
  //       u = ((t << 1) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7;  // http://canonical.org/~kragen/bytebeat/
  //       break;
  //     case 2:
  //       u = t * ((t >> 12 | t >> 7) & 63 & t >> 4);  // https://github.com/aemodular/GRAINS/blob/master/ByteBeat-Xfade/ByteBeat-Xfade.ino#L149-L154
  //       break;
  //     case 3:
  //       u = t * ((t >> 12 | t >> 8) & 63 & t >> 4);
  //       break;
  //     case 4:
  //       u = t * ((t >> 12 | t >> 8) & 61 & t >> 11);
  //       break;
  //     case 5:
  //       u = t * ((t >> 12 | t >> 8) & 59 & t >> 9);
  //       break;
  //     case 6:
  //       u = ((t & 15) * (-t & 15) ^ !(t & 16) - 1) + 32;
  //       break;
  //     case 7:
  //       u = (t % 100 >= t / 200 % 100) * 255;
  //       break;
  //     default:
  //       u = ((t << 1) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7;  // http://canonical.org/~kragen/bytebeat/
  //       break;
  //   }
  //   if (i == 0) {
  //     a = u;
  //   } else {
  //     b = u;
  //   }
  // }

  t = t + 1;

  OutF(
 t * ((t >> 12 | t >> 7) & 63 & t >> 4)
   );
  //  OutF(((a * (255 - pot3) * 100 / 255) +  (b * pot3 * 100 / 255)) / 100);
}
