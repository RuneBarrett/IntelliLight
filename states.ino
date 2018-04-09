enum State {off, connecting, normalLight, showClock, partyMode};
enum AlertState {none,door, bus, weather};

State currentState = normalLight;
AlertState currentAState = none;

void stateLoop() {
  switch (currentState) {
    case connecting:
      loadingLight();
      break;
    case normalLight:
      setMainColor();
      break;
    default:
      //pulseRGB();
      break;
  }
}

void alertLoop() {
  switch (currentState) {
    case connecting:
      loadingLight();
      break;
    case normalLight:
      setMainColor();
      break;
    default:
      pulseRGB();
      break;
  }
}
