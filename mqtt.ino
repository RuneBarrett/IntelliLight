/*
   Code for setting up and using MQTT.
*/

//This method is called whenever anything is published to one of the subscribed topics. The "payload" is the message/value, "length" is the length of the payload array.
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived ["); Serial.print(topic); Serial.println("] ");
  String strPay = "";
  String strTop = topic;
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    strPay += (char)payload[i];
  }

  if (strTop == "intelliLight/lightMode" && strPay == "party") {
    currentState = partyMode;
  }

  if (strTop == "intelliLight/lightMode" && strPay == "normal") {
    currentState = normalLight;
  }

  if (strTop == "doorAlert") {
    //sendRequest();
  }

  if (strTop == "intelliLight/dimming") {
    if (strPay == "UP")
      dimMainHSV(20);
    else
      dimMainHSV(-20);
  }

  if (strTop == "colorChange") {}
}

//publish:
//Serial.println(client.publish("cmnd/sonoff_ceiling/power", "OFF"));

void connect_mqtt() {
  Serial.print("Connecting MQTT ... succes = ");
  client.setServer(mqtt_server, 1883);
  Serial.println(client.connect("IntelliLamp", mqtt_user, mqtt_password));
  client.setCallback(callback);
  client.subscribe("intelliLight/lightMode");
  client.subscribe("intelliLight/dimming");
  //client.subscribe("colorChange");
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Retrying MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    //if (client.connect("IntelliLamp")) {
    if (client.connect("IntelliLamp", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("intelliLight/lightMode");
      client.subscribe("intelliLight/dimming");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
