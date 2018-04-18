/*
   Holds the actual light patterns used for different states.
*/
//A "loading screen"
void loadingLight() {
  allLanesRGB(CRGB( 0, counters[4].getVal(), 0),
              CRGB( counters[4].getVal(), counters[7].getVal(), 0),
              CRGB( 0, counters[3].getVal(), 0),
              CRGB( 0, 0, counters[9].getVal()));
}

void rainPattern() {
  for (int i = 0; i <= 16; i += 4) {
    leds[i] = CRGB( 0, 0, counters[7].getVal());
    leds[i + 2] = CRGB( 0, 0, counters[9].getVal());
  }
}

void cloudPattern() {
  for (int i = 0; i <= 16; i += 4) {
    leds[i + 1] = CRGB( 0, counters[5].getVal(), counters[6].getVal());
    leds[i + 2] = CRGB( 0, counters[7].getVal(), counters[8].getVal() );
  }
}

void clearPattern() {
  for (int i = 0; i <= 16; i += 4) {
    leds[i + 1] = CRGB( counters[4].getVal(), counters[5].getVal(), 0);
    leds[i + 2] = CRGB( counters[6].getVal(), counters[7].getVal(), 0 );
  }
}

void temperaturePattern() {
  if (temperature > TEMP_WARM) temperature = TEMP_WARM;
  if (temperature < TEMP_COLD) temperature = TEMP_COLD;
  for (int i = 20; i <= 32; i += 3) {
    leds[i + 1] = CRGB(map(temperature, TEMP_COLD, TEMP_WARM, 0, 120),
                       10,
                       255 - map(temperature, TEMP_COLD, TEMP_WARM, 0, 120));
  //leds[i + 2] = CRGB(255, 0, 0);
  //if(random(10) == 1)
  //  leds[random(20, NUM_LEDS)] = CRGB(255,255,255);
   
  }
}
