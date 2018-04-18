/*
   Different utilities used for setup and maintaining background tasks.
*/

void utilityLoops() {
  //counter loops
  for (int i = 0; i < 10; i++)
    counters[i].count();
  breatheCounter.count();
  //Serial.println(breatheCounter.getVal());
  //maintain mqtt connection
  if (!client.connected()) reconnect();

  //run mqtt loop (check for published msg etc)
  client.loop();

  //debugCounters();
}

boolean timeUpdate() {
  timeClient.update(); //Collects and updates the current time from an NTP server at set time intervals
  unixTime = timeClient.getEpochTime();
  if (unixTime.length() < 6) { //dont run the program before a correct time is returned
    Serial.println("unixTime: " + unixTime + " - waiting for correct time response");
    return false;
  }
  return true;
}

bool connect_wifi() {
  delay(2000);
  // Connect to Wi-Fi network
  Serial.print("Connecting to... ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("~");
  }
  Serial.println("Wi-Fi connected successfully");
}

bool connect_wifi_multi() {
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
}

void debugCounters() {
  for (int i = 0; i < counterAmount; i++)
    Serial.print(counters[i].getVal() + ", ");
  Serial.println();
}
bool initCounters() {
  for (int i = 0; i < counterAmount; i++) {
    counters[i] = Counter(0, i + 1, true);
  }
  breatheCounter = Counter(0, 1, true, 0, breatheAmount);
}
void testTimers() {
  for (int i = 0; i < 10; i++)
    leds[i * 3] = counters[i].getVal();
}







