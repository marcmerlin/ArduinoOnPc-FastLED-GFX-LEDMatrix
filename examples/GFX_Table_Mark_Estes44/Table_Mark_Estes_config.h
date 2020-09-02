// --------------------------- Config Start --------------------------------
// Randomly slowdown animation. Nice in principle, but not when debugging performance
//#define RANDOMSLOWME

// Control whether pattern order is random from the start or after one pass
//#define MIXIT_AFTER_FIRST_PASS

// write the pattern number in upper left (makes more sense on higher res displays)
#define SHOW_PATTERN_NUM

// Display FPS computed by Framebuffer::GFX
#define DISPLAY_FPS

// Some pattern transitions look weird without a clear in between
#define CLEAR_BETWEEN_PATTERNS

// This allows a selection of only my favourite patterns.
// Comment this out to get all the patterns -- merlin
#define BESTPATTERNS
#ifdef BESTPATTERNS
// 82 and 89 are similar     55 and 102 are similar
uint8_t bestpatterns[] = {
    //   3, 8, 14, 17, 26, 55, 58, 59, 61, 69, 72, 82, 102, 109, 111, 132,
//   4, 10, 11, 25, 67, 70, 73, 77, 80, 86, 104, 105, 110,    // good in original tmed
//   20, 89, 94, 101, 124, 128, 134, 143, 145, 155,// good but not picked for Neomatrix

//, 3, 8, 10, 11, 14, 17, 20, 25, 26, 55, 58, 59, 61, 67, 69, 70, 72, 73, 77, 80, 82, 86, 89, 94, 101, 102, 104, 105, 109, 110, 111, 124, 128, 132, 134, 143, 145, 155, 

// Selection for picture frame:
3, 4, 7, 8, 10, 11, 12, 14, 16, 17, 18, 19, 20, 21, 25, 26, 55, 58, 59, 61, 67, 69, 70, 72, 73, 77, 79, 80, 81, 82, 84, 86, 87, 89, 90, 94, 96, 98, 99, 101, 102, 103, 104, 105, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 118, 119, 120, 121, 122, 124, 126, 128, 130, 131, 132, 134, 139, 141, 144, 147, 148, 149, 151, 155, 158, 159, 
// bad hack to avoid patterns that crash at resolutions higher than 256
// My RPI3 has a lower dispay and the RPI4 has a display that is too big
#ifndef RPI4
163, 166
#endif
};
#define numbest           sizeof(bestpatterns)
#define lastpatindex numbest
#else
#define lastpatindex mpatterns
#endif

// By default audio support is on for what's expected to be teensy.
#define TME_AUDIO
// But turn it off on ARDUINOONPC / Raspberry Pi and ESP32
#ifdef ARDUINOONPC
#undef TME_AUDIO
#endif
#ifdef ESP32
#undef TME_AUDIO
#endif

#ifdef TME_AUDIO
#include <EasyTransfer.h>// used for exchange with 2nd arduino for audio processing
#endif

#define TIMING              90//seconds per pattern
#define LATCH               23

int16_t pattern = 3;//this picks the pattern to start with...
// --------------------------- Config End ----------------------------------
