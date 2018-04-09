void utilityLoops() {
  //counter loops
  for (int i = 0; i < 10; i++)
    counters[i].count();

  //maintain mqtt connection
  if (!client.connected()) reconnect();

  //run mqtt loop (check for published msg etc)
  client.loop();

  //debugCounters();
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

  /*if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }*/
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
}
void testTimers() {
  for (int i = 0; i < 10; i++)
    leds[i * 3] = counters[i].getVal();
}







