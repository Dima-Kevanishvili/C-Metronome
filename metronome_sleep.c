#include <AudioToolbox/AudioToolbox.h>
#include <stdio.h>
#include <unistd.h>
#define MILLION 1000000

int main() {
  int BPM = 180;
  double BPS = (double)60.0 / (double)BPM;
  double subDivision = 8;
  double BPSDivided = BPS * (4.0 / subDivision);
  int timeSignatureTop = 4;
  int timeSignatureBottom = 4;
  double barTime = timeSignatureTop * BPS;
  printf("BPM: %d, BPS: %f, Time Signature: %d/%d, barTime: %f\n", BPM, BPS,
         timeSignatureTop, timeSignatureBottom, barTime);
  double beatCount = 1;
  while (1) {
    usleep(BPSDivided * MILLION);
    AudioServicesPlaySystemSound(kSystemSoundID_UserPreferredAlert);
    if (beatCount == ceil(beatCount)) {
      printf("%.f ", beatCount);
      fflush(stdout);
    }
    beatCount += (4 / subDivision);
    if (floor(beatCount) > timeSignatureTop) {
      beatCount = 1;
      printf("\n");
    }
  }
  return 0;
}
