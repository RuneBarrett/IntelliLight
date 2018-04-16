void webserviceLoop() {
  //send a webrequest at a set time interval
  if (millis() - webserviceTimer > WEB_REQ_INTERVAL)
  {
    webserviceTimer = millis();
    sendRequest("", "", "");
  }
}

void sendRequest(String address, String msg, String fingerPrint) {
  HTTPClient http;
  
  address = "https://api.darksky.net/forecast/" + dark_key + "/" + lati + "," + longti + "?exclude=minutely,hourly,daily,alerts,flags&units=si";
  address = "https://api.darksky.net/forecast/" + dark_key + "/" + lati + "," + longti + "," + formatedTime + "?exclude=minutely,hourly,daily,flags&units=si";
  http.begin(address, "C0:CD:F8:5C:DB:F3:52:0D:AF:79:75:EA:61:2A:95:8A:49:07:DC:33"); //darksky's https fingerprint (needed because of https and the used http library)
  //address = "https://api.darksky.net/forecast/" + dark_key + "/" + lati + "," + longti + "," + formatedTime + "?exclude=minutely,hourly,daily,flags&units=si";
  int httpCode = http.GET();
  response = http.getString(); //get response object
  Serial.println(httpCode);
  Serial.println(response);
  Serial.println(formatedTime);
  http.end();
  parseJson();
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

  JsonObject& currently = root["currently"];
  determineAlertState(currently["summary"]);
  //float currently_temperature = currently["temperature"];
  //const char* currently_summary = currently["summary"];

  //if (strstr(currently_summary, "Cloudy"))
  //  currentAState = rain;
}

void determineAlertState(String summary) {
  Serial.println(summary);

  if (summary.indexOf("Rain") > 0) {
    currentAState = rain; Serial.println("rainy");
  }
  if (summary.indexOf("Cloudy") > 0) {
    currentAState = cloudy; Serial.println("cloudy");
  }
}

