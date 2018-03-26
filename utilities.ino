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







