void webserviceLoop(){}

void sendRequest(String address, String msg) {
  HTTPClient http;
  address = "https://api.darksky.net/forecast/66c827c05b649327decb3563a07402f8/51.5033640,-0.1276250?exclude=minutely,hourly,daily,alerts,flags";
  http.begin(address, "C0:CD:F8:5C:DB:F3:52:0D:AF:79:75:EA:61:2A:95:8A:49:07:DC:33"); //darksky's https fingerprint (needed because of https and the used http library)
  int httpCode = http.GET();
  response = http.getString(); //get response object
  Serial.println(httpCode);
  Serial.println(response);
  http.end();
}

void parseJson() { //currently hardcoded for darksky
  StaticJsonBuffer<1000> jsonBuffer;
  char output[response.length()+1];//buffer for converting c_str to char[] (needed by parser library)
  response.toCharArray(output, response.length()+1);//convert
  JsonObject& root = jsonBuffer.parseObject(output);

  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  
  JsonObject& currently = root["currently"];
  float currently_temperature = currently["temperature"];

  Serial.println(currently_temperature);
}

