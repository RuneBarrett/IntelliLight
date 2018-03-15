void setMainColor() {
  CHSV lessBright = mainColor;
  lessBright.val = lessBright.val - lessBright.val * 0.4;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i < 20)
      leds[i] = lessBright;
    else
      leds[i] = mainColor;
  }
}

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

void testTimers() {
  for (int i = 0; i<10;i++) {
    leds[i] = CRGB(0,counters[i].getVal(),0);
  }

}

