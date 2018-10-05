/*
 * VU: Palette blending demo
 */

CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;

void vu10() {

  EVERY_N_SECONDS(5) { // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8(); // You can use this as a baseline colour if you want similar hues in the next line.

    for (int i = 0; i < 16; i++) {
      targetPalette[i] = CHSV(random8(), 255, 255);
    }
  }

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges); // AWESOME palette blending capability.
  }

  EVERY_N_MILLISECONDS(20) { // FastLED based non-blocking delay to update/display the sequence.
    soundtun();

    FastLED.show();
  }
}

void soundtun() {

  int sampleLeft = abs(analogRead(LEFT_IN_PIN) - 512 - DC_OFFSET);
  CRGB newcolourLeft = ColorFromPalette(currentPalette, constrain(sampleLeft, 0, 255), constrain(sampleLeft, 0, 255), LINEARBLEND);
  nblend(ledsLeft[0], newcolourLeft, 128);
  for (int i = N_PIXELS - 1; i > 0; i--) {
    ledsLeft[i] = ledsLeft[i - 1];
  }

  #ifdef TWO_STRIPS
    int sampleRight = abs(analogRead(RIGHT_IN_PIN) - 512 - DC_OFFSET);
    CRGB newcolourRight = ColorFromPalette(currentPalette, constrain(sampleRight, 0, 255), constrain(sampleRight, 0, 255), LINEARBLEND);
    nblend(ledsRight[0], newcolourRight, 128);
    for (int i = 0; i < N_PIXELS; i++) {
      ledsRight[i] = ledsRight[i + 1];
    }
  #endif

}
