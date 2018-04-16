enum State {off, connecting, normalLight, showClock, partyMode};
enum AlertState {none, door, cloudy, rain};

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
      if (millis() - lightTimer < 8000) //only run this for X seconds
        rainAlert();
      break;
    case cloudy:
      if (millis() - lightTimer < 8000) //only run this for X seconds
        cloudAlert();
      break;
    default:
      //pulseRGB();
      break;
  }

  //reset/rerun light timer after X minutes
  if (millis() - lightTimer > LIGHT_INTERVAL)
    lightTimer = millis();
}
