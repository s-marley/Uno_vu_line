/*
 * VU: Ripple (mono) with or without background
 */
 
int rippleStep = -1;
const float RIPPLE_FADE_RATE = 0.80;
int peakspersec = 0;
int peakcount = 0;
unsigned int sampleavg;
uint8_t rippleHue = 0;
uint8_t bgcol = 0;

void vu7(boolean show_background) {
  
  EVERY_N_MILLISECONDS(1000) {
    peakspersec = peakcount; // Count the peaks per second. This value will become the foreground rippleHue.
    peakcount = 0; // Reset the counter every second.
  }

  soundmems();

  EVERY_N_MILLISECONDS(20) {
    ripple3(show_background);
  }

  #ifdef TWO_STRIPS
    // Copy left LED array into right LED array
    for (uint8_t i = 0; i < N_PIXELS; i++) {
      ledsRight[i] = ledsLeft[i];
    }
  #endif
  
  FastLED.show();
}

void soundmems() { // Rolling average counter - means we don't have to go through an array each time.
  
  static int samplecount;
  static unsigned long samplesum;
  static unsigned long oldtime;
  unsigned long newtime = millis();
  unsigned int sample = abs(analogRead(LEFT_IN_PIN) - 512);
  
  samplesum = samplesum + sample - volLeft[samplecount]; // Add the new sample and remove the oldest sample in the array 
  sampleavg = samplesum / SAMPLES; // Get an average
  volLeft[samplecount] = sample; // Update oldest sample in the array with new sample
  samplecount = (samplecount + 1) % SAMPLES; // Update the counter for the array

  if ((sample > (sampleavg + 50)) && (newtime > (oldtime + 100))) { // Check for a peak, which is 50 > the average, but wait at least 100ms for another.
    rippleStep = -1;
    peakcount++;
    oldtime = newtime;
  }
}

void ripple3(bool show_background) {

  const uint8_t MAX_STEPS = 16;
  static int center = 0;
  
  if(show_background) {
    for (int i = 0; i < N_PIXELS; i++) {
      ledsLeft[i] = CHSV(bgcol, 255, sampleavg * 2); // Set the background colour.
    }
  } else {
    fadeToBlackBy(ledsLeft, N_PIXELS, 64);
  }

  switch (rippleStep) {

  case -1: // Initialize ripple variables.
    center = random(N_PIXELS);
    rippleHue = (peakspersec * 10) % 255; // More peaks/s = higher the hue colour.
    rippleStep = 0;
    bgcol = bgcol + 8;
    break;

  case 0:
    ledsLeft[center] = CHSV(rippleHue, 255, 255); // Display the first pixel of the ripple.
    rippleStep++;
    break;

  case MAX_STEPS: // At the end of the ripples.
    break;

  default: // Middle of the ripples.
    ledsLeft[(center + rippleStep + N_PIXELS) % N_PIXELS] += CHSV(rippleHue, 255, 255 / rippleStep * 2); // Simple wrap from Marc Miller.
    ledsLeft[(center - rippleStep + N_PIXELS) % N_PIXELS] += CHSV(rippleHue, 255, 255 / rippleStep * 2);
    rippleStep++; // Next step.
    break;
  }
}
