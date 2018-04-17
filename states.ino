/*
 * Defines our basic state machines. One for the "main" light, one for the "weather" and one for the "alert" states.
 */
enum State {off, connecting, normalLight, showClock, partyMode};
enum WeatherState {tbd, cloudy, rain};
enum AlertState {none, door, iss};

State currentState = normalLight;
WeatherState currentWState = tbd;
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

void weatherLoop() {
  switch (currentWState) {
    case rain:
      if (millis() - lightTimer < SHOW_WEATHER_TIME * 1000) //only run this for SHOW_WEATHER_TIME seconds
        rainPattern();
      break;
    case cloudy:
      if (millis() - lightTimer < SHOW_WEATHER_TIME * 1000) 
        cloudPattern();
      break;
    default:
      //pulseRGB();
      break;
  }

  //reset/rerun light timer after X minutes
  if (millis() - lightTimer > WEATHER_INTERVAL * 1000)
    lightTimer = millis();
}

void alertLoop() {
  switch (currentAState) {
    case door:
      break;
    case iss:
      break;
    default:
      break;
  }
}
