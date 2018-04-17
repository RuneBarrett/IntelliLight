/*
 * Holds the actual light patterns used for different states.
 */
//A "loading screen"
void loadingLight() {
  allLanesRGB(CRGB( 0, counters[4].getVal(), 0),
              CRGB( counters[4].getVal(), counters[7].getVal(), 0),
              CRGB( 0, counters[3].getVal(), 0),
              CRGB( 0, 0, counters[9].getVal()));
}

void rainAlert() {
  for (int i = 0; i <= 16; i += 4) {
    leds[i] = CRGB( 0, 0, counters[7].getVal());
    leds[i + 2] = CRGB( 0, 0, counters[9].getVal());
  }
}
void cloudAlert() {
  for (int i = 0; i <= 16; i += 4) {
    leds[i + 1] = CRGB( 0, counters[5].getVal(), counters[6].getVal());
    leds[i + 2] = CRGB( 0, counters[7].getVal(), counters[8].getVal() );
  }
}
