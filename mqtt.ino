//publish:
//Serial.println(client.publish("cmnd/sonoff_ceiling/power", "OFF"));

void connect_mqtt() {
  client.setServer(mqtt_server, 1883);
  client.connect("FunkyLamp", mqtt_user, mqtt_password);
  client.setCallback(callback);
  client.subscribe("lightMode");
  client.subscribe("lightAlert");
  client.subscribe("dimming");
  client.subscribe("colorChange");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String strPay = "";
  String strTop = topic;
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    strPay += (char)payload[i];
  }
  Serial.println(strPay);
  if (strTop == "lightMode") {
    switchSimple = !switchSimple;
  }
  
  if (strTop == "lightAlert") {}

  if (strTop == "dimming") {
    if (strPay == "UP")
      dimMainHSV(20);
    else
      dimMainHSV(-20);
  }

  if (strTop == "colorChange") {}
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("FunkyLamp", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("lightMode");
      client.subscribe("lightAlert");
      client.subscribe("dimming");
      client.subscribe("colorChange");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
