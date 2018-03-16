enum State {normalLight, showClock};
State currentState = normalLight;
void stateLoop() {
  switch (currentState) {
    case normalLight:
      pulseRGB();
  }
}
