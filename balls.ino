/*
 * Standby: Three balls bouncing under gravity
 */

void balls() {

  const float H0 = 0.5;
  const int NUM_BALLS = 3;
  static float h[NUM_BALLS]; // An array of heights
  static float vImpact0 = sqrt(-2 * -9.81 * H0); // Impact velocity of the ball when it hits the ground if "dropped" from the top of the strip
  static float vImpact[NUM_BALLS]; // As time goes on the impact velocity will change, so make an array to store those values
  static float tCycle[NUM_BALLS]; // The time since the last time the ball struck the ground
  static int pos[NUM_BALLS]; // The integer position of the dot on the strip (LED index)
  static long tLast[NUM_BALLS]; // The clock time of the last ground strike
  static float COR[NUM_BALLS]; // Coefficient of Restitution (bounce damping)
  static bool fireFirstRun = true;

  if (fireFirstRun) {
    for (int i = 0; i < NUM_BALLS; i++) { // Initialize variables
      tLast[i] = millis();
      h[i] = H0;
      pos[i] = 0; // Balls start on the ground
      vImpact[i] = vImpact0; // And "pop" up at vImpact0
      tCycle[i] = 0;
      COR[i] = 0.90 - float(i) / pow(NUM_BALLS, 2);
    }
    fireFirstRun = false;
  }

  for (int i = 0; i < NUM_BALLS; i++) {
    tCycle[i] = millis() - tLast[i]; // Calculate the time since the last time the ball was on the ground

    // A little kinematics equation calculates positon as a function of time, acceleration (gravity) and intial velocity
    h[i] = 0.5 * -9.81 * pow(tCycle[i] / 1000, 2.0) + vImpact[i] * tCycle[i] / 1000;

    if (h[i] < 0) {
      h[i] = 0; // If the ball crossed the threshold of the "ground," put it back on the ground
      vImpact[i] = COR[i] * vImpact[i]; // and recalculate its new upward velocity as it's old velocity * COR
      tLast[i] = millis();

      if (vImpact[i] < 0.01) vImpact[i] = vImpact0; // If the ball is barely moving, "pop" it back up at vImpact0
    }
    pos[i] = round(h[i] * (N_PIXELS - 1) / H0); // Map "h" to a "pos" integer index position on the LED strip
  }

  //Choose color of LEDs, then the "pos" LED on
  for (int i = 0; i < NUM_BALLS; i++) ledsLeft[pos[i]] = CHSV(uint8_t(i * 40), 255, 255);

  // Copy left LED array into right LED array
  for (uint8_t i = 0; i < N_PIXELS; i++) {
    ledsRight[i] = ledsLeft[i];
  }
  
  FastLED.show();
  
  //Then off for the next loop around
  for (int i = 0; i < NUM_BALLS; i++) {
    ledsLeft[pos[i]] = CRGB::Black;
    ledsRight[pos[i]] = CRGB::Black;
  }
}
