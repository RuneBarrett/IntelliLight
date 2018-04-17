/*
   Defines our basic state machines. One for the "main" light, one for the "weather" and one for the "alert" states.
*/


void stateLoop() {
  switch (currentState) {
    case connecting:
      loadingLight();
      break;
    case normalLight:
      setMainColor();
      break;
    case partyMode:
      pulseRGB();
      break;
    default:
      //pulseRGB();
      break;
  }
}

void weatherLoop() {
  if (millis() - lightTimer < SHOW_WEATHER_TIME * 1000) { //only run this for SHOW_WEATHER_TIME seconds
    switch (currentWState) {
      case rain:
        rainPattern();
        break;
      case cloudy:
        cloudPattern();
        break;
      case clearW:
        clearPattern();
        break;
      default:
        //pulseRGB();
        break;
    }
    //Show temperature
    temperaturePattern();
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
