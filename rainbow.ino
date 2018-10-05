/*
 * Standby: Rainbow cycling around in clockwise direction
 */

void rainbow(uint8_t rate) {
  static uint8_t leftHue = 0;
  static uint8_t rightHue = 0;
  
  fill_rainbow(ledsLeft, N_PIXELS, leftHue, 7);
  #ifdef TWO_STRIPS
    fill_rainbow(ledsRight, N_PIXELS, rightHue, 7);
  #endif
  
  EVERY_N_MILLISECONDS(20) {
    leftHue = (leftHue + rate) % 255;
    rightHue = (rightHue - rate) % 255;
  }
   
  FastLED.show();
}
