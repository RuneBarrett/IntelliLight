enum State {off, connecting, normalLight, showClock, partyMode};
enum AlertState {none, door, bus, rain};

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
  switch (currentAState) {
    case rain:
      if (millis() - timer < 4000) //only run this for X seconds
        rainAlert();
      break;
    default:
      //pulseRGB();
      break;
  }
}
