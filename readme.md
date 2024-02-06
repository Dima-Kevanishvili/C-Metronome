# Simple Metronome in C

This is a test program I wrote in C as a learning experience.

I wanted to join in my interest towards music and C together and I came up with a simple Metronome

I did three versions.
1. Using `usleep()` to wait between the beats
2. Using `clock_gettime()` to continously keep track of time, single threaded
3. Using `clock_gettime()` to continously keep track of time, multi threaded

Disclaimer: I suck at C. Have very little experience. This is the first time I ever touched threads.

What I found is that it is hard to make a precise metronome, because most of the time you are dealing with little fractions of seconds and lots of floating point divisions.

Neither of the versions are too precise, they drift time to time. But from what I could hear, the `metronome_timer_mt` version is most precise.

## To build:
You need to be using MacOs, as the sound is dependant on `AudioToolbox`
```sh
gcc -o metronome metronome_timer_mt.c -framework AudioToolbox
```
Change the .c file name in the above commands to try out different versions.
