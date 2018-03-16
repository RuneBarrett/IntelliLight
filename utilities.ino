bool connect_wifi() {
  delay(5000);
  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to...");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");
}

void debugCounters() {
  for (int i = 0; i < 10; i++) {
    Serial.print(counters[i].getVal()+ ", ");
  }
  Serial.println();
}
/*bool initCounters() {
  for (int i = 0; i < counter1.length; i++) {
    //counter1[i] = i*20;
  }
}*/





