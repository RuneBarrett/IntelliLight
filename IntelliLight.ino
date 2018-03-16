#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Counter.h>

//wifi
char ssid[] = "EmbedNet2"; //SSID of your Wi-Fi router
char pass[] = "betonprint"; //Password of your Wi-Fi router

//mqtt
#define mqtt_server "192.168.1.128"
#define mqtt_user ""
#define mqtt_password ""
WiFiClient espClient;
PubSubClient client(espClient);

//leds
#define DATA_PIN D2
#define NUM_LEDS 46
CRGB leds[NUM_LEDS];
CRGB last_leds[NUM_LEDS];
CHSV mainColor(180, 100, 200);
//CRGB mainColor(255, 244, 229);
bool switchSimple = true;

Counter counters[10]; //Holds counter objects that run between 0 and 255 in different speeds. The counter object is defined in the Counter.h library

unsigned long timer = 0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);//9600
  delay(1000);
  connect_wifi();
  connect_mqtt();
  for (int i = 0; i < 10; i++) {
    counters[i] = Counter(0, i + 1, true);
  }
}

void loop() {
  //reset to main color
  //setMainColor();

  //switchSimple is just for testing/debugging
  //  if (switchSimple) {
  //    allLanesRGB(CRGB( counters[3].getVal(), 0 , counters[4].getVal()),
  //                CRGB( 0, counters[4].getVal(), 0),
  //                CRGB( 0, counters[8].getVal(), 0),
  //                CRGB( 0, 0, counters[1].getVal()));
  //  }
  stateLoop();
  showLeds();

  //run counter loops
  for (int i = 0; i < 10; i++) {
    counters[i].count();
  }

  //maintain mqtt connection
  if (!client.connected())
    reconnect();
  client.loop();

  //debugCounters();
}

void showLeds() {
  //only adress the leds if the array changed
  bool changed = false;
  //delay(10);
  for (int i = 0; i < NUM_LEDS; i++)
    if (leds[i] != last_leds[i])
      changed = true;
  if (changed) {
    FastLED.show();
    for (int i = 0; i < NUM_LEDS; i++)
      last_leds[i] = leds[i];
  }
}




