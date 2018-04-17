/*
 * Defines our basic state machines. One for the "main" light and one for the "alert" state.
 */
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
      if (millis() - lightTimer < ALERT_TIME * 1000) //only run this for ALERT_TIME seconds
        rainAlert();
      break;
    case cloudy:
      if (millis() - lightTimer < ALERT_TIME * 1000) 
        cloudAlert();
      break;
    default:
      //pulseRGB();
      break;
  }

  //reset/rerun light timer after X minutes
  if (millis() - lightTimer > LIGHT_INTERVAL * 1000)
    lightTimer = millis();
}
