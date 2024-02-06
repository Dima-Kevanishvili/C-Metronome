#include <AudioToolbox/AudioToolbox.h>
#include <mach/clock_types.h>
#include <stdio.h>
#include <time.h>
#define BILLION 1000000000L

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
  struct timespec t1, t2;
  double elapsed = 0;
  double lastBeat = 0;
  double beatCount = 1;
  clock_gettime(REALTIME_CLOCK, &t1);
  while (1) {
    clock_gettime(REALTIME_CLOCK, &t2);
    elapsed =
        (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_nsec - t1.tv_nsec) / BILLION;
    if (lastBeat + BPSDivided <= elapsed) {
      if (beatCount == ceil(beatCount)) {
        printf("%.f ", beatCount);
        fflush(stdout);
      }
      AudioServicesPlaySystemSound(kSystemSoundID_UserPreferredAlert);
      beatCount += (4 / subDivision);
      lastBeat += BPSDivided;
    }
    if (elapsed >= barTime) {
      clock_gettime(REALTIME_CLOCK, &t1);
      lastBeat = 0;
      beatCount = 1;
      printf("\n");
    }
  }
  return 0;
}
