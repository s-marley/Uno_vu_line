/*
 * VU: Rainbow from bottom or middle with hue cycling
 */

void vu6(bool is_centered, uint8_t channel) {

  const uint8_t SPEED = 10;
  static uint8_t hueOffset = 30;

  CRGB* leds;
  uint8_t i = 0;
  uint8_t *peak;      // Pointer variable declaration
  uint16_t height = auxReading(channel);

  if(channel == 0) {
    leds = ledsLeft;    // Store address of peakLeft in peak, then use *peak to
    peak = &peakLeft;   // access the value of that address
  }
  else {
      leds = ledsRight;
      peak = &peakRight;
  }

  if(height > *peak)
    *peak = height; // Keep 'peak' dot at top
  
  EVERY_N_MILLISECONDS(SPEED) {hueOffset++;}

  if(is_centered) {
    // Color pixels based on rainbow gradient
    for (uint8_t i = 0; i < N_PIXELS_HALF; i++) {
      if (i >= height) {
        leds[N_PIXELS_HALF - i - 1] = CRGB::Black;
        leds[N_PIXELS_HALF + i] = CRGB::Black;
      } else {
        leds[N_PIXELS_HALF - i - 1] = CHSV(hueOffset + (10 * i),255,255);
        leds[N_PIXELS_HALF + i] = CHSV(hueOffset + (10 * i),255,255);
      }
    }

    // Draw peak dot  
    if (*peak > 0 && *peak <= N_PIXELS_HALF - 1) {
      leds[N_PIXELS_HALF - *peak - 1] = CHSV(hueOffset,255,255);
      leds[N_PIXELS_HALF + *peak] = CHSV(hueOffset,255,255);
    }
  }
  
  else {
    // Color pixels based on rainbow gradient
    for (uint8_t i = 0; i < N_PIXELS; i++) {
      if (i >= height) {
        leds[i] = CRGB::Black;
      } else {
        leds[i] = CHSV(hueOffset + (10 * i),255,255);
      }
    }
    // Draw peak dot  
    if (*peak > 0 && *peak <= N_PIXELS - 1)
      leds[*peak] = CHSV(hueOffset, 255, 255);
  
  }
  dropPeak(channel);

  averageReadings(channel);

  FastLED.show();
}
