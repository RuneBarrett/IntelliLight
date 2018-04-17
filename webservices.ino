/*
   Manages communication with a webservice
*/

void webserviceLoop() {
  //send a webrequest at a set time interval
  if (millis() - webserviceTimer > WEB_REQ_INTERVAL * 1000)
  {
    webserviceTimer = millis();
    //Fetch the time and add FORECAST_TIME to it
    unixTime = timeClient.getEpochTime(); 
    unixTime = unixTime.toInt() + (FORECAST_TIME * 60 * 1000); //1523896372 - returns cloudy for testing
    Serial.println(unixTime);
    sendRequest();
    parseJson();
  }
}

void sendRequest() { //String address, String fingerPrint
  HTTPClient http;
  //address = "https://api.darksky.net/forecast/" + dark_key + "/" + lati + "," + longti + "?exclude=minutely,hourly,daily,alerts,flags&units=si";
  String address = "https://api.darksky.net/forecast/" + dark_key + "/" + lati + "," + longti + "," + unixTime + "?exclude=minutely,hourly,daily,flags&units=si";
  http.begin(address, "C0:CD:F8:5C:DB:F3:52:0D:AF:79:75:EA:61:2A:95:8A:49:07:DC:33"); //darksky's https fingerprint (needed because of https and the used http library)
  int httpCode = http.GET();
  response = http.getString(); //get response object
  Serial.println(httpCode);
  Serial.println(response);
  Serial.println(unixTime);
  http.end();
}

void parseJson() {
  DynamicJsonBuffer jsonBuffer;
  char output[response.length() + 1]; //buffer for converting c_str to char[] (needed by parser library)
  response.toCharArray(output, response.length() + 1); //convert
  JsonObject& root = jsonBuffer.parseObject(output);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  //Pick the needed values and call the weather state selector
  JsonObject& currently = root["currently"];
  determineWeatherState(currently["summary"]);
}

void determineWeatherState(String summary) {
  Serial.println(summary);
  if (summary.indexOf("Rain") > 0) {
    currentWState = rain; Serial.println("rainy");
  }
  if (summary.indexOf("Cloudy") > 0) {
    currentWState = cloudy; Serial.println("cloudy");
  }
}

