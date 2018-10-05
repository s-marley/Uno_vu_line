/*
 * Standby: A colored dot sweeping back and forth, with fading trails
 */

void sinelon() {

  const uint8_t THIS_BEAT = 23;
  const uint8_t THAT_BEAT = 28;
  const uint8_t THIS_FADE = 2; // How quickly does it fade? Lower = slower fade rate.

  fadeToBlackBy(ledsLeft, N_PIXELS, THIS_FADE);
  int pos1 = beatsin16(THIS_BEAT, 0, N_PIXELS - 1);
  int pos2 = beatsin16(THAT_BEAT, 0, N_PIXELS - 1);
  ledsLeft[(pos1 + pos2) / 2] += CHSV(myhue, 255, 255);
  EVERY_N_MILLISECONDS(10) {
    myhue++;
  }
  
  #ifdef TWO_STRIPS
  // Copy left LED array into right LED array
  for (uint8_t i = 0; i < N_PIXELS; i++) {
    ledsRight[i] = ledsLeft[i];
  }
  #endif
  
  FastLED.show();
}
