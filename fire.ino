/*
 * Standby: Looks like fire! Both channels are seperate and random
 */

void fire() {
  const uint8_t COOLING = 55;
  const uint8_t SPARKING = 50;
  
  // Array of temperature readings at each simulation cell
  static byte heatLeft[N_PIXELS];
  static byte heatRight[N_PIXELS];

  // Step 1.  Cool down every cell a little
  for (int i = 0; i < N_PIXELS; i++) {
    heatLeft[i] = qsub8(heatLeft[i], random8(0, ((COOLING * 10) / N_PIXELS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int k = N_PIXELS - 1; k >= 2; k--) {
    heatLeft[k] = (heatLeft[k - 1] + heatLeft[k - 2] + heatLeft[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if (random8() < SPARKING) {
    int y = random8(7);
    heatLeft[y] = qadd8(heatLeft[y], random8(160, 255));
  }

  // Step 4.  Map from heat cells to LED colors
  for (int j = 0; j < N_PIXELS; j++) {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with color palettes.
    byte colorindex = scale8(heatLeft[j], 240);
    CRGB color = ColorFromPalette(CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White), colorindex);
    int pixelnumber = j;
    ledsLeft[pixelnumber] = color;
  }

  #ifdef TWO_STRIPS
    // Now do it all again for the right channel
    // Step 1.  Cool down every cell a little
    for (int i = 0; i < N_PIXELS; i++) {
      heatRight[i] = qsub8(heatRight[i], random8(0, ((COOLING * 10) / N_PIXELS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = N_PIXELS - 1; k >= 2; k--) {
      heatRight[k] = (heatRight[k - 1] + heatRight[k - 2] + heatRight[k - 2]) / 3;
    }
  
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < SPARKING) {
      int y = random8(7);
      heatRight[y] = qadd8(heatRight[y], random8(160, 255));
    }
  
    // Step 4.  Map from heat cells to LED colors
    for (int j = 0; j < N_PIXELS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8(heatRight[j], 240);
      CRGB color = ColorFromPalette(CRGBPalette16(CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White), colorindex);
      int pixelnumber = j;
      ledsRight[pixelnumber] = color;
    }
  #endif
  
  FastLED.show();
}
