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
// 4 and 189 are similar
// 16 and 17 are similar     
// 55 and 102 are similar, 112 is somewhat similar
// 66 and 115 are similar, 115 has stars in addition
// 75 twirls
// 82 and 89 are similar     
// 85 and 87 are very close
// 89 and 94 and 98 are similar
// 110 and 151 are similar
// 121 and 122 similar
// 132 134 are similar, 134 looks better with reflections, 192 almost same
// 150 and 185 and 186 are almost the same
uint8_t bestpatterns[] = {
    // 14: circles around circles
    // 23: dragged rgb triangle: fix  to be triangle spin only, remove text and mirror
    // 26: lots of circles
    // 69: falling rain, fix: reverse up/down and remove text
    // 82: opposite rotation circles
    // 87: zoomout spread disks. fix: remove mirror
    // 103: colorspiral
    // 110: dancing cubes
    // 111: dancing disks
    // 115: two rgbspirals with stars
    // 124: exploding circles and triangles
    // 134: really nice patterns vs circles. TODO take from 46
    // 146: offset rgb disks
    // 150: fat fire. Fixme  to remove line in fire and mirror
    // 155: flying rgb triangles
    // 162: 2 crossed color waves. Fix: remove text and mirror
    // 187: big discs merging like shutter
    // 189: zoom circles. fix: remove text
    14, 23, 26, 69, 82, 87, 103, 110, 111, 115, 124, 134, 146, 150, 155, 162, 187, 189, // new patterns to add to FastLED_IR
    // 4: different from old, 189 is similar
    // 52, 60, 62 are  different demo in new tme, don't want it. 105 changed a lot, I like the old one
    4, 10, 11, 25, 52, 60, 62, 67, 70, 77, 80, 104, 105,  // good in original tmed

    3, 17, 19, 20, 45, 53, 55, 58, 59, 66, 72, 73, 75, 79, 81, 86, 88, 89, 94, 96, 98, 101, 102, 107, 108, 109, 112, 113, 114, 118, 119, 120, 121, 126, 128, 131, 139, 141, 143, 144, 145, 147, 149, 151, 158, 192,   // good but not picked for FastLED_IR

// Aurora does not work well at resolutions over 256 wide or high or more than 64K pixels.
// My RPI3 has a lower dispay and the RPI4 has a display that is too big
#if mwidth < 256
    170, 177, 180, 
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
