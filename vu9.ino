/*
 * VU: Ocean waves (stereo)
 */

void vu9() {
  currentPalette = OceanColors_p; // Initial palette.
  EVERY_N_SECONDS(5) { // Change the palette every 5 seconds.
    for (int i = 0; i < 16; i++) {
      targetPalette[i] = CHSV(random8(), 255, 255);
    }
  }

  EVERY_N_MILLISECONDS(100) { // Palette blending capability once they do change.
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
  }

  EVERY_N_MILLIS_I(thistimer, 20) { // For fun, let's make the animation have a variable rate.
    uint8_t timeval = beatsin8(10, 20, 50); // Use a sinewave for the line below. Could also use peak/beat detection.
    thistimer.setPeriod(timeval); // Allows you to change how often this routine runs.
    fadeToBlackBy(ledsLeft, N_PIXELS, 20); // 1 = slow, 255 = fast fade. Depending on the faderate, the LED's further away will fade out.
    #ifdef TWO_STRIPS
      fadeToBlackBy(ledsRight, N_PIXELS, 20); // 1 = slow, 255 = fast fade. Depending on the faderate, the LED's further away will fade out.
    #endif
    sndwave();
  }
  FastLED.show();

}

void sndwave() {

  int sampleLeft = abs(analogRead(LEFT_IN_PIN) - 512 - DC_OFFSET);
  int sampleRight = abs(analogRead(RIGHT_IN_PIN) - 512 - DC_OFFSET);

  ledsLeft[N_PIXELS / 2] = ColorFromPalette(currentPalette, sampleLeft, sampleLeft * 2, LINEARBLEND); // Put the sample into the center
  #ifdef TWO_STRIPS
    ledsRight[N_PIXELS / 2] = ColorFromPalette(currentPalette, sampleRight, sampleRight * 2, LINEARBLEND); // Put the sample into the center
  #endif
  
  for (int i = N_PIXELS - 1; i > N_PIXELS / 2; i--) { //move to the left      // Copy to the left, and let the fade do the rest.
    ledsLeft[i] = ledsLeft[i - 1];
    #ifdef TWO_STRIPS
      ledsRight[i] = ledsRight[i - 1];
    #endif
  }

  for (int i = 0; i < N_PIXELS / 2; i++) { // move to the right    // Copy to the right, and let the fade do the rest.
    ledsLeft[i] = ledsLeft[i + 1];
    #ifdef TWO_STRIPS
      ledsRight[i] = ledsRight[i + 1];
    #endif
  }

}
