/*
 * Holds methods that address the LED's in a general way.
 */
// -------------- STATIC LIGHT MODES -----------------
//Set the lamp to normal light
void setMainColor() {
  CHSV lessBright = mainColor;
  lessBright.val = lessBright.val - lessBright.val * 0.3;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i < 20)
      leds[i] = lessBright;
    else
      leds[i] = mainColor;
  }
}

//Used for dimming the main color variable
void dimMainHSV(int val) {
  if (val + mainColor.val > 255)
    mainColor.val = 255;
  else if (val + mainColor.val < 0)
    mainColor.val = 0;
  else
    mainColor.val += val;
}

// -------------- DYNAMIC LIGHT METHODS ----------------- (used by other light control methods)
void allLanesRGB(CRGB outer, CRGB outmid, CRGB midin, CRGB inner) {
  for (int i = 0; i < NUM_LEDS; i = i + 1)
  {
    if (i < 20)
      leds[i] = outer;
    else if (i >= 20 && i < 35)
      leds[i] = outmid;
    else if (i >= 35 && i < 44)
      leds[i] = midin;
    else
      leds[i] = inner;
  }
}


// -------------- UTILITY LIGHT CONTROL METHODS -----------------
//only address the leds if the array changed
void showLeds() {
  bool changed = false;
  for (int i = 0; i < NUM_LEDS; i++)
    if (leds[i] != last_leds[i])
      changed = true;
  if (changed) {
    FastLED.show();
    for (int i = 0; i < NUM_LEDS; i++)
      last_leds[i] = leds[i];
  }
}

void fadeToMainColor() {
  return;
  for (int i = 0; i < NUM_LEDS; i = i + 1)
  {
    
  }
}


// --- DEBUG/TEST/OTHER STUFF ---
void pulseRGB() {
  for (int i = 0; i < NUM_LEDS; i = i + 1)
  {
    if (i < 20)
      leds[i] = CRGB( counters[3].getVal(), 0 , counters[4].getVal());
    else if (i >= 20 && i < 35)
      leds[i] = CRGB( 0, counters[4].getVal(), 0);
    else if (i >= 35 && i < 44)
      leds[i] = CRGB( 0, counters[8].getVal(), 0);
    else
      leds[i] = CRGB(0, counters[i].getVal(), 0);
  }
}







